///////////////////////////////////RAVI KUMAR HOODA/////////2018201041////////////////////////////
#include"keyMovement.h"
#include"DirListing.h"
#include<iostream>
#include<cstring>
#include<string>

using namespace std;
//string home_path="";
stack<string>backward_history;
stack<string>forward_history;

void disHomeKey(string& home_path,vector<string>&DirectryList)
{
	int low,high;
//	if(path!=home_path)
	{
//	home_path=path;
	DirectryList.clear();
	//vector<string>DirectryList;
	DirectryList=addDirList(home_path);
	int c=chdir(home_path.c_str());
	//if(c<0)
	//cout<<"error changing directory";					
	low=0;high=25;
	display(low,high,DirectryList);
					//	cout<<"\u001b[25A";
	cout<<"\033[3;1H";	
	//backward_history.pop();	
	}					
}
void disBackspaceKey(vector<string>&DirectryList,string home_path)
{
	//cout<<"\033c";
	char buffer[256];
	string path = getcwd(buffer, 256);
	if(path!=home_path)
	{
	int low,high;
	DirectryList.clear();
	//vector<string>DirectryList;
	DirectryList=addDirList("..");
	int c=chdir("..");
							//curr_ptr=0;
						//	if(c<0)
						//	cout<<"error changing directory";
	low=0;high=25;
	display(low,high,DirectryList);
						//	cout<<"\u001b[25A";
	cout<<"\033[3;1H";
	}
}
int disUpKey(int curr_ptr,vector<string>&DirectryList)
{
	
					if(curr_ptr+1>0&&curr_ptr+1<=DirectryList.size())
				{
					if(curr_ptr<25)
					{curr_ptr--;cout<<"\u001b[1A";
					//cout<<curr_ptr;
					
					}
					else
					{curr_ptr--;
					display(curr_ptr-25+1,curr_ptr+1,DirectryList);//cout<<"\u001b[1A";
					
					}
				
					
				}	
			
				return curr_ptr;
}
int disDownKey(int curr_ptr,vector<string>&DirectryList)
{
		if(curr_ptr+1<DirectryList.size()&&curr_ptr+1>=0)
				{
					
					if(curr_ptr>=25)
					{curr_ptr++;display(curr_ptr-25+1,curr_ptr+1,DirectryList);
				//	cout<<curr_ptr;
					//cout<<"\u001b[1A";
					//errFlag=true;
					}
					else
					{
					curr_ptr++;
					
					cout<<"\u001b[1B";
					}
				
					
					
				}
			
				return curr_ptr;
				
}
int disLeftKey(int curr_ptr,vector<string>&DirectryList)
{
	int low,high;
		if(!backward_history.empty())
					{
						// if(backward_history.top()!=home_path)
						{
							DirectryList.clear();
							DirectryList=addDirList(backward_history.top());
								int c=chdir((backward_history.top()).c_str());
								//if(c<0)
								//cout<<"error changing directory";
								curr_ptr=0;
							low=0;high=25;
							display(low,high,DirectryList);
						//	cout<<"\u001b[25A";
							cout<<"\033[3;1H";
							forward_history.push(backward_history.top());	
							backward_history.pop();
						}
						
						
					}
				
					return curr_ptr;
}
int disRightKey(int curr_ptr,vector<string>&DirectryList)
{
	int low,high;
	if(!forward_history.empty())
					{
						// if(backward_history.top()!=home_path)
						{
							DirectryList.clear();
							DirectryList=addDirList(forward_history.top());
								int c=chdir((forward_history.top()).c_str());
								//if(c<0)
								//cout<<"error changing directory";
								curr_ptr=0;
							low=0;high=25;
							display(low,high,DirectryList);
						//	cout<<"\u001b[25A";
							cout<<"\033[3;1H";
							backward_history.push(forward_history.top());	
							forward_history.pop();
						}
						
						
					}
					return curr_ptr;
}

int disEnterKey(int curr_ptr,vector<string>&DirectryList)
{
						
						int low,high;
						//cout<<"\033c";
						//current directory read
						char buffer[256];
						string path = getcwd(buffer, 256);
						backward_history.push(path);
						string CurrentPath;
						vector<string> tokens;
						
						stringstream check1(path);
						string rawcode;
						while(getline(check1, rawcode, '/'))
						{
							tokens.push_back(rawcode);
						}
						if(tokens[tokens.size()-1]!=DirectryList[curr_ptr])
						{
						CurrentPath = path+"/"+DirectryList[curr_ptr];
						int c=chdir(CurrentPath.c_str());
						}
						else CurrentPath=path;
						//if(c<0)
						//cout<<"error changing diectory";
						//for checking directory
						struct stat buf;
						string filename=CurrentPath;
						stat(filename.c_str(),&buf);
						
						//cout << CurrentPath << endl;
						if(S_ISDIR(buf.st_mode))
						{	DirectryList.clear();
							DirectryList=addDirList(CurrentPath);
								curr_ptr=0;
							low=0;high=25;
							display(low,high,DirectryList);

							//cout<<"\u001b[25A";
						
							//cout << CurrentPath << endl;
								cout<<"\033[3;1H";	
						}
						else
						{	
							if (fork() == 0) {
							execl("/usr/bin/xdg-open", "xdg-open", (DirectryList[curr_ptr]).c_str(), (char *)0);
								
														exit(1);
							}
							
						}
						
						return curr_ptr;
}
