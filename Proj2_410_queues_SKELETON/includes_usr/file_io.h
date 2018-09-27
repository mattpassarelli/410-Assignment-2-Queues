/*
* file_IO.h
*
*  Created on: Aug 28, 2016
*      Author: Keith
*/

#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "constants.h"

enum SORT_ORDER { CPU_TIME, PROCESS_NUMBER, START_TIME };

//allthe functions available for use

//attempt to open file 'filename' to read, parse its rows 
//into PCB structs and add these structs to a vector 
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename);

//sorts the vector, returns nothing (thats what void means)
void sortData(SORT_ORDER mySortOrder);

//return the first struct in the vector
//then deletes it from the vector
PCB getNext();

//returns when the next job starts without altering the container
int peekNextStartTime();

//return the number of elements
//in the container
int size();

#endif /* UTILITIES_H_ */
