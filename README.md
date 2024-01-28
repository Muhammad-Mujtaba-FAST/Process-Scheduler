# Process-Scheduler
It is a mini CPU.

Process has five basic states:
1. New: Process is created and stored in Process List.
2. Ready: The process can be executed anytime if CPU is assigned. In other words process is not waiting for the completion of any I/O operations.
3. Running: Instructions of the process are being executed. A single CPU can executed one process at any time. Therefore only one process can be in running state.
4. Waiting: Waiting for the completion of an I/O operation, e.g., waiting to get user input from keyboard, writing/reading to a file. The completion of an I/O operation is indicated by an I/O event.
5. Terminated: The process is finished and its memory and resources are deallocated.

The data between Start and End of the input file specify a set of instructions associated with each
process. There are three types of instructions, READ, WRITE and COMPUTE. These instructions
represent CPU computations and read/write data to the Hard Disk, Network and Peripheral devices
(Monitor, Keyboard and Printer). COMPUTE instruction always will be 1 tick. Different keywords
as below:

DISK: This keyword represents the hard disk.
SCREEN: represents the monitor. And it’s a Peripheral device.
PRINTER: represents the printer. And it’s a Peripheral device.
KEYBOARD: represents the keyboard. And it’s a Peripheral device.
NETWORK: represents the Network communication.

Description of Files:
Following files will be provided for Process Scheduling
1. job.txt
This file will contain process name and their arrival time separated with space. i.e.
P0 0
P1 1
P2 2
P3 3

Note: List of processes is unordered.
2. ProcessName.txt
a) Examples of this file are P0.txt , P1.txt and P2.txt

P0.txt
P1.txt
P2.txt

void runProcessScheduling(const char* PathofJobFile, int globalTick)
1. const char* PathofJobFile :- path of job.txt file.
2. int globalTick :- simulation can be specified to run for a certain global ticks (ticks vs. time)
3. Path for ProcessName.txt will be same as job.txt.
After every tick of the global clock, writing data to files
1) Process.txt
Name of process (in order of their arrival time), state, which queue process resides OR CPU
2) CPU.txt
Name of process currently being executed, instruction being executed.
3) Queue.txt
Name of queue, list of processes in the queue.
