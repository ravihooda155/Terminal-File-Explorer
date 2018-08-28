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

string terminalMode="NORMAL";
int main(int argc, char **argv)
{
	vector<string>DirectryList;
	//string current_path=argv[1];
	int key1 = ' ';
	int key2 = ' ';
	int key3 = ' ';
	char keyy=' ';
	vector<char>commandBuffer;
	//int command_length=0;
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
				commandBuffer.clear();
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
			if(keyy!=10 && keyy!=27 && keyy!=127)
			{
				cout<<keyy;
				commandBuffer.push_back(keyy);
			}
			////////escape Key//////////////
			else if(keyy==27)
			{
				terminalMode="NORMAL";

				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				//cout<<"\u001b["<<1<<"A";
				//cout<<"\033["<<w.ws_row-10<<";1H";
				cout<<"\u001b["<<1<<"K";
				cout<<"\033["<<3<<";1H";
				break;
				 
			}
			/////////////backspace key/////////////
			else if(keyy==127)
			{
				string mesg="";

				setCommandModeStatus(commandBuffer,mesg);
			}
			//////////////enter key////////////////
			else if(keyy==10)
			{		string mesg;
					string str=string(commandBuffer.begin(),commandBuffer.end());
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
									mesg="File Successfully Copied";
									setCommandModeStatus(commandBuffer,mesg);
								}
								///////////move file////////////
								else if(tokens[0]=="move_file")
									{
											string compSrc;
											char buffer[256];
											string basePath = getcwd(buffer, 256);
											string dest=tokens[tokens.size()-1];
											for(unsigned int i=1;i<tokens.size()-1;i++)
											{
												 compSrc=basePath+"/"+tokens[i];
												string compDest=dest+"/"+tokens[i];
												moveFiles(compSrc,compDest);
											
											}
											for(unsigned int i=1;i<tokens.size()-1;i++)
											{
												 compSrc=basePath+"/"+tokens[i];
												if( remove(compSrc.c_str()) != 0 )
													mesg="Error deleting file" ;
												else
													mesg="File successfully moved";
												
											}
											
											setCommandModeStatus(commandBuffer,mesg);
									}
									/////////create directory//////////////
								else if(tokens[0]=="create_dir")
								{
										
										char buffer[256];
										string basePath = getcwd(buffer, 256);
										
										string compSrc;
										string dest=tokens[2];
										if(dest==".")
										{
											compSrc=basePath+"/"+tokens[1];
										}
										else{
												compSrc=tokens[2]+"/"+tokens[1];
										}	
											createdirectory(compSrc);
											mesg="Directory Created Successfully";
											setCommandModeStatus(commandBuffer,mesg);
								}
								///////////rename file////////////////
								else   if(tokens[0]=="rename")
								{
								
									char buffer[256];
									string basePath = getcwd(buffer, 256);
									string src,dest;
									src=tokens[1];
									dest=tokens[2];
								
									string compSrc=basePath+"/"+src;
									string compDest=basePath+"/"+dest;
									
									renameFiles(compSrc,compDest);
									 compSrc=basePath+"/"+src;
									if( remove(compSrc.c_str()) != 0 )
										mesg= "Error deleting file";
									else
										mesg="File successfully renamed";
									
									
									setCommandModeStatus(commandBuffer,mesg);
								}
				
					}
					else if(str.length()==2)
					{
						    string basePath; 
							/////////////delete file ////////////
							if(tokens[0]=="delete_file")
							{
							
								char buffer[256];
								basePath = getcwd(buffer, 256);
								string dest;
                            	string compSrc;
							 	dest=tokens[1];
                                compSrc=basePath+"/"+dest;
                                deletefile(compSrc);
								mesg="File Deleted Successfully";
								setCommandModeStatus(commandBuffer,mesg);
							}
							///////////delete dir///////////
							else if(tokens[0]=="delete_dir")
							{
							
							    char buffer[256];
							    basePath = getcwd(buffer, 256);
							
                                string compSrc;
							    string dest=tokens[1];
                                compSrc=basePath+"/"+dest;
                                delete_dir(compSrc);
								mesg="Directory Deleted Successfully";
								setCommandModeStatus(commandBuffer,mesg);
							}	
							/////////create file////////////
							else if(tokens[0]=="create_file")
							{
							
								char buffer[256];
								basePath = getcwd(buffer, 256);
								
								string compSrc;
								string dest=tokens[2];
								if(dest==".")
								{
									compSrc=basePath+"/"+tokens[1];
								}
							    else{
									compSrc=tokens[2]+"/"+tokens[1];
							   }
									createfile(compSrc);
									mesg="File Created Successfully";
									setCommandModeStatus(commandBuffer,mesg);
							}
                    
					}
					else 
					{
					
				
					mesg="Enter correct command";
					setCommandModeStatus(commandBuffer,mesg);
					}


			}
		
		}
	
	}
	}
	
return 0;
}
