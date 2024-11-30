#include "io_redirection.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cstring>

using namespace std;

void handleRedirection(vector<string> &tokens) {
    int inputFd = -1, outputFd = -1;

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (*it == "<") {
            if (it + 1 != tokens.end()) {
                inputFd = open((it + 1)->c_str(), O_RDONLY);
                dup2(inputFd, STDIN_FILENO);
                it = tokens.erase(it, it + 2) - 1;
            } 
            else 
            {
                cerr << "No input file specified" << endl;
                return;
            }

        } 
        else if (*it == ">") 
        {
            if (it + 1 != tokens.end()) {
                outputFd = open((it + 1)->c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(outputFd, STDOUT_FILENO);
                it = tokens.erase(it, it + 2) - 1;
            } 
        else 
        {
                cerr << "No output file specified" << endl;
                return;
        }
        } 
        else if (*it == ">>") 
        {
            if(it + 1 != tokens.end()) {
                outputFd = open((it + 1)->c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(outputFd, STDOUT_FILENO);
                it = tokens.erase(it, it + 2) - 1;
            } 
            else {
                cerr << "No output file specified" << endl;
                return;
            }
        }
    }

     close(inputFd);
     close(outputFd);
}