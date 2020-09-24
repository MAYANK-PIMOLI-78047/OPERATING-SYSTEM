#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>

using namespace std;

int main()
{
    int z;
    struct utsname s1;
    z=uname(&s1);
    if(z==0)
    {
        printf("\nSystem name : %s" ,s1.sysname);
        printf("\nVersion : %s" , s1.version);
        printf("\nRelease : %s" , s1.release);
        printf("\nMachine : %s" , s1.machine);
        system("cat /proc/cpuinfo | awk 'NR==3,NR==4{print}'");

    }
    else
    {
       printf("Ooops Error !! \n");

    }

    return 0;
}
