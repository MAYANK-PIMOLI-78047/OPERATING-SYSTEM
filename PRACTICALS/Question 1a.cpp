/*	
	Q1. Write a program using fork() where parent
	and child execute same program, same code
*/
#include<iostream>
#include<unistd.h>
#include<sys/types.h>		
using namespace std;

int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		cout<<"\nFORK FAILED !!";
	}
	else{
		cout<<"\nProcess executing...";
		cout<<"\nPID :"<<pid;
		cout<<"\ngetpid :"<<getpid();
		cout<<"\ngetppid :"<<getppid();
	}
	cout<<endl;
	return 0;
}


/*
			OUTPUT

onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ ps
  PID TTY          TIME CMD
 4255 pts/0    00:00:00 bash
 6918 pts/0    00:00:00 ps
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ g++ Q1a.cpp
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ ./a.out

Process execuiting...
PID :6940
getpid :6939
getppid :4255
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ 
Process execuiting...
PID :0
getpid :6940
getppid :667
^C
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ g++ Q1a.cpp
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ ./a.out

Process execuiting...
PID :6974
getpid :6973
getppid :4255
onworks@onworks-Standard-PC-i440FX-PIIX-1996:~/Desktop$ 
Process execuiting...
PID :0
getpid :6974
getppid :667

*/
