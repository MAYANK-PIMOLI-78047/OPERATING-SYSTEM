//Q4


#include<iostream>
#include<fcntl.h>
#include<sys/stat.h>
using namespace std;
int main(int argc,char *argv[])
{
	char time[50];
	struct stat s1;
	int fd;
	if(argc!=2)
	{
		cout<<"Wrong arguments";
		return 0;
	}
	fd=open(argv[1],O_RDONLY);
	fstat(fd,&s1);
	cout<<"Owner ID: "<<s1.st_uid<<"\n";
	cout<<"Group ID: "<<s1.st_gid<<"\n";
	printf("Mode: %o(octal)\n",s1.st_mode & 0777);
	cout<<"Size= "<<s1.st_size<<"\n";
	cout<<"No of links= "<<s1.st_nlink<<"\n";
	strftime(time, sizeof (time),"%d.%m.%Y.%H.%M.%S",localtime(&s1.st_atime));
	cout<<"Last access time= "<<time<<"\n";
	strftime(time, sizeof (time),"%d.%m.%Y.%H.%M.%S",localtime(&s1.st_mtime));
	cout<<"Last modified time= "<<time<<"\n";
	return 0;
	
	
}
