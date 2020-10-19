#include<iostream>
#include<iomanip>
using namespace std;

struct Process{
	int pid;
	int arrival_time;
	int burst_time;

	int response_time;
	int wait_time;
	int turnaround_time;

	int start_time;
	int complete_time;
};

class SchedulingAlgorithm{
	double total_wait_time, total_turnaround_time, total_response_time, average_wait_time, average_turnaround_time, average_response_time ;
	int number_of_process;
	Process * process;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0;
			average_wait_time=0;
			average_turnaround_time = 0;
			total_response_time=0;
			average_response_time = 0;

		}
		void input();
		void FCFS();
		void output();
		void sort_arrival_time();
};

void SchedulingAlgorithm::input(){
	cout<<"Enter number of processes :";
	cin>>number_of_process;
	process = new Process[number_of_process];

	for(int i=0;i<number_of_process;i++){
		cout<<"\n\nEnter details for process "<<i+1;
		cout<<"\n\t1. Enter PID :";
		cin>>process[i].pid;
		cout<<"\t2. Enter Arrival Time :";
		cin>>process[i].arrival_time;
		cout<<"\t3. Enter Burst Time :";
		cin>>process[i].burst_time;
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
			Process temp=process[min];
			process[min]=process[i];
			process[i]=temp;
		}
	}
}

void SchedulingAlgorithm::FCFS(){

		process[0].start_time = process[0].arrival_time;
		process[0].complete_time = process[0].arrival_time + process[0].burst_time;

		//wait time for first process
		process[0].wait_time = 0;
		//turnaround time for first process
		process[0].turnaround_time = process[0].burst_time;


		//calculate wait time, turnaround time and response time for rest processes
		for(int i=1;i<number_of_process;i++){
			//for wait time
			process[i].wait_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time - process[i].arrival_time ;
			if(process[i].wait_time<0)
				process[i].wait_time=0;



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

			//turnaround time
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

		average_wait_time = total_wait_time/number_of_process;
        average_turnaround_time = total_turnaround_time/number_of_process;
		average_response_time = total_response_time/number_of_process;
	}



void SchedulingAlgorithm::output(){

	cout<<"\n\n  =====================================================================================";
		cout<<"\n   "<<"   PID"<<"   ArrivalTime"<<"   BurstTime"<<"   Wait time"<<"   Turnaround time"<<"     Response Time";
		cout<<"\n   -----------------------------------------------------------------------------------";
	for(int i=0;i<number_of_process;i++){
		cout<<"\n   "<<setw(5)<<process[i].pid<<setw(9)<<process[i].arrival_time<<setw(14)<<process[i].burst_time<<setw(12)<<process[i].wait_time<<setw(14)<<process[i].turnaround_time<<setw(18)<<process[i].response_time;
	}
	cout<<"\n  =====================================================================================";


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
	obj.FCFS();
	obj.output();
	return 0;
}
