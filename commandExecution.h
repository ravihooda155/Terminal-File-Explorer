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
string copyFiles(string,string);
string moveFiles(string,string);
string createdirectory(string);
string renameFiles(string ,string);
string deletefile(string);
string delete_dir(string);
string createfile(string);
void setCommandModeStatus(std::vector<char>&,std::string);
std::vector<std::string> searchFile(std::string,std::vector<std::string>&,string);
void snap_shot(string ,ofstream&);
void rec_dir_copy(string,string );
#endif  

