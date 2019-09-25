#pragma once
#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#include<iostream>
constexpr auto CAPACITY = 20;
constexpr auto DATE_SIZE = 17;
using namespace std;
typedef struct MinHeap {
	int* arr;
	int size;
	size_t capacity;
	MinHeap();
	bool builtHeap(int* dateArr);
	bool adjustDownHeap(int father);
	bool insertHeap(int value);
	bool popHeap();
}MH;
bool initHeap(MinHeap& heap, int dateSize);
void printfHeap(MinHeap& heap);

#endif // !MIN_HEAP_H
