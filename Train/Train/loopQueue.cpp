#include"LoopQueue.h"

LoopQueue::LoopQueue() {
	arr = new int[MAX_LENGTH]();
	front = 0; rear = 0;
}

void initLoopQueue() {}

int addLoopQueue(LoopQueue* q, Date date) {
	if (!q ||(q->rear+1) % MAX_LENGTH ==q->front)return 0;
	q->arr[q->rear] = date;
	q->rear++; q->rear = q->rear % MAX_LENGTH;
	
	return 0;
}

int subLoopQueue(LoopQueue* q) {
	if (!q||q->front==q->rear)return 0;
	/*for (int i = q->front; i < q->rear; i++) {
		q->arr[i] = q->arr[i + 1];
	}*/q->front++; q->front = q->front % MAX_LENGTH;
	return 0;
}

void printfLoopQueue(LoopQueue* q) {
	for (int i = q->front; i < q->rear; i++) {
		i = i % MAX_LENGTH;
		cout << q->arr[i] << "\t";
	}
}
