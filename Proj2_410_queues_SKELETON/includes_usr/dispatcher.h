#pragma once
#include "constants.h"
namespace dispatcher {
	//clears ready_Q and blocked_Q these are queues of PCB structures,
	//initializes runningPCB to default values in constants (see PCB structure)
	void init();

	//add a job to the ready queue
	void addJob(PCB &myPCB);

	//see flowchart
	int doTick();

	//interrupt can be either;
	//a switch process interrupt in which case the function performs the appropriate tasks and returns PCB_SWITCHED_PROCESSES
	//or a io_complete interrupt in which case it pulls ALL processes off of the blockedQ and returns either PCB_MOVED_FROM_BLOCKED_TO_READY (if there were any) 
	//or PCB_BLOCKED_QUEUE_EMPTY if there were none.
	int processInterrupt(int interrupt);

	//used for testing, return a copy of runningPCB
	PCB getCurrentJob();
}

