#include<iostream>
#include<cmath>
#include<sys/sysinfo.h>

using namespace std;

int main(){

	int a, total_RAM, free_RAM, used_RAM;
	struct sysinfo obj1;
	a=sysinfo(&obj1);
	if(a==0)
	{
		total_RAM = obj1.totalram/pow(2,20);
		free_RAM = obj1.freeram/pow(2,20);
		used_RAM = total_RAM - free_RAM;
		cout<<"\nTotal RAM is :"<<total_RAM<<"MB";
		cout<<"\nFree RAM is :"<<free_RAM<<"MB";
		cout<<"\nUsed RAM is :"<<used_RAM<<"MB";
	}
	else{
		cout<<"\nOoops   ERROR !!";
	}

	cout<<endl;
	return 0;
}
