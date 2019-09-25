#include"Heap.h"
//#include"priorityQueue.h"
//#include"MinHeap.h"


int main() {
	H heap; heap.capacity = CAPACITY;
	int arr[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
	initHeap(heap, 17);
	heap.builtHeap(arr);//17      16      14      15      9       11      13      10      4       3       8       2       6       5       12      1       7	
	//heap.insertHeap(666,heap.size);
	//heap.popHeap(); heap.popHeap(); 
	//heap.popHeap(); //heap.popHeap(); //heap.popHeap();
	//heap.sortHeap();//17        16      15      14      12      10      9       8       7       6       5       13      11      4       3       2       1
	H hCopy = heap; heap.findFrontHeap(10,hCopy);
	printfHeap(heap);
	//堆实现优先队列
	//HPQ heap; heap.capacity = CAPACITY;
	//Date arr[17] = {};//45,4,78,556,79,123,47,5,66,77,556,79,123,47,5,66,77 
	//for (size_t i = 0; i < 17; i++) {
	//	arr[i].date = i + 1; arr[i].priority = i + 1;
	//}
	//initHeapPriQueue(heap, 17);
	//heap.builtHeapPriQueue(arr);//666     556     123     556     79      123     47      66      77      77      78      45      79      47      5       4       66      5	
	////heap.insertHeap(666,heap.size);
	//heap.popHeapPriQueue();//556     556     123     77      79      123     47      66      66      77      78      45      79      47      5       4       66
	//printfHeapPriQueue(heap);
	//最小堆
	//MinHeap heap; heap.capacity = CAPACITY;
	//int arr[17] = { 45,4,78,556,79,123,47,5,66,77,556,79,123,47,5,66,77 };//
	///*for (size_t i = 0; i < 17; i++) {
	//	arr[i].date = i + 1; arr[i].priority = i + 1;
	//}*/
	//initHeap(heap, 17);
	//heap.builtHeap(arr);//666     556     123     556     79      123     47      66      77      77      78      45      79      47      5       4       66      5	
	////heap.insertHeap(666,heap.size);
	//heap.popHeap();//556     556     123     77      79      123     47      66      66      77      78      45      79      47      5       4       66
	//printfHeap(heap);
	system("pause");
	return 0;
}