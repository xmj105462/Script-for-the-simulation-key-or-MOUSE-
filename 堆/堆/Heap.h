#pragma once
#ifndef HEAP_H
#define HEAP_H
#include<iostream>
constexpr auto CAPACITY = 20;
constexpr auto DATE_SIZE = 17;
using namespace std;
typedef struct Heap {
	int* arr;
	int size;
	size_t capacity;
	Heap();
	~Heap();
	Heap(const Heap& other) { size = other.size; capacity = other.capacity;
	arr = new int[capacity];
	memcpy(arr, other.arr, sizeof(*(other.arr))*size);	
	}
	const Heap& operator=(const Heap& other) {
		size = other.size; capacity = other.capacity;
		arr = new int[capacity];
		memcpy(arr, other.arr, sizeof(*(other.arr)) * size);
	}


	 bool builtHeap(int* dateArr);
	 bool adjustDownHeap(int father);
	 bool insertHeap(int value);
	 bool popHeap();
	 void sortHeap();
	 void findFrontHeap(size_t frontCount, Heap& copyHeap);//查找前front count个最大值，用拷贝对象
}H;
 bool initHeap(Heap& heap, int size);
 void printfHeap(Heap& heap);

#endif // !HEAP_H
