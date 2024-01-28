#include<iostream>
#include<string>
#include<fstream>
#include<unistd.h> 
#include<ctime>
using namespace std;


void runProcessScheduling(const char* PathofJobFile, int globalTick);
string* assignInstructions(string processFileName);
//void multiLevelFeedbackQueue(); 
// global time
int globalTime = 0;

// a process list node to store process information
class processListNode
{
public:    
    string processName;
    int indexInProcessList;
    string state;
    float arrivalTime;
    string currentQueue;
	string* instructions;

    processListNode* next;
    processListNode* pre;

    void setState(string temp)
    {
        state = temp;
    }
    void setQueue(string temp)
    {
        currentQueue = temp;
    }

};

// a process list to store processes
class processList
{
public:
    processListNode* head; 
    int setIndex = 1;

    processList()
    {
        head = NULL;
    }

    // Adding a new process in the double linked list
    void add(string pName,string pState,float pArrival,string pQueue,string* steps)
    {
        if (head == NULL)
		{
			processListNode* temp = new processListNode;
			
            temp->processName = pName;
            temp->indexInProcessList = 0;
            temp->state = pState;
            temp->arrivalTime = pArrival;
            temp->currentQueue = pQueue;
			temp->instructions = steps;

			temp->next = NULL;
			temp->pre = NULL;
			head = temp;
		}
		else
		{
			processListNode* ptr, *temp;
			ptr = head;

			while (ptr->next != NULL)
			{
				ptr = ptr->next;
                setIndex++;
			}
			temp = new processListNode;

			temp->processName = pName;
            temp->indexInProcessList = setIndex;
            temp->state = pState;
            temp->arrivalTime = pArrival;
            temp->currentQueue = pQueue;
			temp->instructions = steps;
			
            temp->next = NULL;
			temp->pre = ptr;
			ptr->next = temp;
		}
    }
	
	// Displaying the process list
	void displayLinkedList() 
	{		
		processListNode* temp = head;
		
		while (temp != NULL) 
		{
			cout << temp->processName << " ";
			temp = temp->next;
		}
	}

	// access processes out side
	processListNode getLinkedList() 
	{	
		return *head;
	}
};


string* assignInstructions(string processFileName)
{
	string* arr = new string[50];
	fstream file;
    string word;
    file.open(processFileName.c_str());

	int i = 0;
    while (file >> word)
    {
        arr[i] = word;
        //cout << arr[i] << endl;
        i++;
    }
    arr[i] = "\0";

	return arr;
}

// FCFS 1 queue starts
struct QNode_FCFS_1 
{
	int data;
	QNode_FCFS_1* next;

	QNode_FCFS_1(int d)
	{
		data = d;
		next = NULL;
	}
};

class Queue_FCFS_1 
{
public:
	QNode_FCFS_1* front, * rear;

	Queue_FCFS_1()
	{
		front = rear = NULL;
	}

	void enQueue(int x)
	{
		QNode_FCFS_1* temp = new QNode_FCFS_1(x);

		if (rear == NULL) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void deQueue()
	{
		if (front == NULL)
			return;

		QNode_FCFS_1* temp = front;
		cout<<front->data;
		front = front->next;
		

		if (front == NULL)
			rear = NULL;

		delete (temp);
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
// FCFS 1 queue ends

// FCFS 2 queue starts
struct QNode_FCFS_2 
{
	int data;
	QNode_FCFS_2* next;

	QNode_FCFS_2(int d)
	{
		data = d;
		next = NULL;
	}
};

class Queue_FCFS_2 
{
public:
	QNode_FCFS_2* front, * rear;

	Queue_FCFS_2()
	{
		front = rear = NULL;
	}

	void enQueue(int x)
	{
		QNode_FCFS_2* temp = new QNode_FCFS_2(x);

		if (rear == NULL) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void deQueue()
	{
		if (front == NULL)
			return;

		QNode_FCFS_2* temp = front;
		front = front->next;

		if (front == NULL)
			rear = NULL;

		delete (temp);
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
// FCFS 2 queue ends

// SJF queue starts
struct QNode_SJF 
{
	int data;
	QNode_SJF* next;

	QNode_SJF(int d)
	{
		data = d;
		next = NULL;
	}
};

class Queue_SJF 
{
public:
	QNode_SJF* front, * rear;

	Queue_SJF()
	{
		front = rear = NULL;
	}

	void enQueue(int x)
	{
		QNode_SJF* temp = new QNode_SJF(x);

		if (rear == NULL) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void deQueue()
	{
		if (front == NULL)
			return;

		QNode_SJF* temp = front;
		front = front->next;

		if (front == NULL)
			rear = NULL;

		delete (temp);
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
// SJF queue ends


void writeToFile(processListNode* temp,string);

// main 
int main()
{
    // Calling scheduling
    runProcessScheduling("job.txt",globalTime);

    cout<<"\nEND\n";

    return 0;
}

void runProcessScheduling(const char* PathofJobFile, int globalTick)
{
    int size=0;
    string str;
	
	// arrays to store instructions of each process
	string* steps1 = new string[50];
	string* steps2 = new string[50];
	string* steps3 = new string[50];

    int *processArrive=new int[3];              // Array to store process ID
    string *processName= new string[3];     // Arrcy to store process name

    processList pl; // process class object to store process

    // Getting size of job.txt file
    fstream fileSize(PathofJobFile);
    if(!fileSize)
    {
        cout<<"File not open\n";
    }
    else
    {
        while(getline(fileSize,str))
        {
            size++;
        }
    }
    fileSize.close();

    fstream file(PathofJobFile);
    if(!file)
    {
        cout<<"File not open\n";
    }
    else
    {
        for(int i=0; i<size;i++){

            file>>processName[i]>>processArrive[i];
        }
    }
    file.close();


	// sorting the processes in accending order
	int first=0,second=0,third=0;
	if(processArrive[0]>processArrive[1] && processArrive[0]>processArrive[2])
	{
		third=0;
		if(processArrive[1]>processArrive[2])
		{
			second=1;
			first=2;
		}
		else
		{
			second=2;
			first=1;
		}
	}
	else if(processArrive[1]>processArrive[0] && processArrive[1]>processArrive[2])
	{
		third=1;
		if(processArrive[2]>processArrive[0])
		{
			second=2;
			first=0;
		}
		else
		{
			second=0;
			first=2;
		}
	}
	else if(processArrive[2]>processArrive[0] && processArrive[2]>processArrive[1])
	{
		third=2;
		if(processArrive[0]>processArrive[1])
		{
			second=0;
			first=1;
		}
		else
		{
			second=1;
			first=0;
		}
	}
	// displaying the order of processes
// 	cout<<"\n"<<"process 1 is: "<<first;
// 	cout<<"\n"<<"process 2 is: "<<second;
// 	cout<<"\n"<<"process 3 is: "<<third;

	// getting instructions of each process
	steps1 = assignInstructions((processName[first]+".txt"));
	steps2 = assignInstructions((processName[second]+".txt"));
	steps3 = assignInstructions((processName[third]+".txt"));

	// adding process in the processes list
	pl.add(processName[first],"non",processArrive[first],"non",steps1);
	pl.add(processName[second],"non",processArrive[second],"non",steps2);
	pl.add(processName[third],"non",processArrive[third],"non",steps3);

	// to display linked list of processes
	//pl.displayLinkedList();
	
	Queue_FCFS_1 qf1;
    Queue_FCFS_2 qf2;
    Queue_SJF qsjf;

	processListNode *process1,*process2,*process3;
	process1 = pl.head;
	process2 = pl.head->next;
	process3 = pl.head->next->next;

	// temporary array to read instructions
	string* tempstr = new string[50];
	// temporary variables to hold instructions being executing
	string tempInstruction,tempDevice,tempTicks;

	// scheduling starts
	for(int tick=0;tick<=50;tick++)
	{
		// when process 1 will arrive 
		if(tick==process1->arrivalTime)
		{
			qf1.enQueue(process1->indexInProcessList);
			tempstr = process1->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE" || tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					break;
				}
			}
			process1->setQueue("FSFC-1");
			process1->setState("Ready");
			sleep(1);
			writeToFile(process1,tempInstruction);

			globalTime += 1;
			goto point;
		}

		// 2nd process
		if(tick==process2->arrivalTime)
		{
			qf1.enQueue(process2->indexInProcessList);
			tempstr = process2->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE" || tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					break;
				}
			}
			process2->setQueue("FSFC-1");
			process2->setState("Ready");
			sleep(1);
			writeToFile(process2,tempInstruction);

			globalTime += 1;
			goto point1;
		}

		// 3rd process
		if(tick==process3->arrivalTime)
		{
			qf1.enQueue(process3->indexInProcessList);
			tempstr = process3->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE" || tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					break;
				}
			}
			process3->setQueue("FSFC-1");
			process3->setState("Ready");
			sleep(1);
			writeToFile(process3,tempInstruction);

			globalTime += 1;
			goto point2;
		}

		// process 1
		tempstr = process1->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					process1->setQueue("FSFC-1");
					process1->setState("Ready");

sleep(1);
					writeToFile(process1,tempInstruction);

					break;
				}
				else if(tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempTicks = tempstr[i+2];
					if(tempTicks == "1")
					{
						tempInstruction = tempstr[i];
						process1->setState("Waiting");
						tempstr[i] = "none";
						tempDevice = tempstr[i+1];
						tempstr[i+1] = "none";
						if(tempDevice == "SCREEN")
						{
							process1->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process1->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process1->setState("Network");
						}
						
						tempstr[i+2] = "none";
						//tick+=(stoi(tempTicks)-1);
						tempstr[i+3] = "none";
sleep(1);
						writeToFile(process1,tempInstruction);

						break;
					}
					else
					{
						tempInstruction = tempstr[i];
						process1->setState("Waiting");
						tempDevice = tempstr[i+1];
						if(tempDevice == "SCREEN")
						{
							process1->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process1->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process1->setState("Network");
						}
						
						// decresing tick time
						tempTicks = to_string((stoi(tempTicks)-1));
						tempstr[i+2] = tempTicks;
sleep(1);
						writeToFile(process1,tempInstruction);

						break;
					}					
				}
			}
			point:
		
		//process 2
		if(tick>process2->arrivalTime){		

		tempstr = process2->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					process2->setQueue("FSFC-1");
					process2->setState("Ready");
sleep(1);
					writeToFile(process2,tempInstruction);

					break;
				}
				else if(tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempTicks = tempstr[i+2];
					if(tempTicks == "1")
					{
						tempInstruction = tempstr[i];
						process2->setState("Waiting");
						tempstr[i] = "none";
						tempDevice = tempstr[i+1];
						tempstr[i+1] = "none";
						if(tempDevice == "SCREEN")
						{
							process2->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process2->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process2->setState("Network");
						}
						
						tempstr[i+2] = "none";
						//tick+=(stoi(tempTicks)-1);
						tempstr[i+3] = "none";
sleep(1);
						writeToFile(process2,tempInstruction);

						break;
					}
					else
					{
						tempInstruction = tempstr[i];
						process2->setState("Waiting");
						tempDevice = tempstr[i+1];
						if(tempDevice == "SCREEN")
						{
							process2->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process2->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process2->setState("Network");
						}
						
						// decresing tick time
						tempTicks = to_string((stoi(tempTicks)-1));
						tempstr[i+2] = tempTicks;
sleep(1);
						writeToFile(process2,tempInstruction);

						break;
					}					
				}
			}
		}
		point1:

		// process 3
		if(tick>process3->arrivalTime){		

		tempstr = process3->instructions;
			for(int i=0;tempstr[i]!="\0";i++)
			{
				if(tempstr[i] == "COMPUTE")
				{
					tempInstruction = tempstr[i];
					tempstr[i] = "none";
					process2->setQueue("FSFC-1");
					process2->setState("Ready");
sleep(1);
					writeToFile(process3,tempInstruction);

					break;
				}
				else if(tempstr[i] == "READ" || tempstr[i] == "WRITE")
				{
					tempTicks = tempstr[i+2];
					if(tempTicks == "1")
					{
						tempInstruction = tempstr[i];
						process3->setState("Waiting");
						tempstr[i] = "none";
						tempDevice = tempstr[i+1];
						tempstr[i+1] = "none";
						if(tempDevice == "SCREEN")
						{
							process3->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process3->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process3->setState("Network");
						}
						
						tempstr[i+2] = "none";
						//tick+=(stoi(tempTicks)-1);
						tempstr[i+3] = "none";
sleep(1);
						writeToFile(process3,tempInstruction);

						break;
					}
					else
					{
						tempInstruction = tempstr[i];
						process3->setState("Waiting");
						tempDevice = tempstr[i+1];
						if(tempDevice == "SCREEN")
						{
							process3->setQueue("Device");	
						}
						else if(tempDevice == "DISK")
						{
							process3->setQueue("Hard Disk");
						}
						else if(tempDevice == "NETWORK")
						{
							process3->setState("Network");
						}
						
						// decresing tick time
						tempTicks = to_string((stoi(tempTicks)-1));
						tempstr[i+2] = tempTicks;
sleep(1);
						writeToFile(process3,tempInstruction);

						break;
					}					
				}
			}
		}

		point2:
		cout<<"";
		
	}

	// qf1.deQueue();
	// qf1.deQueue(); 
	// qf1.deQueue();
}

void writeToFile(processListNode* temp,string instructionFile)
{	
	// object capture the process
	processListNode* current = temp;


	// writting in the Process.txt
	fstream file("Process.txt",ios::app);
	if(!file)
    {
        cout<<"File not open\n";
    }
    else
    {
        //file<<"Process Name\t"<<"Process State\t"<<"Process Queue\n";
		file<<"\n";
		file<<"     "<<current->processName<<"\t\t\t\t"<<current->state<<"\t\t\t\t"<<current->currentQueue;
    }
    file.close();


	// writting in the CPU.txt
	fstream file1("CPU.txt",ios::app);
	if(!file)
    {
        cout<<"File not open\n";
    }
    else
    {
        //file<<"Process Name\t"<<"Process State\t"<<"Process Queue\n";
		file1<<"\n";
		file1<<"     "<<current->processName<<"\t\t\t\t"<<instructionFile;
		
    }
    file.close();


	// Writting in the Queue.txt
	fstream file("Queue.txt",ios::app);
	if(!file)
    {
        cout<<"File not open\n";
    }
    else
    {
        //file<<"Process Name\t"<<"Process State\t"<<"Process Queue\n";
		file<<"     "<<current->processName<<"\t\t\t\t"<<*current->instructions<<"\n";
    }
    file.close();
}