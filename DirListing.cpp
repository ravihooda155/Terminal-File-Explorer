#include"DirListing.h"
#include<iostream>


using namespace std;

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
	cout<<path<<endl<<endl;
	//cout<<DirectryList.size()<<endl;
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
