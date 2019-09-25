#include"Heap.h"
#include<string.h>
Heap::Heap() {
	arr = nullptr;
	size = 0;
	capacity = 0;
}
Heap::~Heap() {
	delete arr;
}
inline void insertHeap2(int value, Heap& heap);
bool Heap::builtHeap(int* dateArr) {
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

bool Heap::adjustDownHeap(int fatherIndex) {
	if (size == 0)return false; 
	int father = 0; int child = 2 * father + 1; size_t bigChild = 0;
	for (father = fatherIndex; father < (size-2)/2; father=bigChild) {//7
		child = 2 * father + 1; if (child > size - 1)return true;
		 bigChild = arr[child] > arr[child+1] ? child : child+1;
		if (arr[father] < arr[bigChild]) {
			int temp = arr[bigChild];
			arr[bigChild] = arr[father]; arr[father] = temp;
		}
	}	
	if (size % 2) {//最后父节点有两个子节点
		 child = 2 * father + 1; 
		 if (child > size - 1)return true;
	 bigChild = arr[child] > arr[child + 1] ? child : child + 1;
		if (arr[father] < arr[bigChild]) {
			int temp = arr[bigChild];
			arr[bigChild] = arr[father]; arr[father] = temp;
			father = bigChild;
		}
	}
	else {//最后父节点有1个子节点
		 child = 2 * father + 1; 
		 if (child > size - 1)return true;
		if (arr[father] < arr[child]) {
			int temp = arr[child];
			arr[child] = arr[father]; arr[father] = temp;
			father = child;
		}
	}
	return true;
}

bool Heap::insertHeap( int value) {
	if (size==CAPACITY)return false;
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

bool Heap::popHeap() {
	int temp = arr[0];
	arr[0] = arr[size - 1];
	size--;
	adjustDownHeap(0); cout << temp << "\t";
	return true;
}

void Heap::sortHeap() {
	int count = size; cout << "堆排序";
	for (int i = 0; i < count; i++) {
		int temp = arr[0];
		arr[0] = arr[size - 1];
		arr[size - 1] = temp;
		size--;
		adjustDownHeap(0); cout <<temp << "\t";
	}
}

void Heap::findFrontHeap(size_t frontCount, Heap& copyHeap) {
		 cout << "查找前"<<frontCount<<"个最大值";
		for (size_t i = 0; i < frontCount; i++) {
			int temp = copyHeap.arr[0];
			copyHeap.arr[0] = copyHeap.arr[copyHeap.size - 1];
			copyHeap.arr[copyHeap.size - 1] = temp;
			copyHeap.size--;
			copyHeap.adjustDownHeap(0); cout << temp << "\t";
		}
	
}


bool initHeap(Heap& heap, int size) {
	if (size == 0)return false;
	//heap.size = size;
	heap.arr = new int[heap.capacity];
	//memcpy(heap.arr, arr, sizeof(*arr)*size);		
	return true;
}

void printfHeap(Heap& heap) {
	if (heap.size==0) {
		cout << "堆为空"; return;
	}
	cout << "打印";
	for (int i = 0; i < heap.size; i++) {
		cout << heap.arr[i] << "\t";
	}
}
inline void insertHeap2(int value, Heap& heap) {
	if (heap.size == CAPACITY)return ;
	heap.arr[heap.size] = value; int child = heap.size;
	while (child > 0) {
		int father = (child - 1) / 2;
		if (heap.arr[child] > heap.arr[father]) {
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
