///////////////////////////////////RAVI KUMAR HOODA/////////2018201041////////////////////////////
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
int disUpKey(int,std::vector<std::string>&);
int disDownKey(int,std::vector<std::string>&);
int disLeftKey(int,std::vector<std::string>&);
int disRightKey(int,std::vector<std::string>&);
void disHomeKey(string,std::vector<std::string>&);
void disBackspaceKey(std::vector<std::string>&);
int disEnterKey(int,std::vector<std::string>&);
#endif  

