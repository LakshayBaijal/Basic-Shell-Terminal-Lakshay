#include<bits/stdc++.h>
using namespace std;
#include <termios.h>  

#ifndef SHELL_H
#define SHELL_H


class Shell {
public:
    void run();

private:

    string historyFile; 
    vector <string> history;

    void display();
    vector <string> tokenize(const string &str);
    void loadhistory();
    void addhistory(const std::string &command);
    void showhistory();



};

#endif