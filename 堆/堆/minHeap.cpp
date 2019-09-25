#include"MinHeap.h"
#include<string.h>
MinHeap::MinHeap() {
	arr = nullptr;
	size = 0;
	capacity = 0;
}
inline void insertHeap2(int value, MinHeap& heap);
bool MinHeap::builtHeap(int* dateArr) {
	//if (size == 0)return false;
	//int father = size / 2 - 1; int child = 2 * father + 1;
	//if (size % 2) {//最后父节点有两个子节点
	//	size_t bigChild = arr[child] > arr[child+1] ? child : child+1;
	//	if (arr[father] < arr[bigChild]) {
	//		int temp = arr[bigChild];
	//		arr[bigChild] = arr[father]; arr[father] = temp;
	//	}
	//}
	//else {//最后父节点有1个子节点
	//	if (arr[father] < arr[child]) {
	//		int temp = arr[child];
	//		arr[child] = arr[father]; arr[father] = temp;
	//	}
	//}
	//for (father--; father >= 0; father--) {//方式1
	//	child = 2 * father + 1;
	//	size_t bigChild = arr[child] > arr[child + 1] ? child : child + 1;
	//	if (arr[father] < arr[bigChild]) {
	//		int temp = arr[bigChild];
	//		arr[bigChild] = arr[father]; arr[father] = temp;
	//	}
	//}
	//adjustDownHeap(1);
	for (int i = 0; i < DATE_SIZE; i++) {//方式2
		insertHeap2(dateArr[i],*this);
	}
	return true;
}

bool MinHeap::adjustDownHeap(int fatherIndex) {
	if (size == 0)return false;
	for (int father = fatherIndex; father < size / 2; father++) {
		int child = 2 * father + 1;
		size_t bigChild = arr[child] < arr[child + 1] ? child : child + 1;
		if (arr[father] > arr[bigChild]) {
			int temp = arr[bigChild];
			arr[bigChild] = arr[father]; arr[father] = temp;
		}
	}
	return true;
}

bool MinHeap::insertHeap(int value) {
	if (size == CAPACITY)return false;
	arr[size] = value; int child = size;
	while (child > 0) {
		int father = (child - 1) / 2;
		if (arr[child] > arr[father]) {
			int temp = arr[father];
			arr[father] = arr[child]; arr[child] = temp;
			child = father;
		}
		else {
			break;
		}

	}
	size++;
	return true;
}

bool MinHeap::popHeap() {
	//int temp = arr[0];
	arr[0] = arr[--size - 1];
	adjustDownHeap(0);
	return true;
}

bool initHeap(MinHeap& heap, int dateSize) {
	if (dateSize == 0)return false;
	//heap.size = size;
	heap.arr = new int[heap.capacity];
	//memcpy(heap.arr, arr, sizeof(*arr) * size);
	return true;
}

void printfHeap(MinHeap& heap) {
	if (heap.size == 0) {
		cout << "堆为空"; return;
	}
	for (int i = 0; i < heap.size; i++) {
		cout << heap.arr[i] << "\t";
	}
}
inline void insertHeap2(int value, MinHeap& heap) {
	if (heap.size == CAPACITY)return;
	heap.arr[heap.size] = value; int child = heap.size;
	while (child > 0) {
		int father = (child - 1) / 2;
		if (heap.arr[child] < heap.arr[father]) {
			int temp = heap.arr[father];
			heap.arr[father] = heap.arr[child]; heap.arr[child] = temp;
			child = father;
		}
		else {
			break;
		}

	}
	heap.size++;

}
