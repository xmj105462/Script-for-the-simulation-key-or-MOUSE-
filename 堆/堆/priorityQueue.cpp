#include"priorityQueue.h"
#include<string.h>
HeapPriQueue::HeapPriQueue() {
	dateArr = nullptr;
	size = 0;
	capacity = 0;
}
inline void pushHeapPriQueue2(Date value, HeapPriQueue& heap);
bool HeapPriQueue::builtHeapPriQueue(Date *dateArr) {
	//if (size == 0)return false;
	//int father = size / 2 - 1; int child = 2 * father + 1;
	//if (size % 2) {//最后父节点有两个子节点
	//	size_t bigChild = dateArr[child] > dateArr[child+1] ? child : child+1;
	//	if (dateArr[father] < dateArr[bigChild]) {
	//		int temp = dateArr[bigChild];
	//		dateArr[bigChild] = dateArr[father]; dateArr[father] = temp;
	//	}
	//}
	//else {//最后父节点有1个子节点
	//	if (dateArr[father] < dateArr[child]) {
	//		int temp = dateArr[child];
	//		dateArr[child] = dateArr[father]; dateArr[father] = temp;
	//	}
	//}
	//for (father--; father >= 0; father--) {//方式1
	//	child = 2 * father + 1;
	//	size_t bigChild = dateArr[child] > dateArr[child + 1] ? child : child + 1;
	//	if (dateArr[father] < dateArr[bigChild]) {
	//		int temp = dateArr[bigChild];
	//		dateArr[bigChild] = dateArr[father]; dateArr[father] = temp;
	//	}
	//}
	//adjustDownHeap(1);
	for (int i = 0; i < DATE_SIZE; i++) {//方式2
		pushHeapPriQueue2(dateArr[i], *this);
	}
	return true;
}

bool HeapPriQueue::adjustDownHeapPriQueue(int fatherIndex) {
	if (size == 0)return false;
	for (int father = fatherIndex; father < size / 2; father++) {
		int child = 2 * father + 1;
		size_t bigChild = dateArr[child].priority > dateArr[child + 1].priority ? child : child + 1;
		if (dateArr[father].priority < dateArr[bigChild].priority) {
			D temp = dateArr[bigChild];
			dateArr[bigChild] = dateArr[father]; dateArr[father] = temp;
		}
	}
	return true;
}

bool HeapPriQueue::pushHeapPriQueue(Date& value) {
	if (size == CAPACITY)return false;
	dateArr[size] = value; int child = size;
	while (child > 0) {
		int father = (child - 1) / 2;
		if (dateArr[child].priority > dateArr[father].priority) {
			D temp = dateArr[father];
			dateArr[father] = dateArr[child]; dateArr[child] = temp;
			child = father;
		}
		else {
			break;
		}

	}
	size++;
	return true;
}

bool HeapPriQueue::popHeapPriQueue() {
	//int temp = dateArr[0];
	dateArr[0] = dateArr[--size - 1];
	adjustDownHeapPriQueue(0);
	return true;
}

bool initHeapPriQueue(HeapPriQueue& heap, int dateSize) {
	if (dateSize == 0)return false;
	//heap.size = dateSize;
	heap.dateArr = new Date[heap.capacity]();
	//memcpy(heap.dateArr, dateArr, sizeof(*dateArr) * size);
	return true;
}

void printfHeapPriQueue(HeapPriQueue& heap) {
	if (heap.size == 0) {
		cout << "堆为空"; return;
	}
	for (int i = 0; i < heap.size; i++) {
		cout << heap.dateArr[i].date << "\t";
	}
}
inline void pushHeapPriQueue2(Date value, HeapPriQueue& heap) {
	if (heap.size == CAPACITY)return;
	heap.dateArr[heap.size] = value; int child = heap.size;
	while (child > 0) {
		int father = (child - 1) / 2;
		if (heap.dateArr[child].priority > heap.dateArr[father].priority) {
			Date temp = heap.dateArr[father];
			heap.dateArr[father] = heap.dateArr[child]; heap.dateArr[child] = temp;
			child = father;
		}
		else {
			break;
		}

	}
	heap.size++;

}

Date::Date() {
	date = 0; priority = 0;
}

