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
#include"DirListing.h"
#include"keyMovement.h"
using namespace std;

//////////shifting to non canonical to get input//////////////////////
int getch(void)
{
 int ch;
 struct termios oldt;
 struct termios newt;
 tcgetattr(STDIN_FILENO, &oldt); 
 newt = oldt;  
 newt.c_lflag &= ~(ICANON | ECHO); 
 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 ch = getchar(); 
 tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
 return ch; 
}

string terminalMode="NORMAL";
int main(int argc, char **argv)
{
	vector<string>DirectryList;
	//string current_path=argv[1];
	int key1 = ' ';
	 int key2 = ' ';
	 int key3 = ' ';
	int low,high;
	
	//bool errFlag=false;//bug fixing
	//cout << "\033[2J\033[1;1H";
	
	cout<<"\u001b[2J";
	if(argc<2)
	{string curr_path=".";
	DirectryList=addDirList(curr_path);
	int c=chdir(curr_path.c_str());	
	if(c<0)
    cout<<"Error";
	}
	else
	{string curr_path=argv[1];
		DirectryList=addDirList(curr_path);
	int c=chdir(curr_path.c_str());
	if(c<0)
    cout<<"Error";
	}
	//cout<<"\u001b[1A";
	
	low=0;high=25;
	display(low,high,DirectryList);
	cout<<"\033[3;1H";
	//cout<<"\u001b[25A";
	//home directory 
	char buffer[256];
	 string home_path;
	string path = getcwd(buffer, 256);
	home_path=path;
	unsigned int curr_ptr=0;//for displaying screen content
	string chmode;
	int command_count=0;	
	while(1)
	{

		if(terminalMode=="NORMAL")
		{
		
		key1 = getch();
		////////////colon key/////////
		if(key1==58)
		{	
			
			
			cout<<"\u001b[30;1H";
			chmode="no";
			terminalMode="COMMAND";
		}
		/////////for up down left right navigation/////////////
		 if (key1 == 27)
		 {
		  key2 = getch();
		  key3= getch();
		
		 }
		 ///////////home key///////////
		  if(key1==104)
		     {
				disHomeKey(home_path,DirectryList);
				curr_ptr=0;
						 
			 }
			 ////////backspace key/////////
			 if(key1==127)
			 {
				 disBackspaceKey(DirectryList);
				 curr_ptr=0;	
			 }
			 ///////////enter key//////////////////////
			if(key1==10)
			{			curr_ptr=disEnterKey(curr_ptr,DirectryList);
			}
		//////key movement up down left right/////////////
			if (key1== 27 && key2 == 91)
			{///up key/////
			if(key3==65)
			{
				curr_ptr=disUpKey(curr_ptr,DirectryList);	
				
			}
			//////down key/////
				else if(key3==66)
				{	
				curr_ptr=disDownKey(curr_ptr,DirectryList);
				}
				//////left key//////
			else if(key3==68)
				{
					// cout<<"hello"<<backward_history.size();
					curr_ptr=disLeftKey(curr_ptr,DirectryList);
				
				}
			///////right key///////
			else if(key3==67)
				{
					curr_ptr=disRightKey(curr_ptr,DirectryList);
				
				}			
			}
			
		 
	}
	else{
		
		if(chmode=="change")
		{
			key1=getch();
			if(key1==27)
			{
				string str;
				terminalMode="NORMAL";
				cout<<"\u001b[J";
				cout<<"\u001b[27A";
			}
		}
		else{
				 chmode="no";
				cout<<"\u001b[33m";
				cout<<"Enter Command:";
				cout<<"\u001b[0m";	
				string str;command_count++;
				cin>>str;
				///execution
				if(str=="exit")
				{chmode="change";
				cout<<"\u001b["<<command_count<<"A";
				cout<<"\u001b["<<command_count<<"K";
				command_count=0;
				}
		}
	}
	}
	
return 0;
}
