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
			return NO_JOBS;
		} else if (blocked_Q.empty()) {
			return BLOCKED_JOBS;
		} else {
			PCB temp = ready_Q.front();
			ready_Q.pop();

			ready_Q.push(runningPCB);

			runningPCB = temp;

			return PCB_SWITCHED_PROCESSES;
		}
	} else if (interrupt == IO_COMPLETE) {
		if (blocked_Q.size() <= 0) {
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
	return NO_JOBS;
}
