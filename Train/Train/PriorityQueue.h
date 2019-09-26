#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<iostream>
using namespace std;
namespace priorityQ{//优先队列
	constexpr auto FIND_COUNT = 10;
	constexpr auto MAX_PRIORITY = 5;
	typedef int Date;

	typedef struct qNode {
		int priority;
		Date date; qNode* next;
		qNode();
	}QnH;

	typedef qNode* qNodePtr;

	typedef struct PriorityQueue {

		int length; qNodePtr front; qNodePtr rear; int maxPriority;
		PriorityQueue();
	}PQ;
	void addPriorityQueue(qNode& qn, QnH& head, PriorityQueue& lq);
	void subPriorityQueue(PriorityQueue& lq, QnH& head);
	bool deletePriorityQueue(PriorityQueue& lq, QnH head);
	qNode** findQn(PriorityQueue& llh, Date date);
	void printfPriorityQueue(PriorityQueue& lq);
}



#endif