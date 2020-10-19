#include<iostream>
#include<iomanip>

using namespace std;

struct ProcessRR
{
    int pid;
    int arv_t;
    int burst_t;
    int response_t;
    int start_t;
    int remBurst_t;
    int complete_t;
    int wait_t;
    int turnar_t;
};

class Scheduling{
ProcessRR *P;
int n,k=0,t_quantum;
int gantt_t[50],gantt_p[50];
float TotTAT, TotWT, AvgTAT, AvgWT;
public:
Scheduling(){
TotTAT=0.0;
TotWT=0.0;
AvgTAT=0.0;
AvgWT=0.0;
}
void Getdata();
void RR();
void Showdata();
void Sort_arvt();
};


void Scheduling::Getdata(){
cout<<endl;
cout<<"Enter the number of processes: ";
cin>>n;
P=new ProcessRR[n];
for(int i=0;i<n;i++){
P[i].pid=i+1;
}
cout<<endl;
for(int i=0;i<n;i++){
cout<<"Enter the Arrival Time of Process "<<i+1<<": ";
cin>>P[i].arv_t;
}
cout<<endl;
for(int i=0;i<n;i++){
cout<<"Enter the Burst Time of Process "<<i+1<<": ";
cin>>P[i].burst_t;
P[i].remBurst_t=P[i].burst_t;
}
cout<<endl;
cout<<"\nEnter the time quantum for the Round robin\n";
cin>>t_quantum;
Sort_arvt();
}


void Scheduling::Sort_arvt(){
ProcessRR temp;
for(int i=0;i<n-1;i++){
for(int j=n-1;j>i;j--)
if(P[j].arv_t<P[j-1].arv_t)
    {
    temp=P[j];
    P[j]=P[j-1];
    P[j-1]=temp;
    }
 }
}

void Scheduling::RR(){
int current_t=0,counter=0,flag=0,sum=0,temp_pid=0;
gantt_t[k]=0;
current_t=P[0].arv_t;
while(counter<n){
for(int i=0;i<n;i++){
if(sum==0)
temp_pid=P[0].pid;

if(P[i].arv_t>current_t and counter!=i)
break;
else if(P[i].arv_t>current_t and counter==i){
flag=P[i].arv_t-current_t;

current_t=P[i].arv_t;}
if(P[i].remBurst_t==0)
continue;
if(P[i].remBurst_t==P[i].burst_t){
P[i].start_t=current_t;
P[i].response_t=P[i].start_t-P[i].arv_t;}
if(P[i].pid!=temp_pid){
gantt_p[k]=temp_pid;
gantt_t[k]=sum;
sum=0;
k++;}
if(flag){
gantt_t[k]=flag;
gantt_p[k]=0;
k++;
flag=0;}
temp_pid=P[i].pid;
if(P[i].remBurst_t>t_quantum){
current_t+=t_quantum;
sum+=t_quantum;
P[i].remBurst_t-=t_quantum;}
else if(P[i].remBurst_t<=t_quantum){
current_t+=P[i].remBurst_t;
sum+=P[i].remBurst_t;
P[i].remBurst_t=0;
counter++;
P[i].complete_t=current_t;
P[i].turnar_t=P[i].complete_t-P[i].arv_t;
P[i].wait_t=P[i].turnar_t-P[i].burst_t;
current_t=P[i].complete_t;
TotWT=TotWT+P[i].wait_t;
TotTAT=TotTAT+P[i].turnar_t;
}
}
}
gantt_p[k]=temp_pid;
gantt_t[k++]=sum;
AvgWT= TotWT/n;
AvgTAT=TotTAT/n;
}
void Scheduling::Showdata(){
cout<<endl<<"OUTPUT : \n\n";
cout<<setw(5)<<"PID"<<setw(15)<<"Arrival Time"<<setw(15)<<"BurstTime"<<setw(15)<<"Waiting Time"<<setw(20)<<"TurnaroundTime"<<setw(10)<<"RT"<<endl<<endl;
for(int i=0;i<n;i++){
cout<<setw(5)<<P[i].pid<<setw(15)<<P[i].arv_t<<setw(15)<<P[i].burst_t<<setw(15)<<P[i].wait_t
<<setw(20)<<P[i].turnar_t<<setw(10)<<P[i].response_t<<endl;
}
cout<<"\n\n ~~~~~~~~~~GANTT CHART ~~~~~~~~~~ \n\n ";
int x=0;
for(int i=0;i<k;i++){
int temp=gantt_t[i];
if(temp==1)cout<<" ";
while(temp-->0)
cout<<"*";
cout<<" ";
}
cout<<"\n |";
for(int i=0;i<k;i++){
int temp=gantt_t[i];
cout<<setw(temp-1)<<"P"<<gantt_p[i];
cout<<"|";}
cout<<"\n ";
for(int i=0;i<k;i++){
int temp=gantt_t[i];
if(temp==1)cout<<" ";
while(temp-->0)
cout<<"*";
cout<<" ";}
cout<<"\n 0 ";
x=0;
for(int i=0;i<k;i++){
int temp=gantt_t[i];
if(temp==1)cout<<" ";
cout<<setw(temp)<<x+temp<<" ";
x=x+temp;}
cout<<endl;
cout<<"\n[NOTE:- IDLE CPU IS SHOWN BY P0]\n";
cout<<"\nAverage Waiting Time = "<<AvgWT;
cout<<"\nAverage Turnaround Time = "<<AvgTAT<<endl<<endl;
}

int main()
{
cout<<" ******* PROGRAM TO IMPLEMENT ROUND ROBIN ALGORITHM *******\n";
Scheduling rr;
rr.Getdata();
rr.RR();
rr.Showdata();

return 0;
}


