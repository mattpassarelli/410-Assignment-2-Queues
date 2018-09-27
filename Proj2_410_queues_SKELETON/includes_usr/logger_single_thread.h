#pragma once
#include "constants.h"
//use this by filling up the logger and then writing all data out when you are through
//saves on opening and closing a file lots of times

namespace ST_LOG {
	//adds info to a vector
	void log(int tickcount, int process_number);

	//serializes vector to disk
	void save(const char* filename = DEFAULT_LOG_FILE);
}

