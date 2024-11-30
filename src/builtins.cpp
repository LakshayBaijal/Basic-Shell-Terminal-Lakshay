#include<bits/stdc++.h>
#include "builtins.h"
#include <unistd.h>
#include <limits.h>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;


void cdCommand(const string &path) {
    static string previousdir = getcwd(nullptr, 0);  // Track the previous directory

    if (path.empty() || path == "~") {
        chdir(getenv("HOME"));

    } 
    else if (path == "-") 
    {
        string currentdir = getcwd(nullptr, 0);
        if (chdir(previousdir.c_str()) == 0) 
        {
            cout << previousdir << endl;  
            previousdir = currentdir;          } 
        else 
        {
            cerr << "cd: " << previousdir << " No file or directory" << endl;
        }
    } else if (path == "..") {
        chdir("..");
    } else if (chdir(path.c_str()) != 0) {
        cerr << "cd: " << path << " No file or directory" << endl;
    } else {
        previousdir = getcwd(nullptr, 0);
    }
}


void pwdCommand()
{
    char cwd[PATH_MAX];

    getcwd(cwd,sizeof(cwd));
    cout<<cwd<<endl;
}

void echoCommand(const string &text)
{
    cout<< text << endl;
}


void lsCommand(const string &path,bool showall, bool showlong)
{

    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
 

    dir = opendir(path.empty() ? "." : path.c_str());
    if(dir == nullptr)
    {
        cerr<<"ls Cannot Access" << path <<"No Such Directory";
        return;
    }


    while(((entry = readdir(dir)) != nullptr))
    {
        if (!showall == true && entry->d_name[0] == '.') continue; // Skips hidden files
        stat(entry->d_name, &filestat);
        if(showlong)
        {

            cout<< ((S_ISDIR(filestat.st_mode)) ? 'd' : '-');
            cout<< ((filestat.st_mode & S_IRUSR) ? 'r' : '-');
            cout<< ((filestat.st_mode & S_IWUSR) ? 'w' : '-');
            cout<< ((filestat.st_mode & S_IXUSR) ? 'x' : '-');
            cout<< ((filestat.st_mode & S_IRGRP) ? 'r' : '-');
            cout<< ((filestat.st_mode & S_IWGRP) ? 'w' : '-');
            cout<< ((filestat.st_mode & S_IXGRP) ? 'x' : '-');
            cout<< ((filestat.st_mode & S_IROTH) ? 'r' : '-');
            cout<< ((filestat.st_mode & S_IWOTH) ? 'w' : '-');
            cout<< ((filestat.st_mode & S_IXGRP) ? 'x' : '-');

            cout<< "\t" << filestat.st_size<<"\t";
            cout << " " << entry -> d_name << "\t";

            cout<<endl;
        }
        else {
            cout << entry -> d_name << "\t";
    }
    }
    closedir(dir);
}


bool searchCommand(const string &name , const string &directory)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    
    
        if ((dir = opendir(directory.c_str())) == nullptr) 
        {
        return false;
        }    

        while ((entry = readdir(dir)) != nullptr)
        {
            string path = directory + "/" + entry -> d_name;
        
        if(strcmp(entry -> d_name, ".")==0 || strcmp(entry->d_name, "..") == 0 ) 
        {
            continue;
        }
        if(entry->d_name == name)
        {
            closedir(dir);
            return true;
        }
        
        if (stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) 
        {
            if(searchCommand(name,path))
            {
                closedir(dir);
                return true;
            }
        
        }
        }
        closedir(dir);
    return false;
}


//ps aux to get all pinfo from real terminal

void pinfoCommand(const string &pid) {
    string actualpid;
    string procpath;

    if (pid.empty()) {
        actualpid = to_string(getpid());  
    } else {
        actualpid = pid;
    }

    procpath = "/proc/" + actualpid;

    struct stat info;
    if (stat(procpath.c_str(), &info) != 0) {
        cerr << "pinfo: Unable to access process information for PID " << actualpid << endl;
        return;
    }
    
    char buffer[1024];
    string statuspath = procpath + "/status";
    int statusfd = open(statuspath.c_str(), O_RDONLY);

    if (statusfd == -1) {
        cerr << "pinfo: Unable to open status file for PID " << actualpid << endl;
        return;
    }

    ssize_t bytesRead = read(statusfd, buffer, sizeof(buffer) - 1);

    buffer[bytesRead] = '\0';

    string processStatus;
    string memoryUsage;
    string line;
    istringstream iss(buffer);

    // status information
    while (getline(iss, line)) {
        if (line.find("State:") == 0) {
            processStatus = line.substr(7);  // Extract process state
        } else if (line.find("VmSize:") == 0) {
            memoryUsage = line.substr(8);    // Extract memory usage
        }
    }

    close(statusfd);

    string exepath = procpath + "/exe";
    ssize_t len = readlink(exepath.c_str(), buffer, sizeof(buffer) - 1);

    if (len != -1) {
        buffer[len] = '\0';
    }
    else {
        cerr << "pinfo: Unable to access executable path for PID " << actualpid << endl;
        return;
    }

    cout << "pid -- " << actualpid << endl;
    cout << "Process Status -- " << processStatus << endl;
    cout << "memory -- " << memoryUsage << endl;
    cout << "Executable Path -- " << buffer << endl;
}