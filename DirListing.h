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

#ifndef INC_DirListing_H
#define INC_DirListing_H
using namespace std;
std::vector<std::string> addDirList(std::string);
void listing(std::string);
void display(int,int,std::vector<std::string>);
void displaySearchResult(int,int,std::vector<std::string>);
#endif  

