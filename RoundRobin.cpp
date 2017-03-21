#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

struct process
{
	string name;
	int arrival;
	int burst;
	int originalBurst;
};
struct timeSlote{
	int start;
	int end;
	process p;
};
void printProcess(process p)		//print the process struct in a special formate
{
	cout<<"======================"<<endl;
	cout<<"Process name: "<<p.name<<endl;
	cout<<"Process arrival time: "<<p.arrival<<endl;
	cout<<"Process burst time: "<<p.burst<<endl;
	// cout<<"Process periourty"<<p.per<<endl;
	cout<<"======================"<<endl;
}
void printAllProcess(vector<process> p)
{
	for( int i=0; i< p.size(); i++)
		printProcess( p.at(i) );
}
void printSlot(timeSlote s)
{
	cout<<"|"<<s.start<<"==";
	cout<<"["<<s.p.name<<"]==";
	cout<<s.end<<"|";
}
void printAllSlots(vector<timeSlote> t)
{
	cout<<endl;
	for(int i=0;i<t.size();i++)
		printSlot(t.at(i));
	cout<<endl;
}
void writeTimeSlote(vector<timeSlote> v, string fileName)   //save the contents of the vector of timeSlots in a new file with name "fileName"
{
	ofstream outfile;
	outfile.open(fileName);
	timeSlote s;
	for(int i=0;i<v.size();i++)
	{
		s = v.at(i);
		outfile<<"================="<<endl;
		outfile<<"start at time: "<<s.start<<endl;
		outfile<<s.p.name<<endl;
		outfile<<"End at time: "<<s.end<<endl;
		outfile<<"================="<<endl;
	}
	outfile.close();
}
process parseProcess(string s)				//parse the given string s to find the process information 
{
	process p;
	stringstream lineStream;
	lineStream.str(s);
	string item;
	getline(lineStream,item,'$');
	p.name = item;
	getline(lineStream,item,'$');
	p.arrival = stoi(item);
	getline(lineStream,item,'$');
	p.burst = stoi(item);
	// getline(lineStream,item,'$');
	// p.per = stoi(item);
	p.originalBurst = p.burst;
	return p;
}
vector<process> readProcess(string fileName)
{
	vector<process> v;
	ifstream infile(fileName);
	string line;
	while(getline(infile,line))
	{
		static int c = 1;
		process p = parseProcess(line);
		v.push_back(p);
		cout<<"====readProcess== "<< c <<" ====done========"<<endl;
		c ++;
	}
	return v;
}

vector<int> order;      // our queue to handle entry point or process

bool searchinorder(int data){ 	 // block repeated process
	for(int i=0 ; i < order.size() ; i++)
		if(order.at(i)==data)  // used for guarantee our entry point is not repeated
			return true;
	return false;
}

bool ordersearch(vector<process> process, int time){ // check for new process at current Time without storing
	for(int i=0; i < process.size() ; i++ )
		if(process.at(i).arrival < time)
			if(!searchinorder(i) && process.at(i).burst > 0)
				return true;
	return false;
}

void orderf(vector<process> process, int time){ //check for new process at current Time
	for(int i=0; i < process.size() ; i++ )
		if(process.at(i).arrival <= time)
			if(!searchinorder(i) && process.at(i).burst > 0)
				order.push_back(i); 	 //store position of process
}

bool continuee(vector<process> process){  //check for process and send true if 'single' process still need to processed
	for(int i=0; i< process.size(); i++)
		if(process.at(i).burst > 0)
			return true;
	return false;
}

int quantumtime = 3;
int totalTurn = 0;
int totalWait = 0;

vector<timeSlote> RR(vector<process> v)
{
	vector<timeSlote> t;
	timeSlote ts;
	int currentTime = 0;
	int turn,wait;
  
	while(continuee(v)){

		orderf(v,currentTime); 	//arrangement of process

		ts.start = currentTime;  

	  	//check if we have process in queue
		if(!order.empty())      //if there a process or idle
			ts.p = v.at(order.at(0));
		else {    //idle
			
			bool found = false;     
			int foundtime = currentTime;
			        //use current time as start to found next and less arrival time 
			while(!found){
				for(int i = 0 ; i < v.size(); i++){
					if(v.at(i).arrival == foundtime && v.at(i).burst > 0){
						order.push_back(i); 	//store position of next process
						found = true;
					}
				}
				foundtime++; //still looping until found next process 
				currentTime = foundtime-1; // -1 is for last ++ !!! :(())
			}

			//after we determine next process

			process p = {"idle"};  //we creating a new process called idle
			ts.p = p; // assign it to time slot 
			ts.end = currentTime; //put time as we found from search !

			t.push_back(ts); // push whole TS to our vector 
			continue;
		}

		
		if(ts.p.burst > quantumtime){           // case burst > Q 
		
			ts.p.burst -= quantumtime;  
			v.at(order.at(0)).burst -= quantumtime;       //decrement time from original process {important for calculation}
			currentTime += quantumtime;            // increment time after round 
			ts.end = currentTime;

			if(ordersearch(v,currentTime))	// check for new process at current Time
				orderf(v,currentTime); 	    // add new process we found at current Time

			order.push_back(order.at(0));   // put our process again in queue
		
		}else {  // case burst <= Q 

			currentTime += ts.p.burst;
			ts.p.burst = 0;
			v.at(order.at(0)).burst = 0;      //decrement time from original process {important for calculation}
			ts.end = currentTime;
			orderf(v,currentTime);  // check for new process at currentTime

			        //this part of time calculation will not executed until process totally finished
			turn = ts.end - ts.p.arrival;       //turn arround time 
			wait = turn - ts.p.originalBurst;       //waiting time 
			totalTurn += turn;        //total turn !!
			totalWait += wait;        //total waiting !

		}

		order.erase(order.begin()); //delete process we calculated from queue 
		t.push_back(ts);	// put the whole time slot we processed in vector 
	}

	return t;
}
int main(int argc,char *argv[])		//it takes two arguments 1:inputFile name, 2:outputFile name
{
	
	vector<process> v = readProcess(argv[1]);

	int processNumber = v.size();
	printAllProcess(v);

	cout << "\nEnter quantum time : ";
	cin >> quantumtime ;

	vector<timeSlote> t = RR(v);      //call Round Robin algorithm
  
	printAllSlots(t);
	writeTimeSlote(t,argv[2]);

	cout<<"Average Turn Time = "<<(float)totalTurn/processNumber<<endl;
	cout<<"Average WaitingTime = "<<(float)totalWait/processNumber<<endl;
	return 0;
}
