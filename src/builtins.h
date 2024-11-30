#include<bits/stdc++.h>
#ifndef BUILTINS_H
#define BUILTINS_H
using namespace std;

void cdCommand(const string &path);
void pwdCommand();
void echoCommand(const string &text);
void lsCommand(const string &path, bool showall, bool showlong);
bool searchCommand(const string &name, const string &directory);
void pinfoCommand(const string &pid = "");

#endif

