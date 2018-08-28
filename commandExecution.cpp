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
void createdirectory(string src)
{
								
							if (mkdir(src.c_str(),0777) != 0)
                            {
                                cout<<"directory not created successfully";
                            }
}
void renameFiles(string src,string dest)
{
								ifstream fsin;
								ofstream ftop;
								char ch;
								
								fsin.open(src);
								if(!fsin)
								{
									cout<<"Error in opening source file..!!";
									getchar();
									exit(1);
								}
								
								ftop.open(dest);
								if(!ftop)
								{
									cout<<"Error in opening target file..!!";
									fsin.close();
									getchar();
									exit(2);
								}
								while(fsin.eof()==0)
								{
									fsin>>ch;
									ftop<<ch;
								}
							
								fsin.close();
								ftop.close();
}
void deletefile(string src)
{                               
                                 if( remove(src.c_str()) != 0 )
                                    perror( "Error deleting file" );
                                else
                                    puts( "File successfully deleted" );
                                
                            
}
void delete_dir(string src)
{                               
                                 if (rmdir(src.c_str()) != 0)
                                    perror( "Error deleting folder" );
                                else
                                    puts( "Folder successfully deleted" );
                                
                            
}
void createfile(string src)
{
								
								ofstream ftsrc;
								char ch;
								
								
								ftsrc.open(src);
								if(!ftsrc)
								{
									cout<<"Error in creating  file..!";
									getchar();
									exit(2);
								}
								ftsrc.close();
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