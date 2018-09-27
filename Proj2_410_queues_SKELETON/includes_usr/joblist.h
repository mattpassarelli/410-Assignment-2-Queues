#pragma once
#include "constants.h"
namespace joblist {
	
	//loads data from filename and sorts 
	//it by job start time
	int init(const char* filename = DEFAULT_SOURCE_FILE);

	//if no jobs in vector managed by file_io return NO_JOBS
	//otherwise see if its time to load a process by comparing current tick 
	//to the next process in lines start_time.  
	//If its time to load return ADD_JOB_TO_DISPATCHER
	//if not return WAITING_TO_ADD_JOB_TO_DISPATCHER
	int doTick(int currentTick);

	//gets next job from file_IO
	PCB getNextJob();
}





