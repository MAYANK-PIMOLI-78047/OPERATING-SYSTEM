#include<iostream>
#include<iomanip>
using namespace std;

struct ProcessDetail{
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
		void sort_arrival_time();
		void assign_queue();
		void sort_burst_time(ProcessDetail process[],int size);
        void SJF();
		void output();
};

void SchedulingAlgorithm::input(){
	cout<<"Enter number of processes :";
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

void SchedulingAlgorithm::sort_burst_time(ProcessDetail  P[], int size){
	for(int i=0;i<size-1;i++){
		int min = i;
		for(int j=i+1;j<size;j++){
			if(P[j].arrival_time<P[min].arrival_time)
				min=j;
		}

		if(P[min].arrival_time!=P[i].arrival_time)
		{
			ProcessDetail temp=P[min];
			P[min]=P[i];
			P[i]=temp;
		}
	}
}

void SchedulingAlgorithm::assign_queue(){
	int i=0,j;
	int t=0;
	ProcessDetail temp[number_of_process];
	for(t=0;t<number_of_process;t++){
		i=t;
		while(process[i].arrival_time<=current_time){
		j=0;
		temp[j] = process[i];
		j++;
		i++;
	}
		if(j>0)
			sort_burst_time(temp, j);
		current_time = process[t].burst_time;
	}


}
void SchedulingAlgorithm::SJF(){


		process[0].start_time = process[0].arrival_time;
		process[0].complete_time = process[0].arrival_time + process[0].burst_time;


		process[0].wait_time = 0;

		process[0].turnaround_time = process[0].burst_time;



		for(int i=1;i<number_of_process;i++){

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


			process[i].turnaround_time = process[i].complete_time - process[i].arrival_time ;

		}


		for(int i=0;i<number_of_process;i++){
			process[i].response_time = process[i].start_time - process[i].arrival_time;
		}


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
	obj.assign_queue();
	obj.SJF();
	obj.output();
	return 0;
}

