#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<iostream>
constexpr auto CAPACITY = 20;
constexpr auto DATE_SIZE = 17;
using namespace std;
typedef struct Date {
	int date;
	int priority;
	Date();
}D;
typedef struct HeapPriQueue {
	Date* dateArr;
	int size;
	size_t capacity;
	HeapPriQueue();
	bool builtHeapPriQueue(Date* dateArr);
	bool adjustDownHeapPriQueue(int father);
	bool pushHeapPriQueue(Date& value);
	bool popHeapPriQueue();
}HPQ;
bool initHeapPriQueue(HeapPriQueue& heapQueue, int dateSize);
void printfHeapPriQueue(HeapPriQueue& heapQueue);

#endif // !PRIORITY_QUEUE_H
