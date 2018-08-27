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
#include"commandExecution.h"
#include<fstream>
#include <sys/ioctl.h>
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
//	string home_path="";
/*void copyFiles(string src,string dest)
{
								ifstream fs;
								ofstream ft;
								char ch;
								
								fs.open(src.c_str());
								if(!fs)
								{
									cout<<"Error in opening source file..!!";
									getch();
									exit(1);
								}
								
								ft.open(dest.c_str());
								if(!ft)
								{
									cout<<"Error in opening target file..!!";
									fs.close();
									getch();
									exit(2);
								}
								while(fs.eof()==0)
								{
									fs>>ch;
									ft<<ch;
								}
							
								fs.close();
								ft.close();

}
*/
string terminalMode="NORMAL";
int main(int argc, char **argv)
{
	vector<string>DirectryList;
	//string current_path=argv[1];
	int key1 = ' ';
	int key2 = ' ';
	int key3 = ' ';
	char keyy=' ';
	char commandBuffer[256];
	int command_length=0;
	int low,high;
	
	//bool errFlag=false;//bug fixing
	//cout << "\033[2J\033[1;1H";
	
	cout<<"\u001b[2J";
	if(argc<2)
	{string curr_path=".";
	DirectryList=addDirList(curr_path);
	int c=chdir(curr_path.c_str());	
	if(c<0)
	cout<<"Error in changing directory";
	}
	else
	{string curr_path=argv[1];
		DirectryList=addDirList(curr_path);
	int c=chdir(curr_path.c_str());
	if(c<0)
	cout<<"Error in changing directory";
	}
	//cout<<"\u001b[1A";
	
	low=0;high=25;
	display(low,high,DirectryList);
	cout<<"\033[3;1H";
	//cout<<"\u001b[25A";
	//home directory 
	char buffer[256];
	string home_path="";
	string path = getcwd(buffer, 256);
	home_path=path;
	int curr_ptr=0;
	while(1)
	{

		if(terminalMode=="NORMAL")
		{
		
		key1 = getch();
		////////////colon key/////////
		if(key1==58)
		{	
			
				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				//cout<<"\u001b[J";
				cout<<"\u001b["<<w.ws_row-3<<"B";
				//cout<<"\033["<<50<<"B";
				command_length=0;
				terminalMode="COMMAND";
				cout<<"\u001b[33m";
				cout<<"Enter Command:";
				cout<<"\u001b[0m";
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
			{	curr_ptr=disEnterKey(curr_ptr,DirectryList);
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
	/////////////Command Mode///////////////////////////
	else if(terminalMode=="COMMAND"){
		
		while(keyy=getch())
		{
			if(keyy!=10 && keyy!=27)
			{
				cout<<keyy;
				commandBuffer[command_length]=keyy;
				command_length++;
			}
			////////escape Key//////////////
			else if(keyy==27)
			{
				terminalMode="NORMAL";

				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				cout<<"\u001b["<<1<<"A";
				cout<<"\033["<<w.ws_row-4<<";1H";
				cout<<"\u001b["<<1<<"K";
				cout<<"\u001b["<<w.ws_row-7<<"A";
				break;
				 
			}
			//////////////enter key////////////////
			else if(keyy==10)
			{
					string str=string(commandBuffer);
					vector<string> tokens;
					stringstream check1(str);
					string intermediate;
					while(getline(check1, intermediate, ' '))
					{
						tokens.push_back(intermediate);
					}				
					if(str.length()>2)
					{			
								//////copy file////////////
								if(tokens[0]=="copy_file")
								{
									string dest,basePath;
									char buffer[256];
									basePath = getcwd(buffer, 256);
									dest=tokens[tokens.size()-1];
									
									for(unsigned int i=1;i<tokens.size()-1;i++)
									{
										string compSrc=basePath+"/"+tokens[i];
										string compDest=dest+"/"+tokens[i];
										cout<<compSrc<<compDest;
										copyFiles(compSrc,compDest);
									
									}
								}
								else if(tokens[0]=="move_file")
									{
											
											char buffer[256];
											string basePath = getcwd(buffer, 256);
											string dest=tokens[tokens.size()-1];
											for(int i=1;i<tokens.size()-1;i++)
											{
												string compSrc=basePath+"/"+tokens[i];
												string compDest=dest+"/"+tokens[i];
												moveFiles(compSrc,compDest);
											
											}
											for(int i=1;i<tokens.size()-1;i++)
											{
												string compSrc=basePath+"/"+tokens[i];
												if( remove(compSrc.c_str()) != 0 )
													perror( "Error deleting file" );
												else
													puts( "File successfully moved" );
												return 0;
											}
									}
                	
	
				
					}




			}
		
		}
	
	}
	}
	
return 0;
}
