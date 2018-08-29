#include"commandExecution.h"
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

string copyFiles(string src,string dest)
{
								ifstream fs;
								ofstream ft;
								char ch;
								string mesg;
								fs.open(src);
								if(!fs)
								{
									mesg="Error in opening source file..!!";
									exit(1);
								}
								
								ft.open(dest);
								if(!ft)
								{
									mesg="Error in opening target file..!!";
									fs.close();
									exit(2);
								}
								while(fs.eof()==0)
								{
									fs>>ch;
									ft<<ch;
								}
							
								fs.close();
								ft.close();
								return mesg;
}
string moveFiles(string src,string dest)
{
								ifstream fs;
								ofstream ft;
								char ch;
								string mesg;
								fs.open(src);
								if(!fs)
								{
									mesg="Error in opening source file..!!";
								
									exit(1);
								}
								
								ft.open(dest);
								if(!ft)
								{
									mesg="Error in opening target file..!!";
									fs.close();
								
									exit(2);
								}
								while(fs.eof()==0)
								{
									fs>>ch;
									ft<<ch;
								}
							
								fs.close();
								ft.close();
								return mesg;
}
string createdirectory(string src)
{
								string mesg;
							if (mkdir(src.c_str(),0777) != 0)
                            {
                                mesg="directory not created successfully";
                            }
							return mesg;
}
string renameFiles(string src,string dest)
{
								ifstream fsin;
								ofstream ftop;
								char ch;
								string mesg;
								fsin.open(src);
								if(!fsin)
								{
									mesg="Error in opening source file..!!";
									
									exit(1);
								}
								
								ftop.open(dest);
								if(!ftop)
								{
									mesg="Error in opening target file..!!";
									fsin.close();
									
									exit(2);
								}
								while(fsin.eof()==0)
								{
									fsin>>ch;
									ftop<<ch;
								}
							
								fsin.close();
								ftop.close();
								return mesg;
}
string deletefile(string src)
{                              string mesg; 
                                 if( remove(src.c_str()) != 0 )
                                    mesg="Error deleting file" ;
                                else
                                    mesg= "File successfully deleted" ;
									return mesg;
                                
                            
}
string delete_dir(string src)
{                               string mesg;
                                 if (rmdir(src.c_str()) != 0)
                                    mesg= "Error deleting folder";
                                else
                                    mesg= "Folder successfully deleted" ;
                                return mesg;
                            
}
string createfile(string src)
{
								
								ofstream ftsrc;
								char ch;
								string mesg;
								
								ftsrc.open(src);
								if(!ftsrc)
								{
									mesg="Error in creating  file..!";
								
									exit(2);
								}
								ftsrc.close();
								return mesg;
}
void setCommandModeStatus(vector<char>&commandBuffer,string mesg)
{
				struct winsize w;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				
				//cout<<"\033["<<w.ws_row-4<<";25H";
				cout<<"\u001b["<<1<<"K";
				//cout<<"\u001b["<<w.ws_row-7<<"A";
				cout<<"\033["<<w.ws_row<<";1H";
				cout<<"\u001b[33m";
				cout<<"Enter Command:";
				cout<<"\u001b[0m";

				cout<<mesg;
				
			    cout<<"\033["<<w.ws_row<<";"<<15+mesg.length()<<"H";
				commandBuffer.clear();
}
vector<string> searchFile(string dir,vector<string>&search1,string file)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char buffer[256];
	string  basePath = getcwd(buffer, 256);
	if((dp = opendir(dir.c_str())) == NULL) 
	{
	//return search1;
	}
	chdir(dir.c_str());
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
		if(strcmp(".",entry->d_name) == 0 ||
		strcmp("..",entry->d_name) == 0)
		continue;
		search1=searchFile(dir+"/"+string((entry->d_name)),search1,file);
	    }
	    else 
		{
			if(string(entry->d_name)==file)
			search1.push_back(dir+"/"+string(entry->d_name));
		
		}
	}
	chdir(basePath.c_str());
	closedir(dp);
	return search1;
}

void snap_shot(string dir,ofstream &of)
{
        DIR *dp;
        struct dirent *entry;
        struct stat statbuf;
        queue<string>pathQueue;
        if((dp = opendir(dir.c_str())) == NULL) {
       // fprintf(stderr,"cannot open directory: %s\n", string(dir));
            return;
        }
        chdir(dir.c_str());
        while((entry = readdir(dp)) != NULL) 
        {
                lstat(entry->d_name,&statbuf);
                if(S_ISDIR(statbuf.st_mode)) {
                
                if(string(entry->d_name)=="." ||(string(entry->d_name)) == "..")
                continue;
                //cout<<string(entry->d_name)<<" ";
                of<<string(entry->d_name)<<" ";
                pathQueue.push(string(entry->d_name));
            
               
        }
        else  
        {//cout<<string(entry->d_name)<<"  ";
        of<<string(entry->d_name)<<"  ";
        }

        }
        while(!pathQueue.empty())
        {
         // cout<<endl<<endl<<"     ./"<<pathQueue.front()<<":"<<endl<<"         ";
          of<<endl<<endl<<"     ./"<<pathQueue.front()<<":"<<endl<<"         ";
             snap_shot(string(dir)+"/"+pathQueue.front(),of);
                chdir((dir+"/"+pathQueue.front()).c_str());
                pathQueue.pop();
        }
        
               
        closedir(dp);
}
void rec_dir_copy(string dir,string dest)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char buffer[256];
	string  basePath = getcwd(buffer, 256);
	if((dp = opendir(dir.c_str())) == NULL) 
	{
	
	}
	chdir(dir.c_str());
	while((entry = readdir(dp)) != NULL) 
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) 
		{
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
		continue;
        cout<<dir+"/"+string(entry->d_name)<<dest+"/"+string(entry->d_name);
        createdirectory(dest+"/"+string(entry->d_name));
		rec_dir_copy(dir+"/"+string(entry->d_name),dest+"/"+string(entry->d_name));
	    }
	    else 
		{		
            copyFiles(dir+"/"+string(entry->d_name),dest+"/"+string(entry->d_name));
		}
	}
	chdir(basePath.c_str());
	closedir(dp);
	
}	