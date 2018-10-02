#include <iostream>
#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"

//assumme the worst
bool joblistHasJobs = false;

int joblist::init(const char* filename) {

	loadData(filename);
	sortData(START_TIME);

	return SUCCESS;
}

PCB joblist::getNextJob() {
	return getNext();
}

int joblist::doTick(int currentTick) {

	if (size() <= 0) {
		return NO_JOBS;
	} else {
		if (currentTick < joblist::getNextJob().start_time) {
			return ADD_JOB_TO_DISPATCHER;
		} else {
			return WAITING_TO_ADD_JOB_TO_DISPATCHER;
		}
	}
}

