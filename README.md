# Shell Terminal using System Calls

[Screencast from 2024-09-09 02-39-28.webm](https://github.com/user-attachments/assets/2eeceea7-aa00-4f68-8fff-a6e62d3ef7c5)


## Overview
This project is a custom shell implemented in C++. It replicates common shell functionalities, including directory navigation, process management, I/O redirection, and command history. The shell supports various built-in commands and allows for both foreground and background process execution.

## Features
1. Directory Navigation (CD)
cd: Changes the current directory to the user's home directory.
cd ~: Also changes to the user's home directory.
cd ..: Moves up one directory level.
cd -: Switches to the previous directory and prints the directory after switching.
cd <directory>: Changes the current directory to the specified directory. Prints an error message if the directory doesn't exist.

2. Print Working Directory (PWD)
pwd: Prints the current working directory.

3. List Directory Contents (LS)
ls: Lists the contents of the current directory.
ls <directory>: Lists the contents of the specified directory.
Supports options:
-a: Includes hidden files in the listing.
-l: Displays detailed information about each file, including permissions, owner, group, size, and modification date.

4. Search
search <pattern>: Searches for files and directories matching the given pattern in the current directory. Outputs true if found, otherwise false.

5. Process Management
Foreground Execution: By default, commands are executed in the foreground.
Background Execution: Appending & to a command runs it in the background. The shell does not wait for the process to complete before accepting the next command.
CTRL+C: Interrupts the currently running foreground process.
CTRL+Z: Suspends the currently running foreground process and moves it to the background.
CTRL+D: Exits the Shell.

6. Input/Output Redirection
Output Redirection (> and >>): Redirects command output to a file. > truncates the file, and >> appends to the file.
Input Redirection (<): Redirects input from a file.
Example:
command > output.txt: Redirects standard output to output.txt.
command < input.txt: Takes input from input.txt.

7. History
history: Displays the last 10 commands entered.
The shell maintains a history of up to 20 commands across sessions.
The history is stored in a file to persist between sessions.


Compile the shell:
```bash
g++ -o shell shell.cpp builtins.cpp io_redirection.cpp
```
or
```bash
Make
```

Run the Shell:
```bash
./shell
```

