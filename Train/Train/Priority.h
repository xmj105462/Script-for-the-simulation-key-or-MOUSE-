#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<iostream>
typedef int Date;

typedef struct qNode {

	Date date; qNode* next;
	qNode();
}QnH;

typedef qNode* qNodePtr;

typedef struct PriorityQueue {

	int length; qNodePtr front; qNodePtr rear;
	PriorityQueue();
}PQ;
void addPriorityQueue(qNode& qn, QnH& head, PriorityQueue& lq);
void subPriorityQueue(PriorityQueue& lq, QnH& head);
bool deletePriorityQueue(PriorityQueue& lq, QnH head);
qNode** findQn(PriorityQueue& llh, Date date);
void printfPriorityQueue(PriorityQueue& lq);



#endif