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
using namespace std;
//struct termios saved_attributes;
vector<string>DirectryList;
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
void addDirList(char dirname[])
{
	DIR *dir;
	dirent *pdir;
	
	dir=opendir(dirname);
	while((pdir=readdir(dir))!=NULL)
	{	string filename((pdir->d_name));
 		DirectryList.push_back(filename);
	}
	closedir(dir);
}
void listing(string filename)
{
	// char*filename=filname.c_str();
	struct stat buf;
	struct tm *tym;
	struct passwd *pws;
	struct group *grp;
	const char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int len;
	int size;
	
	cout<<"\u001b[33m";
	//while(filename!=NULL)
		
		  
     		stat(filename.c_str(),&buf);
 		
		len=filename.size();

		//file name
		cout<<filename;
		cout << std::string( 30-len, ' ' );

		//file size
		cout<<buf.st_size<<"B"<<std::string(2,'\t');

		//ownership
		 
	        cout<<( (S_ISDIR(buf.st_mode)) ? "d" : "f");
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
	cout<<"";
	
}
void display(int low,int high)
{	
	cout<<"\033c";//clear screen
	 cout<<"\u001b[31m";
	cout<<"Name"<<std::string( 26, ' ' )<<"Size"<<std::string( 15, ' ' )<<"Ownership"<<std::string( 18, ' ' )<<"Group"<<std::string( 18, ' ' )<<"User"<<std::string( 17, ' ' )<<"Last Modified"<<endl;
	cout<<"\u001b[0m";
	int i;
	if(DirectryList.size()<34)
	high=DirectryList.size();
	for(i=low;i<high;i++)
	{
	listing(DirectryList[i]);
	}
	if(high<30)
	cout<<"\u001b["<<high-low<<"A";
	
}
int main(int argc, char **argv)
{
	int key1 = ' ';
	 int key2 = ' ';
	 int key3 = ' ';
	int low,high;
	char s[]={"."};
	bool errFlag=false;//bug fixing
	//cout << "\033[2J\033[1;1H";
	cout<<"\u001b[2J";
	if(argc<2)
	{
	addDirList(s);	
	}
	else
	{addDirList(argv[1]);
	}
	//cout<<"\u001b[1A";
	
	low=0;high=34;
	display(low,high);

	cout<<"\u001b[34A";
	int curr_ptr=0;
	while(1)
	{
		key1 = getch();
		
		 if (key1 == 27)
		 {
		  key2 = getch();
		  key3= getch();
		
		 }
		if(key1==10)
		{cout<<"\033c";
		if(curr_ptr>=0)
		cout<<"File is"<<DirectryList[curr_ptr-1];
		}
		 if (key1== 27 && key2 == 91)
		 {
		  if(key3==65)
		  {
				
				if(curr_ptr>0&&curr_ptr<=DirectryList.size())
			{
				if(curr_ptr<=34)
				{curr_ptr--;cout<<"\u001b[1A";
				
				}
				else
				{curr_ptr--;
				display(curr_ptr-34,curr_ptr);cout<<"\u001b[1A";
				
				}
			
				
			}
			
				
				
			
		   }
		    else if(key3==66)
			{	
			
			if(curr_ptr<DirectryList.size()&&curr_ptr>=0)
			{
				
				if(curr_ptr>=34)
				{curr_ptr++;display(curr_ptr-34,curr_ptr);
				cout<<"\u001b[1A";
				errFlag=true;
				}
				else
				{
				curr_ptr++;
				
				cout<<"\u001b[1B";
				}
			
				
				
			}
			
				
			
			}
		  /* else if(key3==67)
		     cout<<"\u001b[1C";
		
		  else if(key3==68)
		     cout<<"\u001b[1D";	*/			
		  
		
		  }
		 
		 
	}
	
	
return 0;
}
