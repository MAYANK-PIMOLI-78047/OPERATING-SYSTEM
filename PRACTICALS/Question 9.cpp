#include<iostream>
#include<iomanip>
using namespace std;

struct ProcessDetail{
	int pid;
	int arrival_time;
	int burst_time;
	int priority;

	int response_time;
	int wait_time;
	int turnaround_time;

	int start_time;
	int complete_time;
};


class SchedulingAlgorithm{
	double total_wait_time, total_turnaround_time, total_response_time, average_wait_time, average_turnaround_time, average_response_time ;
	int number_of_process, current_time;
	ProcessDetail * process;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0;
			average_wait_time=0;
			average_turnaround_time = 0;
			total_response_time=0;
			average_response_time = 0;
			 current_time=0;

		}
		void input();
		void priority();
		void output();
		void sort_arrival_time();
		void assign_queue();
		void sort_priority(int start,int end);
};


void SchedulingAlgorithm::input(){
	cout<<"\nEnter number of processes :";
	cin>>number_of_process;
	process = new ProcessDetail[number_of_process];


	for(int i=0;i<number_of_process;i++){
		cout<<"\n\nEnter details for process "<<i+1;
		process[i].pid = i+1;
		cout<<"\n\t1. PID :"<<process[i].pid;
		cout<<"\n\t2. Enter Arrival Time :";
		cin>>process[i].arrival_time;
		cout<<"\t3. Enter Burst Time :";
		cin>>process[i].burst_time;
		cout<<"\t4. Enter Priority :";
		cin>>process[i].priority;

	}
}


void SchedulingAlgorithm::sort_arrival_time(){
	for(int i=0;i<number_of_process-1;i++){
		int min = i;
		for(int j=i+1;j<number_of_process;j++){
			if(process[j].arrival_time<process[min].arrival_time)
				min=j;
		}

		if(process[min].arrival_time!=process[i].arrival_time)
		{
			ProcessDetail temp=process[min];
			process[min]=process[i];
			process[i]=temp;
		}
	}
}


void SchedulingAlgorithm::sort_priority(int start, int end){

	{
			for(int i=start;i<end-1;i++){
			int min = i;
			for(int j=i+1;j<end;j++){
				if(process[j].priority<process[min].priority)
					min=j;
			}
			if(process[min].priority!=process[i].priority)
			{
				ProcessDetail temp=process[min];
				process[min]=process[i];
				process[i]=temp;
			}
		}
	}


}


void SchedulingAlgorithm::assign_queue(){
	int i=0;
	int t=0;
	current_time=process[0].arrival_time;
	for(t=0;t<number_of_process;t++){
		i=t;
		while(process[i].arrival_time <= current_time && i<number_of_process){
			i++;
		}
		sort_priority(t, i);

		current_time = current_time+process[t].burst_time;
	}
}


void SchedulingAlgorithm::priority(){

		//for visual representation
		process[0].start_time = process[0].arrival_time;
		process[0].complete_time = process[0].arrival_time + process[0].burst_time;

		//wait time for first process
		process[0].wait_time = 0;
		//turnaround time for first process
		process[0].turnaround_time = process[0].burst_time;


		//calculate wait time, turnaroundtime and response time for rest processes
		for(int i=1;i<number_of_process;i++){
			//for wait time
			process[i].wait_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time - process[i].arrival_time ;
			if(process[i].wait_time<0)
				process[i].wait_time=0;


			//for visual representation
			process[i].start_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time ;
			process[i].complete_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time + process[i].burst_time;

			if((process[i].arrival_time - process[i-1].complete_time) > 0){
				process[i].start_time += process[i].arrival_time - process[i-1].complete_time;
				process[i].complete_time += process[i].arrival_time - process[i-1].complete_time;
			}
			else{
				process[i].start_time+=0;
				process[i].complete_time+=0;
			}

			//for turnaround time
			process[i].turnaround_time = process[i].complete_time - process[i].arrival_time ;

		}

		//response time
		for(int i=0;i<number_of_process;i++){
			process[i].response_time = process[i].start_time - process[i].arrival_time;
		}

		//total wait, turnaround and response time
		for(int i=0;i<number_of_process;i++){
			total_wait_time += process[i].wait_time;
			total_turnaround_time += process[i].turnaround_time;
			total_response_time += process[i].response_time;
		}

		//average wait time
		average_wait_time = total_wait_time/number_of_process;

		//average turnaround time
		average_turnaround_time = total_turnaround_time/number_of_process;

		//average response time
		average_response_time = total_response_time/number_of_process;
}




void SchedulingAlgorithm::output(){

	cout<<"\n\n  ===============================================================================================";
		cout<<"\n   "<<"   PID"<<"   ArrivalTime"<<"   BurstTime"<<"	Priority"<<"   Wait time"<<"   Turnaround time"<<"     Response Time";
		cout<<"\n   -----------------------------------------------------------------------------------------------";
	for(int i=0;i<number_of_process;i++){
		cout<<"\n   "<<setw(5)<<process[i].pid<<setw(9)<<process[i].arrival_time<<setw(14)<<process[i].burst_time<<setw(13)<<process[i].priority<<setw(12)<<process[i].wait_time<<setw(14)<<process[i].turnaround_time<<setw(18)<<process[i].response_time;
	}
	cout<<"\n  ===============================================================================================";


	cout<<"\n\n\nGANTT CHART :\n";

		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"------------  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|          |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|    "<<process[k].pid<<"     |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|          |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"------------  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
				cout<<process[k].start_time<<setw(11)<<process[k].complete_time<<setw(3);
		}



	cout<<"\n\nTotal Wait Time :"<<total_wait_time;
	cout<<"\nAverage Wait Time :"<<average_wait_time;
	cout<<"\n\nTotal Turnaround Time :"<<total_turnaround_time;
	cout<<"\nAverage Turnaround Time :"<<average_turnaround_time;
	cout<<"\n\nTotal Response Time :"<<total_response_time;
	cout<<"\nAverage Response Time :"<<average_response_time;
}


int main(){
	SchedulingAlgorithm obj;
	obj.input();
	obj.sort_arrival_time();
	obj.assign_queue();
	obj.priority();
	obj.output();
	return 0;
}


/*

Test Case 1:


Enter number of processes :5


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :0
        3. Enter Burst Time :10
        4. Enter Priority :3


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :0
        3. Enter Burst Time :1
        4. Enter Priority :1


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :0
        3. Enter Burst Time :2
        4. Enter Priority :4


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :0
        3. Enter Burst Time :1
        4. Enter Priority :5


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :0
        3. Enter Burst Time :5
        4. Enter Priority :2


  ===============================================================================================
      PID   ArrivalTime   BurstTime     Priority   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------------------
       2        0             1            1           0             1                 0
       5        0             5            2           1             6                 1
       1        0            10            3           6            16                 6
       3        0             2            4          16            18                16
       4        0             1            5          18            19                18
  ===============================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |
|    2     |  |    5     |  |    1     |  |    3     |  |    4     |
|          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------
0          1  1          6  6         16 16         18 18         19

Total Wait Time :41
Average Wait Time :8.2

Total Turnaround Time :60
Average Turnaround Time :12

Total Response Time :41
Average Response Time :8.2


============================================================================================================================


Test Case 2 :



Enter number of processes :5


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :2
        3. Enter Burst Time :5
        4. Enter Priority :1


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :4
        3. Enter Burst Time :2
        4. Enter Priority :1


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :6
        3. Enter Burst Time :1
        4. Enter Priority :3


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :0
        3. Enter Burst Time :6
        4. Enter Priority :4


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :12
        3. Enter Burst Time :5
        4. Enter Priority :2


  ===============================================================================================
      PID   ArrivalTime   BurstTime     Priority   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------------------
       4        0             6            4           0             6                 0
       1        2             5            1           4             9                 4
       2        4             2            1           7             9                 7
       5       12             5            2           1             6                 1
       3        6             1            3          12            13                12
  ===============================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |
|    4     |  |    1     |  |    2     |  |    5     |  |    3     |
|          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------
0          6  6         11 11         13 13         18 18         19

Total Wait Time :24
Average Wait Time :4.8

Total Turnaround Time :43
Average Turnaround Time :8.6

Total Response Time :24
Average Response Time :4.8


==============================================================================================================

Test Case 3:


Enter number of processes :5


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :2
        3. Enter Burst Time :5
        4. Enter Priority :2


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :4
        3. Enter Burst Time :2
        4. Enter Priority :3


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :6
        3. Enter Burst Time :1
        4. Enter Priority :1


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :12
        3. Enter Burst Time :5
        4. Enter Priority :5


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :13
        3. Enter Burst Time :6
        4. Enter Priority :4


  ===============================================================================================
      PID   ArrivalTime   BurstTime     Priority   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------------------
       1        2             5            2           0             5                 0
       3        6             1            1           1             2                 1
       2        4             2            3           4             6                 4
       4       12             5            5           0             5                 0
       5       13             6            4           4            10                 4
  ===============================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |
|    1     |  |    3     |  |    2     |  |    4     |  |    5     |
|          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------
2          7  7          8  8         10 12         17 17         23

Total Wait Time :9
Average Wait Time :1.8

Total Turnaround Time :28
Average Turnaround Time :5.6

Total Response Time :9
Average Response Time :1.8


*/

