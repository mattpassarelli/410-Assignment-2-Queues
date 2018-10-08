#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
#include "../includes_usr/logger_single_thread.h"
#include <queue>

PCB runningPCB;
std::queue<PCB> ready_Q, blocked_Q;

//small method just to clear the queues, since there is no native one
void clear(std::queue<PCB> q) {
	std::queue<PCB> empty;
	std::swap(q, empty);
}

void reinitializePCB() {
	runningPCB.cpu_time = UNINITIALIZED;
	runningPCB.io_time = UNINITIALIZED;
	runningPCB.process_number = UNINITIALIZED;
	runningPCB.start_time = UNINITIALIZED;
}

void dispatcher::init() {
	clear(ready_Q);
	clear(blocked_Q);
	reinitializePCB();
}

PCB dispatcher::getCurrentJob() {
	return runningPCB;
}

void dispatcher::addJob(PCB &myPCB) {
	ready_Q.push(myPCB);
}

int dispatcher::processInterrupt(int interrupt) {
	if (interrupt == SWITCH_PROCESS) {
		if (ready_Q.empty()) {
			//is blocked_Q empty
			if (blocked_Q.empty()) {
				return NO_JOBS;
			}
			//no blocked_Q is not empty, but ready_Q is
			return BLOCKED_JOBS;
		} else {
			PCB temp = ready_Q.front();
			ready_Q.pop();

			if (runningPCB.process_number != UNINITIALIZED
					&& runningPCB.start_time != UNINITIALIZED
					&& runningPCB.cpu_time != UNINITIALIZED
					&& runningPCB.io_time != UNINITIALIZED) {
				ready_Q.push(runningPCB);
			}

			runningPCB = temp;

			return PCB_SWITCHED_PROCESSES;
		}
	} else if (interrupt == IO_COMPLETE) {
		if (blocked_Q.empty()) {
			return PCB_BLOCKED_QUEUE_EMPTY;
		} else {
			while (!blocked_Q.empty()) {
				ready_Q.push(blocked_Q.front());
				blocked_Q.pop();
			}

			return PCB_MOVED_FROM_BLOCKED_TO_READY;
		}
	} else {
		return PCB_UNIMPLEMENTED;
	}
}

int dispatcher::doTick() {
	//if any part of the runningPCB is UNINITIALIZED, don't proceed
	if (runningPCB.process_number == UNINITIALIZED
			|| runningPCB.start_time == UNINITIALIZED
			|| runningPCB.cpu_time == UNINITIALIZED
			|| runningPCB.io_time == UNINITIALIZED) {
		//is ready_Q empty?
		if (ready_Q.empty()) {
			//is blocked_Q empty
			if (blocked_Q.empty()) {
				return NO_JOBS;
			}
			//no blocked_Q is not empty, but ready_Q is
			return BLOCKED_JOBS;
		} else {
			//ready_Q is not empty, but runningPCB is still uninitialized
			runningPCB = ready_Q.front();
			ready_Q.pop();
			return PCB_MOVED_FROM_READY_TO_RUNNING;
		}
	} else {
		//we have a runningPCB

		//if cpu_time is above 0, decrement it. Prevents doing 0 - 1 = -1
		if (runningPCB.cpu_time > 0) {
			runningPCB.cpu_time -= 1;
			//if it is now still above zero, return
			if (runningPCB.cpu_time > 0) {
				return PCB_CPUTIME_DECREMENTED;
			}
			//otherwise, we just move on
		}
		//otherwise, if it is 0 to start with, proceed
		if (runningPCB.cpu_time == 0) {
			//process is done, move on
			int rtn;

			//check for IO blocking call
			//1 == yes
			if (runningPCB.io_time == 1) {
				runningPCB.io_time = 0;
				blocked_Q.push(runningPCB);
				rtn = PCB_ADDED_TO_BLOCKED_QUEUE;
				reinitializePCB();
			} else {
				reinitializePCB();
				rtn = PCB_FINISHED;
			}
			return rtn;
		}
	}
}
