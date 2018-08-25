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
using namespace std;


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
//directory files loading in vector
vector<string> addDirList(string dirname)
{
	DIR *dir;
	dirent *pdir;
	vector<string>DirectryList;
	dir=opendir(dirname.c_str());
	while((pdir=readdir(dir))!=NULL)
	{	string filename((pdir->d_name));
 		DirectryList.push_back(filename);
	}
	closedir(dir);
	return DirectryList;
}
void listing(string filename)
{
	struct stat buf;
	struct tm *tym;
	struct passwd *pws;
	struct group *grp;
	const char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int len;
	int size;
	
	cout<<"\u001b[33m";
	
		
		  
     		stat(filename.c_str(),&buf);
 		
		len=filename.size();

		//file name
		cout<<filename;
		cout << std::string( 30-len, ' ' );

		//file size
	
		cout<<buf.st_size<<"B"<<std::string(2,'\t');

		//ownership
		 
	        cout<<( (S_ISDIR(buf.st_mode)) ? "d" : "-");
	        cout<<( (buf.st_mode & S_IRUSR) ? "r" : "-");
	        cout<<( (buf.st_mode & S_IWUSR) ? "w" : "-");
	        cout<<( (buf.st_mode & S_IXUSR) ? "x" : "-");
	        cout<<( (buf.st_mode & S_IRGRP) ? "r" : "-");
	        cout<<( (buf.st_mode & S_IWGRP) ? "w" : "-");
	        cout<<( (buf.st_mode & S_IXGRP) ? "x" : "-");
	        cout<<( (buf.st_mode & S_IROTH) ? "r" : "-");
	        cout<<( (buf.st_mode & S_IWOTH) ? "w" : "-");
		cout<<( (buf.st_mode & S_IXOTH) ? "x" : "-");
		cout<<std::string(2,'\t');
		
		//group
		grp = getgrgid(buf.st_gid);
		if(strlen(grp->gr_name)<12)
		{cout<<grp->gr_name;
		cout<<std::string((12-strlen(grp->gr_name)),' ');
		}
		else if(strlen(grp->gr_name)>12)
		{ string str=grp->gr_name;
		str.resize(10);
		cout<<str<<"..";
		}
		else
		{cout<<grp->gr_name;
		}
		cout<<std::string(2,'\t');
		
		//owner
		pws = getpwuid(buf.st_uid);
		cout << pws->pw_name;
		if(strlen(pws->pw_name)<12)
		cout<<std::string((12-strlen(pws->pw_name)),' ');
		cout<<std::string(2,'\t');

		//file last modified
		 tym = gmtime(&(buf.st_mtime));
		  cout<<tym->tm_mday<<" "<<months[(tym->tm_mon)-1]<<" "<<tym->tm_hour<<":"<<tym->tm_min;
		
		cout<<endl;
	
	 cout<<"\u001b[0m";
	//cout<<"";
	
}
void display(int low,int high,vector<string>DirectryList)
{	
	cout<<"\033c";//clear screen
	char buffer[256];
	string path = getcwd(buffer, 256);
	cout<<path<<endl;
	cout<<DirectryList.size()<<endl;
	 /*cout<<"\u001b[31m";
	cout<<"Name"<<std::string( 26, ' ' )<<"Size"<<std::string( 15, ' ' )<<"Ownership"<<std::string( 18, ' ' )<<"Group"<<std::string( 18, ' ' )<<"User"<<std::string( 17, ' ' )<<"Last Modified"<<endl;
	cout<<"\u001b[0m";*/
	int i;
	if(DirectryList.size()<25)
	high=DirectryList.size();
	
	for(i=low;i<high;i++)
	{
	listing(DirectryList[i]);
	
	}
	if(high<22)
	cout<<"\u001b["<<high-low+2<<"A";
	
}
string home_path="";
stack<string>backward_history;
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
	pid_t  pid;
	cout<<"\u001b[2J";
	if(argc<2)
	{string s=".";
	DirectryList=addDirList(s);	
	}
	else
	{string s=argv[1];
		DirectryList=addDirList(s);
	}
	//cout<<"\u001b[1A";
	
	low=0;high=25;
	display(low,high,DirectryList);
	//cout<<"\033[3;1H";
	cout<<"\u001b[25A";
	//home directory 
	char buffer[256];
	string path = getcwd(buffer, 256);
	home_path=path;
	int curr_ptr=0;
	while(1)
	{
		key1 = getch();
		
		 if (key1 == 27)
		 {
		  key2 = getch();
		  key3= getch();
		
		 }
		  if(key1==104)
		     {
				
						 DirectryList.clear();
						DirectryList=addDirList(home_path);
						
						curr_ptr=0;
						low=0;high=25;
						display(low,high,DirectryList);
					//	cout<<"\u001b[25A";
						cout<<"\033[3;1H";	
						 backward_history.pop();
					
			 }
		if(key1==10)
		{			DirectryList.clear();
					//cout<<"\033c";
					//current directory read
					char buffer[256];
					string path = getcwd(buffer, 256);
					backward_history.push(path);
					string CurrentPath;
					CurrentPath = path+"/"+DirectryList[curr_ptr];
					int c=chdir(CurrentPath.c_str());

					//for checking directory
					struct stat buf;
					string filename=CurrentPath;
					stat(filename.c_str(),&buf);
					//cout << CurrentPath << endl;
					if(S_ISDIR(buf.st_mode))
					{
						DirectryList=addDirList(CurrentPath);
							curr_ptr=0;
						low=0;high=25;
						display(low,high,DirectryList);

						//cout<<"\u001b[25A";
					
						cout << CurrentPath << endl;
							cout<<"\033[3;1H";	
					}
					else
					{
						
						if (fork() == 0) {
						execl("/usr/bin/xdg-open", "xdg-open", (DirectryList[curr_ptr]).c_str(), (char *)0);
						cout<<"File cannot be opened";
						exit(1);
						}
					}
		}
		
		 if (key1== 27 && key2 == 91)
		 {
		  if(key3==65)
		  {
				
				if(curr_ptr>0&&curr_ptr<=DirectryList.size())
			{
				if(curr_ptr<=25)
				{curr_ptr--;cout<<"\u001b[1A";
				
				}
				else
				{curr_ptr--;
				display(curr_ptr-25,curr_ptr,DirectryList);cout<<"\u001b[1A";
				
				}
			
				
			}		
			
		   }
		    else if(key3==66)
			{	
			
			if(curr_ptr<DirectryList.size()&&curr_ptr>=0)
			{
				
				if(curr_ptr>=25)
				{curr_ptr++;display(curr_ptr-25,curr_ptr,DirectryList);
				cout<<"\u001b[1A";
				//errFlag=true;
				}
				else
				{
				curr_ptr++;
				
				cout<<"\u001b[1B";
				}
			
				
				
			}
			
				
			
			}
		   else if(key3==68)
		     {
				// cout<<"hello"<<backward_history.size();
				 if(!backward_history.empty())
				 {
					// if(backward_history.top()!=home_path)
					 {
						 DirectryList.clear();
						DirectryList=addDirList(backward_history.top());
						
							curr_ptr=0;
						low=0;high=25;
						display(low,high,DirectryList);
					//	cout<<"\u001b[25A";
						cout<<"\033[3;1H";	
						 backward_history.pop();
					 }
					
					
				 }
			 }
		
		 /* else if(key3==68)
		     cout<<"\u001b[1D";	*/			
		  
		
		  }
		 
		 
	}
	
	
return 0;
}
