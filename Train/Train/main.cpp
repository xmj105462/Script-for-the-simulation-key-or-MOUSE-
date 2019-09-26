
//#include"Queue.h"
//#include"LinkQueue.h"
//#include"LoopQueue.h"
//#include"PriorityQueue.h"
//using namespace priorityQ;
#include<iostream>
//typedef struct Node {
//	Node* front;
//	Node* next;
//}Ts;
//typedef struct MyStruct {
//	int a;
//	int b;
//	Node ts;
//}MS;
int main() {
	/*Queue q;//数组队列
	for (size_t i = 0; i < 5; i++) {
		addQueue(&q, i+1);
	}
	subQueue(&q); subQueue(&q);
	printfQueue(&q);*/
	//LinkQueue lq; QnH head;//链队列
	//for (size_t i = 0; i < 5; i++) {
	//	qNode *qn = new qNode();
	//	qn->date = i+1;
	//	addLinkQueue(*qn, head,lq);
	//}
	//subLinkQueue(lq,head); subLinkQueue(lq, head);
	////deleteLinkQueue(lq, head);
	//qNode** qn=findQn(lq, 5);
	//cout << "查找值为"<<(*(qn))->date << endl;
	//printfLinkQueue(lq);
	//LoopQueue lq;//循环数组队列
	//for (size_t i = 0; i < 5; i++) {
	//	addLoopQueue(&lq, i+1);
	//}
	//subLoopQueue(&lq); subLoopQueue(&lq);
	//printfLoopQueue(&lq);
	//优先队列测试
	//PriorityQueue pq; QnH head;
	///*qNode* qn = new qNode();
	//qn->date = 6; qn->priority = MAX_PRIORITY;
	//addPriorityQueue(*qn, head, pq);*/
	//for (size_t i = 0; i < 5; i++) {
	//	qNode *qn = new qNode();
	//	qn->date = i + 1; qn->priority = i;
	//	addPriorityQueue(*qn, head,pq);
	//}
	//qNode* qn2 = new qNode();
	//qn2->date = 7; qn2->priority = 3;
	//addPriorityQueue(*qn2, head, pq);
	//subPriorityQueue(pq,head); //subPriorityQueue(pq, head);
	//
	////deletePriorityQueue(pq, head);
	//qNode** qn=findQn(pq, 5);
	////cout << "查找值为"<<(*(qn))->date << endl;
	//printfPriorityQueue(pq);
	/*MS ms; Node n; Node* p;
	ms.a = 7; n.next = &ms.ts; p = n.next;
	((MS*)(((int)p) - 8))->b=2;
	std::cout << ms.b;*/
	system("pause");
	return 0;
}