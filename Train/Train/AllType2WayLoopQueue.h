#pragma once
#ifndef AT2WLQ_H
#define AT2WLQ_H
#include<iostream>
using namespace std;
namespace allType2WayLoopQ {//优先队列
	constexpr auto FIND_COUNT = 10;
	constexpr auto MAX_PRIORITY = 5;
	typedef int Date;

	typedef struct qNode {
		qNode* front; qNode* next;
		qNode();
	}QnH;

	typedef qNode* qNodePtr;

	typedef struct AllType2WayLoopQueue {

		int length; qNodePtr qHead; qNodePtr rear; int maxPriority;
		AllType2WayLoopQueue();
	}AY2WLQ;
	void addAllType2WayLoopQueue(qNode& qn, QnH& head, AllType2WayLoopQueue& lq);
	void subAllType2WayLoopQueue(AllType2WayLoopQueue& lq, QnH& head);
	bool deleteAllType2WayLoopQueue(AllType2WayLoopQueue& lq, QnH head);
	qNode** findQn(AllType2WayLoopQueue& llh, Date date);
	void printfAllType2WayLoopQueue(AllType2WayLoopQueue& lq);
}
#endif // !AT2WLQ_H