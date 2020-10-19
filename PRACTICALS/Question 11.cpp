
#include<iostream>
#include<iomanip>

using namespace std;


struct Process{
        int pid;
        int arv_t;
        int burst_t;
        int response_t;
        int start_t;
        int temp_start;
        int temp_complete;
        int remBurst_t;
        int complete_t;
        int wait_t;
        int turnar_t;
};
class Scheduling{
         Process *P;
        int n,k=0;
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
                void srjf();
                void Showdata();
                void Sort_arvt();
                void Sort_RemBurst(int,int);
};


void Scheduling::Getdata(){
        cout<<endl;
        cout<<"Enter the number of processes: ";
        cin>>n;
        P=new Process[n];

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
        Sort_arvt();
}


// for sorting the arrival time
void Scheduling::Sort_arvt(){
 Process temp;
        for(int i=0;i<n-1;i++){
                for(int j=n-1;j>i;j--)
                        if(P[j].arv_t<P[j-1].arv_t){
                                temp=P[j];
                                P[j]=P[j-1];
                                P[j-1]=temp;
                        }
        }
}


//for sorting remaining burst time
void Scheduling::Sort_RemBurst(int r, int s ){
 Process temp;
        for(int i=r;i<s-1;i++){
                for(int j=s-1;j>i;j--)
                        if(P[j].remBurst_t<P[j-1].remBurst_t){
                                temp=P[j];
                                P[j]=P[j-1];
                                P[j-1]=temp;
                        }
        }
}


//
void Scheduling::srjf(){
  int current_t=0,i=0,sum=0,temp_pid=0;
  gantt_t[k]=0;
                  while(i<n){
                          int j=i;
                          while(j<n){
                           if(P[j].arv_t>current_t){
                                   break;}
                                   j++;
                           }
                              Sort_RemBurst(i,j);
                              if(sum==0)
                              temp_pid=P[0].pid;
                              if(P[i].pid!=temp_pid){

                                      gantt_p[k]=temp_pid;
                                      gantt_t[k]=sum;
                                      sum=0;// for counting the time upto which one process occupied the CPU
                                      k++;
                                  }
                              if(P[i].remBurst_t==P[i].burst_t){
                                    P[i].response_t=current_t;
                                           if(current_t<P[i].arv_t){
                                           //assign the time period for gantt chart when CPU is idle
                                           gantt_t[k]=P[i].arv_t-current_t;
                                           gantt_p[k]=0;
                                           k++;
                                           //
                          current_t=P[i].arv_t;}
                                    P[i].start_t=current_t;
                           }
                           P[i].remBurst_t--;
                           current_t++;
                           sum++;
                           temp_pid=P[i].pid;
                           if(P[i].remBurst_t==0){
                             P[i].complete_t=current_t;
                                 P[i].turnar_t=P[i].complete_t-P[i].arv_t;
                                P[i].wait_t=P[i].turnar_t-P[i].burst_t;
                             current_t=P[i].complete_t;
                                 TotWT=TotWT+P[i].wait_t;
                                 TotTAT=TotTAT+P[i].turnar_t;
                         i++;
                                }

        }
        gantt_p[k]=temp_pid;
        gantt_t[k++]=sum;
        AvgWT= TotWT/n;
        AvgTAT=TotTAT/n;
}



void Scheduling::Showdata(){
        cout<<endl<<"OUTPUT : \n\n";
        cout<<setw(5)<<"PID"<<setw(15)<<"Arrival Time"<<setw(15)<<"Burst Time"<<setw(15)<<"Waiting Time"<<setw(20)<<"Turnaround Time"<<setw(10)<<"RT"<<endl<<endl;
        for(int i=0;i<n;i++){
                cout<<setw(5)<<P[i].pid<<setw(15)<<P[i].arv_t<<setw(15)<<P[i].burst_t<<setw(15)<<P[i].wait_t<<setw(20)<<P[i].turnar_t<<setw(10)<<P[i].response_t<<endl;
        }


        cout<<"\n\n      ~~~~~~~~~~GANTT CHART ~~~~~~~~~~  \n\n   ";
int x=0;
        for(int i=0;i<k;i++){
                int temp=gantt_t[i];
                if(temp==1)cout<<" ";
                 while(temp-->0)
                 cout<<"*";
                 cout<<" ";
           }
                   cout<<"\n  |";
           for(int i=0;i<k;i++){
                int temp=gantt_t[i];
                cout<<setw(temp-1)<<"P"<<gantt_p[i];
                cout<<"|";}
                cout<<"\n   ";
                for(int i=0;i<k;i++){
            int temp=gantt_t[i];
                        if(temp==1)cout<<" ";
                while(temp-->0)
                cout<<"*";
                cout<<" ";}
                cout<<"\n  0 ";
                   x=0;
           for(int i=0;i<k;i++){
                int temp=gantt_t[i];
                        if(temp==1)cout<<" ";
                cout<<setw(temp)<<x+temp<<" ";
                x=x+temp;}
                cout<<endl;

        cout<<"\nAverage Waiting Time = "<<AvgWT;
        cout<<"\nAverage Turnaround Time = "<<AvgTAT<<endl<<endl;
}


int main(){
        cout<<" ******* Program for SRJF ALGORITHM *******\n";
        Scheduling Obj;
        Obj.Getdata();
        Obj.srjf();
        Obj.Showdata();
        return 0;
}
/*






TEST CASE1:


 ******* Program for SRJF ALGORITHM *******


Enter the number of processes: 4


Enter the Arrival Time of Process 1: 0
Enter the Arrival Time of Process 2: 1
Enter the Arrival Time of Process 3: 2
Enter the Arrival Time of Process 4: 3


Enter the Burst Time of Process 1: 8
Enter the Burst Time of Process 2: 4
Enter the Burst Time of Process 3: 6
Enter the Burst Time of Process 4: 2




OUTPUT :


  PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time        RT


    2              1              4              0                   4         1
    4              3              2              2                   4         5
    3              2              6              5                  11         7
    1              0              8             12                  20         0




      ~~~~~~~~~~GANTT CHART ~~~~~~~~~~


    * **** ** ****** *******
  |P1|  P2|P4|    P3|     P1|
    * **** ** ****** *******
  0  1    5  7     13      20



Average Waiting Time = 4.75
Average Turnaround Time = 9.75


TEST CASE 2:
 ******* Program for SRJF ALGORITHM *******

Enter the number of processes: 4

Enter the Arrival Time of Process 1: 0
Enter the Arrival Time of Process 2: 0
Enter the Arrival Time of Process 3: 0
Enter the Arrival Time of Process 4: 0

Enter the Burst Time of Process 1: 8
Enter the Burst Time of Process 2: 4
Enter the Burst Time of Process 3: 6
Enter the Burst Time of Process 4: 2


OUTPUT :

  PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time        RT

    4              0              2              0                   2         0
    2              0              4              2                   6         2
    3              0              6              6                  12         6
    1              0              8             12                  20        12


      ~~~~~~~~~~GANTT CHART ~~~~~~~~~~

   ** **** ****** ********
  |P4|  P2|    P3|      P1|
   ** **** ****** ********
  0  2    6     12       20

Average Waiting Time = 5
Average Turnaround Time = 10

TEST CASE3:
 ******* Program for SRJF ALGORITHM *******

Enter the number of processes: 5

Enter the Arrival Time of Process 1: 1
Enter the Arrival Time of Process 2: 5
Enter the Arrival Time of Process 3: 9
Enter the Arrival Time of Process 4: 6
Enter the Arrival Time of Process 5: 4

Enter the Burst Time of Process 1: 2
Enter the Burst Time of Process 2: 4
Enter the Burst Time of Process 3: 2
Enter the Burst Time of Process 4: 5
Enter the Burst Time of Process 5: 8


OUTPUT :

  PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time        RT

    1              1              2              0                   2         0
    2              5              4              0                   4         5
    3              9              2              0                   2         9
    4              6              5              5                  10        11
    5              4              8             11                  19         3


      ~~~~~~~~~~GANTT CHART ~~~~~~~~~~

    * **  *  * **** ** ***** *******
  |P0|P1|P0|P5|  P2|P3|   P4|     P5|
    * **  *  * **** ** ***** *******
  0  1  3  4  5    9 11    16      23

Average Waiting Time = 3.2
Average Turnaround Time = 7.4
 */
