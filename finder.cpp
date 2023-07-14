#include <iostream>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <cstring>
#include <string>

using namespace std;

void findfiles(char parmpath[], char parmname[], char parmext[])
{
	char entirepath[1024];
	char names[256];
	string yourname;
	string yourext;
	int totlen;
	int dotloc;
	int pattpos;
	string filealone;
	string extalone;

	DIR *dir;
	struct dirent *ent;
	
	yourext = parmext;

	if ((dir = opendir (parmpath)))
	{
	/* print all the files and directories within directory */
		while ((ent = readdir (dir)))
		{
			
			if ((ent->d_name[0]) != '.')
			{
				strcpy(entirepath,parmpath);
				strcat(entirepath,"/");
				strcpy(names,ent->d_name);
				strcat(entirepath,names);
				
				if (filesystem::is_directory(entirepath))
				{
					findfiles(entirepath,parmname,parmext);
				}
				else
				{
					yourname = names;
					totlen=yourname.length();
					dotloc=yourname.find_last_of(".");
						
					if (dotloc > 0)
					{
						filealone=yourname.substr(0,dotloc);
						extalone=yourname.substr(dotloc+1,totlen-dotloc+1);
						if ((extalone.compare(yourext)) == 0 )
						{
							pattpos = filealone.find(parmname);
							if (pattpos != totlen)
							{	
								cout << parmpath << endl;
								cout << setw(10) << filealone << setw(10) << extalone << endl;
							}
						}
					}	
				}
			}
		}
		closedir (dir);
	}
	else
	{
		/* could not open directory */
		perror ("");
	}
};	

int main()
{
	char path[1024];
	char name2find[256];
	char ext2find[4];
	cout << "Enter the Path: ";
	cin.getline(path,1024) ;
	cout << "Enter the File: ";
	cin.getline(name2find,256);
	cout << "Enter the Ext: ";
	cin.getline(ext2find,4);
	cout << endl;
	cout << "Below the list of matches from each folder" << endl; 
	cout << endl;
	
	findfiles(path,name2find,ext2find);
	
	return 0;
};