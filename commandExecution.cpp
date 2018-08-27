#include"commandExecution.h"
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

void copyFiles(string src,string dest)
{
								ifstream fs;
								ofstream ft;
								char ch;
								
								fs.open(src);
								if(!fs)
								{
									cout<<"Error in opening source file..!!";
									getchar();
									exit(1);
								}
								
								ft.open(dest);
								if(!ft)
								{
									cout<<"Error in opening target file..!!";
									fs.close();
									getchar();
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
void moveFiles(string src,string dest)
{
								ifstream fs;
								ofstream ft;
								char ch;
								
								fs.open(src);
								if(!fs)
								{
									cout<<"Error in opening source file..!!";
									getchar();
									exit(1);
								}
								
								ft.open(dest);
								if(!ft)
								{
									cout<<"Error in opening target file..!!";
									fs.close();
									getchar();
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

