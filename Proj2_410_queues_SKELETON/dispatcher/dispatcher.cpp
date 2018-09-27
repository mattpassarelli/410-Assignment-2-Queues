#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
#include "../includes_usr/logger_single_thread.h"
#include <queue>

PCB runningPCB;

void dispatcher::init() {
}

PCB dispatcher::getCurrentJob() {
	return runningPCB;
}

void dispatcher::addJob(PCB &myPCB) {
}

int dispatcher::processInterrupt(int interrupt) {
	return NO_JOBS;
}

int dispatcher::doTick() {
	return NO_JOBS;
}
