#pragma once
#ifndef NODE_DATE_H
#define NODE_DATE_H
#include"AllType2WayLoopQueue.h"
using namespace allType2WayLoopQ;
typedef int Date;
typedef struct IntStruct {
	int priority;
	Date date; 
	qNode at2wlln;
	IntStruct() {
		date = 0; priority = 0;
		at2wlln.front = nullptr;
		at2wlln.next = nullptr;
	}
}Ints;
#endif // !NODE_DATE_H
