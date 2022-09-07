#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <getopt.h>

using namespace std;

//randomizer declaration
random_device seed;
mt19937 engine(seed());
uniform_int_distribution<int> dist(1,10);

string proc_split[3];

//struct defining common info for a process
struct Process {
  string proc_name;
  int start_time;
  int duration;
  int durTicks = 0;
  int waitTicks = 0;
  bool ready = false;
  bool done = false;
  int completedTime = 0;
};


deque<Process*> procQ;
double procInUse = 0;
double slice = 0;

bool byStartTime(Process* a, Process* b)
{
  return a->start_time < b->start_time;
}

bool byDuration(Process* a, Process* b)
{
  return a->duration < b->duration;
}

bool byRR(Process* a, Process* b)
{
  int aRR = (a->waitTicks + a->duration) / a->duration;
  int bRR = (b->waitTicks + b->duration) / b->duration;
  if(aRR > bRR)
  {
	return true;
  }
  else {
	return false;
  }
}

void addToDeque(Process list[], int size)
{
  int start_times[size];
  int durations[size];
  for(int i = 0; i < size; ++i)
  {
	procQ.push_back(&list[i]);
	start_times[i] = procQ[i]->start_time;
	durations[i] = procQ[i]->duration;
  }
  for(int i = 0; i < size; ++i)
  {
	cout << "[" << procQ[i]->proc_name << ":(" << procQ[i]->start_time << "," << procQ[i]->duration << ")" << endl;
  }
  return;
}

void getStats(double slice, double size, double procInUse, Process list[])
{
  //makespan
  int makespan = slice;
  double avg = 0;
  int total = 0;
  double util = 0;

  for(int i = 0; i < size; ++i)
  {
	total = total + list[i].completedTime; //total time
	avg = avg + list[i].waitTicks; //avg waiting time
  }
  util = procInUse / slice;
  avg = avg / size;
  double throughput = size / slice; //throughput

  cout << "Makespan: " << makespan << endl;
  cout << "Average Waiting Time: " << avg << endl;
  cout << "Throughput: " << throughput << endl;
  cout << "Sum of Completion Times: " << total << endl;
  cout << "Utilization: " << util << endl;
}



void HRRN(Process list[], int size)
{
  cout << "\n";
  addToDeque(list, size);
  deque<Process*> readyQ;
  sort(procQ.begin(), procQ.end(), byStartTime);
  Process* CPU = NULL;
  while(!procQ.empty())
  {
	cout << slice << "	";
	for(int j = 0; j < size; ++j)
	{
	  if(list[j].start_time == slice)
	  {
		cout << " S ";
		readyQ.push_back(&list[j]);
		sort(readyQ.begin(), readyQ.end(), byRR);
		list[j].ready = true;
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}	
	  }
	  else if(list[j].start_time < slice && CPU == &list[j])
	  {
		cout << " X ";
		++list[j].durTicks;
		++procInUse;
		if(list[j].durTicks == list[j].duration) {
		  CPU = NULL;
		  list[j].ready = false;
		  list[j].done = true;
		  list[j].completedTime = slice;
		  procQ.pop_front();
		}

	  }
	  else if(list[j].start_time < slice && CPU != &list[j])
	  {
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}
		if(list[j].done) {
		  cout << "   ";
		}
		else
		{
		  cout << " | ";
		  ++list[j].waitTicks;
		}


	  }
	  else
	  {
		if(slice < list[j].start_time)
		{
		  cout << " . ";
		}
		else {
		  cout << "   ";
		}

	  }
	}
	cout << "\n";
	++slice;
  }
}



void SJR(Process list[], int size)
{
  cout << "\n";
  addToDeque(list, size);
  deque<Process*> readyQ;
  sort(procQ.begin(), procQ.end(), byStartTime);
  Process* CPU = NULL;
  while(!procQ.empty())
  {
	cout << slice << "	";
	for(int j = 0; j < size; ++j)
	{
	  if(list[j].start_time == slice)
	  {
		cout << " S ";
		list[j].ready = true;
		if(CPU != NULL) {
		  readyQ.push_back(CPU);
		  CPU = NULL;
		  readyQ.push_back(&list[j]);
		  sort(readyQ.begin(), readyQ.end(), byDuration);
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}
		if(CPU == NULL && list[j].ready)
		{
		  readyQ.push_back(&list[j]);
		  sort(readyQ.begin(), readyQ.end(), byDuration);
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}	
	  }
	  else if(list[j].start_time < slice && CPU == &list[j])
	  {
		cout << " X ";
		++list[j].durTicks;
		++procInUse;
		if(list[j].durTicks == list[j].duration) {
		  CPU = NULL;
		  list[j].ready = false;
		  list[j].done = true;
		  list[j].completedTime = slice;
		  procQ.pop_front();
		}

	  }
	  else if(list[j].start_time < slice && CPU != &list[j])
	  {
		if(CPU == NULL && list[j].ready)
		{
		  sort(readyQ.begin(), readyQ.end(), byDuration);
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}
		if(list[j].done) {
		  cout << "   ";
		}
		else
		{
		  cout << " | ";
		  ++list[j].waitTicks;
		}


	  }
	  else
	  {
		if(slice < list[j].start_time)
		{
		  cout << " . ";
		}
		else {
		  cout << "   ";
		}

	  }
	}
	//if(CPU != NULL && CPU->duration == CPU->durTicks) {
	//	CPU = NULL;
	//}
	cout << "\n";
	++slice;
  }
}

void SJF(Process list[], int size)
{
  cout << "\n";
  addToDeque(list, size);
  deque<Process*> readyQ;
  sort(procQ.begin(), procQ.end(), byStartTime);
  Process* CPU = NULL;
  while(!procQ.empty())
  {
	cout << slice << "	";
	for(int j = 0; j < size; ++j)
	{
	  if(list[j].start_time == slice)
	  {
		cout << " S ";
		readyQ.push_back(&list[j]);
		sort(readyQ.begin(), readyQ.end(), byDuration);
		list[j].ready = true;
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}	
	  }
	  else if(list[j].start_time < slice && CPU == &list[j])
	  {
		cout << " X ";
		++list[j].durTicks;
		++procInUse;
		if(list[j].durTicks == list[j].duration) {
		  //list[j].ready = false;
		  list[j].done = true;
		  list[j].completedTime = slice;
		  procQ.pop_front();
		}

	  }
	  else if(list[j].start_time < slice && CPU != &list[j])
	  {
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}
		if(list[j].done) {
		  cout << "   ";
		}
		else
		{
		  cout << " | ";
		  ++list[j].waitTicks;
		}


	  }
	  else
	  {
		if(slice < list[j].start_time)
		{
		  cout << " . ";
		}
		else {
		  cout << "   ";
		}

	  }

	}
	if(CPU != NULL && CPU->duration == CPU->durTicks) {
		CPU = NULL;
	}
	cout << "\n";
	++slice;
  }
}


void RR(Process list[], int size)
{
  int cycles = 5;
  cout << "\n";
  addToDeque(list, size);
  sort(procQ.begin(), procQ.end(), byStartTime);
  Process* CPU = NULL;
  while(!procQ.empty())
  {
	cout << slice << "	";
	for(int j = 0; j < size; ++j)
	{
	  if(list[j].start_time == slice)
	  {
		cout << " S ";
		list[j].ready = true;
		if(CPU == NULL && list[j].ready)
		{
		  CPU = &list[j];
		}
	  }
	  else if(list[j].start_time < slice && CPU == &list[j])
	  {
		cout << " X ";
		++list[j].durTicks;
		--list[j].duration;
		++procInUse;
		if(list[j].duration == 0) {
		  CPU = NULL;
		  list[j].ready = false;
		  list[j].done = true;
		  list[j].completedTime = slice;
		  procQ.pop_front();
		}
		if(list[j].durTicks == cycles) {
		  CPU = NULL;
		  list[j].durTicks = 0;
		}

	  }
	  else if(list[j].start_time < slice && CPU != &list[j])
	  {
		if(CPU == NULL && list[j].ready)
		{
		  CPU = &list[j];
		}
		if(list[j].done) {
		  cout << "   ";
		}
		else
		{
		  cout << " | ";
		  ++list[j].waitTicks;
		}


	  }
	  else
	  {
		if(slice < list[j].start_time)
		{
		  cout << " . ";
		}
		else {
		  cout << "   ";
		}

	  }


	}
	cout << "\n";
	++slice;
  }





}

void FCFS(Process list[], int size)
{
  cout << "\n";
  addToDeque(list, size);
  deque<Process*> readyQ;
  Process* CPU = NULL;
  sort(procQ.begin(), procQ.end(), byStartTime);

  //while(!procQ.empty())
  while(!procQ.empty())
  {
	cout << slice  << "	";

	for(int j = 0; j < size; ++j)
	{
	  if(list[j].start_time == slice)
	  {
		cout << " S ";
		readyQ.push_back(&list[j]);
		sort(readyQ.begin(), readyQ.end(), byStartTime);
		list[j].ready = true;
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}	
	  }
	  else if(list[j].start_time < slice && CPU == &list[j])
	  {
		cout << " X ";
		++list[j].durTicks;
		++procInUse;
		if(list[j].durTicks == list[j].duration) {
		  CPU = NULL;
		  list[j].ready = false;
		  list[j].done = true;
		  list[j].completedTime = slice;
		  procQ.pop_front();
		}

	  }
	  else if(list[j].start_time < slice && CPU != &list[j])
	  {
		if(CPU == NULL && list[j].ready)
		{
		  CPU = readyQ.front();
		  readyQ.pop_front();
		}
		if(list[j].done) {
		  cout << "   ";
		}
		else
		{
		  cout << " | ";
		  ++list[j].waitTicks;
		}


	  }
	  else
	  {
		if(slice < list[j].start_time)
		{
		  cout << " . ";
		}
		else {
		  cout << "   ";
		}

	  }
	}
	cout << "\n";
	++slice;
  }
}

//for splitting the process strings taken in by the files
void split(string str, char delim)
{
  int curr = 0, i = 0;
  int start = 0, end = 0;
  while(i <= str.length())
  {
	if(str[i] == delim || i == str.length())
	{
	  end = i;
	  string subStr = "";
	  subStr.append(str, start, end-start);
	  proc_split[curr] = subStr;
	  ++curr;
	  start = end + 1;
	}
	++i;
  }
}

int str2num(string str)
{
  int temp = 0;
  stringstream convert(str);
  convert >> temp;
  return temp;
}



//exec algorithms
int algExec(string alg)
{
  if(alg == "-fcfs") 
  {
	cout << "First Come First Serve" << endl;
	return 0;
  }
  else if(alg == "-rr")
  {
	cout << "Round Robin" << endl;
	//function for alg
	return 1;
  }
  else if(alg == "-hrrn")
  {
	cout << "HRRN" << endl;
	//function for alg
	return 2;
  }
  else if(alg == "-sjf")
  {
	cout << "Shortest Job First" << endl;
	//function for alg
	return 3;
  }
  else if(alg == "-sjr")
  {
	cout << "Shortest Job Remaining" << endl;
	//function for alg
	return 4;
  }
  else {
	cout << "No Algorithm Detected: Running Round Robin Instead" << endl;
	return 5;
  }
}

char* filename = NULL;

int main(int argc, char* argv[])
{
  int index;
  int arg = 0;
  opterr = 1;
  int numRandProcs;
  string whichAlg;
  bool isRandom;
  const struct option long_options[] =
  {
	{"fcfs", no_argument, 0, 'a'},
	{"rr", no_argument, 0, 'b'},
	{"r", required_argument, 0, 'c'},
	{"hrrn", no_argument, 0, 'd'},
	{"sjf", no_argument, 0, 'e'},
	{"sjr", no_argument, 0, 'f'},
  };

  while(arg != -1)
  {
	arg = getopt_long_only(argc, argv, "ab:c:d:e:f:", long_options, &index);
	switch(arg)
	{
	  case 'a':
		printf("case a, fcfs\n");
		whichAlg = "-fcfs";
		break;
	  case 'b':
		whichAlg = "-rr";
		printf("case b, round robin\n");
		break;
	  case 'c':
		numRandProcs = atoi(optarg);
		printf("case c, random arg, num of rand procs = %d\n", numRandProcs);
		isRandom = true;
		break;
	  case 'd':
		printf("case d, hrrn\n");
		whichAlg = "-hrrn";
		break;
	  case 'e':
		printf("case e, sjf\n");
		whichAlg = "-sjf";
		break;
	  case 'f':
		printf("case f, sjr\n");
		whichAlg = "-sjr";
		break;
	}
  }

  bool fileExist = false;
  
  for(int i = 0; i < argc; ++i)
  {
	istringstream iss(argv[i]);
	string token;
	while (getline(iss, token, '.'))
	{
	  if(token == "txt") {
		filename = argv[i];
	   fileExist = true;
	  }
	}

  }


  if(isRandom && fileExist) {

	struct Process randFiles[100];
	int randStart = 0;
	int randDur = 0;

	//declaring variables
	string readin;
	ifstream processes;
	processes.open(filename);
	int i = 0;


	//checking if the file opened properly
	if(processes.is_open())
	{
	  //importing all processes into the program from file
	  char delim = ' ';
	  int start, dur;
	  while(getline(processes, readin))
	  {
		//parse through file lines to store process data
		split(readin, delim);
		randFiles[i].proc_name = proc_split[0];
		start = str2num(proc_split[1]);
		randFiles[i].start_time = start;
		dur = str2num(proc_split[2]);
		randFiles[i].duration = dur;
		++i;
	  }
	}
	else
	{
	  cout << "File could not be opened" << endl;
	  exit(1);
	}
	processes.close();
	int totalProcs = i + numRandProcs;
	for(int j = i; j < totalProcs; ++j)
	{
	  randStart = dist(engine);
	  randDur = dist(engine);
	  string name = "random";
	  name += to_string(j);

	  randFiles[j].proc_name = name;
	  randFiles[j].start_time = randStart;
	  randFiles[j].duration = randDur;
	}
	int alg = algExec(whichAlg);
	switch (alg) {
	  case 0:
		FCFS(randFiles, totalProcs);
		break;
	  case 1:
		RR(randFiles, totalProcs);
		break;
	  case 2:
		HRRN(randFiles, totalProcs);
		break;
	  case 3:
		SJF(randFiles, totalProcs);
		break;
	  case 4:
		SJR(randFiles, totalProcs);
		break;
	  case 5:
		RR(randFiles, totalProcs);
		break;
	}

	getStats(slice, i, procInUse, randFiles);

  }
  else if(isRandom)
  {
	//variable assignments
	struct Process randProcs[numRandProcs];
	int randStart = 0;
	int randDur = 0;

	//loop for creating random processes based on num desired
	for(int i = 0; i < numRandProcs; ++i) {
	  //assign random values and proc name
	  randStart = dist(engine);
	  randDur = dist(engine);
	  string name = "proc";
	  name += to_string(i);

	  //create struct object with data
	  randProcs[i].proc_name = name;
	  randProcs[i].start_time = randStart;
	  randProcs[i].duration = randDur; 
	}
	int alg = algExec(whichAlg);
	switch (alg) {
	  case 0:
		FCFS(randProcs, numRandProcs);
		break;
	  case 1:
		RR(randProcs, numRandProcs);
		break;
	  case 2:
		HRRN(randProcs, numRandProcs);
		break;
	  case 3:
		SJF(randProcs, numRandProcs);
		break;
	  case 4:
		SJR(randProcs, numRandProcs);
		break;
	  case 5:
		RR(randProcs, numRandProcs);
		break;
	}

	getStats(slice, numRandProcs, procInUse, randProcs);

  }
  else
  {
	struct Process fileProcs[100];
	for(int i = 0; i < argc; ++i)
	{
	  istringstream iss(argv[i]);
	  string token;
	  while (getline(iss, token, '.'))
	  {
		if(token == "txt")
		  filename = argv[i];
	  }

	}
	//declaring variables
	string readin;
	ifstream processes;
	processes.open(filename);
	int i = 0;


	//checking if the file opened properly
	if(processes.is_open())
	{
	  //importing all processes into the program from file
	  char delim = ' ';
	  int start, dur;
	  while(getline(processes, readin))
	  {
		//parse through file lines to store process data
		split(readin, delim);
		fileProcs[i].proc_name = proc_split[0];
		start = str2num(proc_split[1]);
		fileProcs[i].start_time = start;
		dur = str2num(proc_split[2]);
		fileProcs[i].duration = dur;
		++i;
	  }
	}
	else
	{
	  cout << "File could not be opened" << endl;
	  exit(1);
	}
	processes.close();
	int alg = algExec(whichAlg);
	switch (alg) {
	  case 0:
		FCFS(fileProcs, i);
		break;
	  case 1:
		RR(fileProcs, i);
		break;
	  case 2:
		HRRN(fileProcs, i);
		break;
	  case 3:
		SJF(fileProcs, i);
		break;
	  case 4:
		SJR(fileProcs, i);
		break;
	  case 5:
		RR(fileProcs, i);
		break;
	}

	getStats(slice, i, procInUse, fileProcs);
  }
  return 0;
}


