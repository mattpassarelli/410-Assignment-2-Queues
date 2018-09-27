#include "../includes_usr/logger_single_thread.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
namespace ST_LOG {
	
	struct logdata {
		int tickcount;
		int process_number;
	};

	std::vector<logdata> myLogInfo;
	logdata myData;

	void log(int tickcount, int process_number) {
		myData.tickcount		= tickcount;
		myData.process_number = process_number;

		myLogInfo.push_back(myData);
	}

	void save(const char* filename) {
		std::ofstream myFile;
		myFile.open(filename);
		if (!myFile.is_open())
			return;
		std::string myline;
		//iterate over vector
		for (logdata myData: myLogInfo) {
			myline = std::to_string(myData.tickcount) + ',' + std::to_string(myData.process_number) + '\n';
			myFile << myline;
		}
		//close file
		if (myFile.is_open())
			myFile.close();

		myLogInfo.clear();
	}
}
