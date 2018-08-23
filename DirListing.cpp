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
void listing()
{
	
	ofstream cout;
        cout.open("/dev/pts/0",ios::out);
	struct stat buf;
	struct tm *tym;
	struct passwd *pws;
	struct group *grp;
	const char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	DIR *dir;
	int len;
	string filename;
	dirent *pdir;
	int size;
	dir=opendir(".");
	
	
	 cout<<"\u001b[31m";
	cout<<"Name"<<std::string( 26, ' ' )<<"Size"<<std::string( 15, ' ' )<<"Ownership"<<std::string( 18, ' ' )<<"Group"<<std::string( 18, ' ' )<<"User"<<std::string( 17, ' ' )<<"Last Modified"<<endl;
	cout<<"\u001b[0m";
	cout<<"\u001b[33m";
	while(readdir(dir))
	{	
		pdir=readdir(dir);
		filename=pdir->d_name;  
     		stat(pdir->d_name,&buf);
 
		len=filename.length();

		//file name
		cout<<pdir->d_name;
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
	}
	 cout<<"\u001b[0m";
	cout<<"";
	cout.close();
	closedir(dir);
}
int main(int argc, char **argv)
{
	int key1 = ' ';
	 int key2 = ' ';
	 int key3 = ' ';

	string s;
	//cout << "\033[2J\033[1;1H";
	
	listing();
	while(1)
	{
		key1 = getch();
		
		 if (key1 == 27)
		 {
		  key2 = getch();
		  key3= getch();
		
		 }

		 if (key1== 27 && key2 == 91)
		 {
		  if(key3==65)
		  {
			
			cout<<"\u001b[1A";
			cout<<"\x1b[\x32 q";
			
		   }
		    else if(key3==66)
			{
		     cout<<"\u001b[1B";
			//cout<<"\e[?5l";	
			}
		  /* else if(key3==67)
		     cout<<"\u001b[1C";
		
		  else if(key3==68)
		     cout<<"\u001b[1D";	*/			
		  
		
		  }
		 
		 
	}
	
	
return 0;
}
