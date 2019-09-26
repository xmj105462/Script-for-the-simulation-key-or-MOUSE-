#include"Queue.h"//╤сап

void initQueue() {
	
}

int addQueue(Queue* q, Date date) {
	if (!q || q->rear == MAX_LENGTH)return 0;
	q->arr[q->rear] = date;
	q->rear++;
	return 0;
}

int subQueue(Queue* q) {
	if (!q)return 0;
	for (int i =q->front; i < q->rear; i++) {
		q->arr[i] = q->arr[i+1];
	}q->rear--;
	return 0;
}

void printfQueue(Queue* q) {
	for (int i =0; i< q->rear; i++) {
		cout << q->arr[i]<<"\t";
	}
}

Queue::Queue() {
	arr = new int[MAX_LENGTH]();
	front = 0; rear = 0;
}
