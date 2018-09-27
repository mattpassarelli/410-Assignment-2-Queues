#pragma once
#include <iostream>

//interrupt codes
const int SWITCH_PROCESS				= 1;
const int IO_COMPLETE					= 0;

//SUCCESS CODES
const int 			SUCCESS				= 0;
const int			ADD_JOB_TO_DISPATCHER				= SUCCESS + 10;
const int			WAITING_TO_ADD_JOB_TO_DISPATCHER	= SUCCESS + 9;
const int			PCB_BLOCKED_QUEUE_EMPTY				= SUCCESS + 8;
const int			PCB_MOVED_FROM_READY_TO_RUNNING		= SUCCESS + 7;
const int			PCB_MOVED_FROM_BLOCKED_TO_READY		= SUCCESS + 6;
const int			PCB_ADDED_TO_BLOCKED_QUEUE			= SUCCESS + 5;
const int			PCB_SWITCHED_PROCESSES  = SUCCESS + 4;
const int			PCB_FINISHED			= SUCCESS + 3;
const int			PCB_CPUTIME_DECREMENTED = SUCCESS + 2;
const int			PCB_SCHEDULED			= SUCCESS + 1;
const int			PCB_UNIMPLEMENTED		= SUCCESS - 1;

//FAILURE CODES
const int 			FAIL				= SUCCESS - 1;
const int 			USER_CHOSE_TO_EXIT	= SUCCESS - 2;
const int 			COULD_NOT_OPEN_FILE = SUCCESS - 3;
const int 			COULD_NOT_READ_FILE = SUCCESS - 4;
const int			UNINITIALIZED		= SUCCESS - 5;
const int			UNIMPLEMENTED		= SUCCESS - 6;
const int			NO_JOBS				= SUCCESS - 7;
const int			BLOCKED_JOBS		= SUCCESS - 8;

const char			CHAR_TO_SEARCH_FOR = ',';

const int			TIMER_BEGIN = 0;

//default files
const char*	const 	DEFAULT_LOG_FILE = "results.txt";
const char*	const 	DEFAULT_SOURCE_FILE = "testdata.txt";

const char* const	SOURCE_FILE_1_IO = "./sampleruns/1_IO_testdata.txt";
const char*	const 	LOG_FILE_1_IO = "1_IO_results.txt";

const char* const	SOURCE_FILE_1_NO_IO = "./sampleruns/1_noIO_testdata.txt";
const char*	const 	LOG_FILE_1_NO_IO = "1_noIO_results.txt";

const char* const	SOURCE_FILE_2_IO = "./sampleruns/2_IO_testdata.txt";
const char*	const 	LOG_FILE_2_IO = "2_IO_results.txt";

const char* const	SOURCE_FILE_2_MIXED = "./sampleruns/2_MIXED_testdata.txt";
const char*	const 	LOG_FILE_2_MIXED = "2_MIXED_results.txt";

const char* const	SOURCE_FILE_2_noIO = "./sampleruns/2_noIO_testdata.txt";
const char*	const 	LOG_FILE_2_noIO = "2_noIO_results.txt";

const char* const	SOURCE_FILE_MANY_MIXED = "./sampleruns/MANY_MIXED_testdata.txt";
const char*	const 	LOG_FILE_MANY_MIXED = "MANY_MIXED_results.txt";

//this is where the loaded data goes
struct PCB {
	int process_number	= UNINITIALIZED;
	int	start_time		= UNINITIALIZED;
	int cpu_time		= UNINITIALIZED;
	int io_time			= UNINITIALIZED;
};

#define _SHOWLOG
#ifdef _SHOWLOG
#define PRINT1(txt) std::cout<<txt<<std::endl;
#define PRINT2(txt,txt1) std::cout<<txt<<txt1<<std::endl;
#define PRINT3(txt,txt1,txt2) std::cout<<txt<<txt1<<txt2<<std::endl;
#define PRINT4(txt,txt1,txt2,txt3) std::cout<<txt<<txt1<<txt2<<txt3<<std::endl;
#else
//compiler will optimize this to nothing for a release build
#define PRINT1(txt);
#define PRINT2(txt,txt1);
#define PRINT3(txt,txt1,txt2);
#define PRINT4(txt,txt1,txt2,txt3);
#endif
