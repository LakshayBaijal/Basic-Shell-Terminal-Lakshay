#include <bits/stdc++.h>
#include "shell.h"
#include "builtins.h"
#include "io_redirection.h"
#include <iostream>
#include <fcntl.h> 
#include <unistd.h>     
#include <pwd.h>        
#include <limits.h>     
#include <sstream>      
#include <vector>       
#include <cstring>     
#include <sys/wait.h>   
#include <errno.h>      

#include <signal.h> 
using namespace std;



pid_t currentForegroundProcess = -1;
// Signal handler SIGTSTP CTRL Z
void handleSigTstp(int sig) {
    if (currentForegroundProcess != -1) {
        kill(currentForegroundProcess, SIGTSTP);
        cout << " Process stopped" << endl;
    }
}

// Signal handler SIGINT CTRL C
void handleSigInt(int sig) {
    if (currentForegroundProcess != -1) {
        kill(currentForegroundProcess, SIGINT);
        cout << " Process interrupted" << endl;
    }
}




void Shell::run() {
    signal(SIGTSTP, handleSigTstp);  // Handle CTRL-Z
    signal(SIGINT, handleSigInt);    // Handle CTRL-C

    historyFile = "./history.txt";
    loadhistory();

    string command;
    while (true) {
        display();
        getline(cin, command);

        if (command == "exit" || cin.eof()) {
            cout<<endl;
            break;  // Handle exit or CTRL-D
        }
        if (command.empty()) continue;

        vector<string> tokens = tokenize(command);
        addhistory(tokens[0]);

        if (tokens.empty()) continue;

        handleRedirection(tokens);

        if (tokens[0] == "cd") {
            cdCommand(tokens.size() > 1 ? tokens[1] : "");
        } else if (tokens[0] == "pwd") {
            pwdCommand();
        } else if (tokens[0] == "echo") {
            echoCommand(command.substr(5));
        } else if (tokens[0] == "ls") {
            bool showall = false;
            bool showlong = false;
            string path = ".";

            for (size_t i = 1; i < tokens.size(); i++) {
                if (tokens[i] == "-a") {
                    showall = true;
                }
                if (tokens[i] == "-l") {
                    showlong = true;
                }
            }
            lsCommand(path, showall, showlong);
        } else if (tokens[0] == "search") {
            bool found = searchCommand(tokens[1], ".");
            cout << (found ? "true" : "false") << endl;
        } else if (tokens[0] == "pinfo") {
            pinfoCommand(tokens.size() > 1 ? tokens[1] : "");
        } else if (tokens[0] == "history") {
            showhistory();
        } else {
            pid_t pid = fork();
            
            if (pid == 0) {  // Child process
                vector<char*> args;
                for (auto &t : tokens) args.push_back(&t[0]);
                args.push_back(nullptr);
                execvp(args[0], args.data());


            } else if (pid > 0) {  // Parent process
                cout <<"  "<<pid << " ";
                currentForegroundProcess = pid;  // Track the foreground process
                waitpid(pid, nullptr, 0);
                currentForegroundProcess = -1;   // Reset after the process finishes
            }

            else // Failed Parent and Child Process
            {
                cerr<<"Failed to fork " <<strerror(errno) << endl;
            }
        }

        cout << endl;
    }
}




void Shell::display()
{
    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];
    
    gethostname(hostname,sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    cout<<hostname<<":"<<cwd<<"$ ";
}

vector<string> Shell::tokenize(const string &str)
{
    istringstream iss(str);
    vector <string> tokens;
    string token;

    while(iss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}





void Shell::loadhistory() {
    int fd = open(historyFile.c_str(), O_RDONLY | O_CREAT, 0644);
    
    char buffer[2000];
    ssize_t bytesRead;
    string token;

    while ((bytesRead = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        token += buffer;
        
        size_t pos;
        while ((pos = token.find('\n')) != string::npos) {
            history.push_back(token.substr(0, pos));
            token.erase(0, pos + 1);
        }
    }

    close(fd);
}
void Shell::addhistory(const std::string &tokens) 
{
    history.push_back(tokens);
}

void Shell::showhistory() {

    for (size_t i = 0; i < history.size(); ++i) {
        cout << i + 1 << " " << history[i] << endl;
    }
}

