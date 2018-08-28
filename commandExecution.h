#include<iostream>
#include<bits/stdc++.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include<string>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <errno.h>  
#include <sys/wait.h>
#include <sys/ioctl.h>

#ifndef INC_commandExecution_H
#define INC_commandExecution_H
using namespace std;
void copyFiles(string,string);
void moveFiles(string,string);
void createdirectory(string);
void renameFiles(string ,string);
void deletefile(string);
void delete_dir(string);
void createfile(string);
void setCommandModeStatus(vector<char>&,string);
#endif  

