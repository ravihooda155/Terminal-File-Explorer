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

#ifndef INC_keyMovement_H
#define INC_keyMovement_H
using namespace std;
int disUpKey(unsigned int,std::vector<std::string>&);
int disDownKey(unsigned int,std::vector<std::string>&);
int disLeftKey(unsigned int,std::vector<std::string>&);
int disRightKey(unsigned int,std::vector<std::string>&);
void disHomeKey(std::string,std::vector<std::string>&);
void disBackspaceKey(std::vector<std::string>&);
int disEnterKey(unsigned int,std::vector<std::string>&);
#endif  

