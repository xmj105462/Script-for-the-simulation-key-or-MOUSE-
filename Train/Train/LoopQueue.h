#pragma once
#ifndef LOOPQUEUE_H
#define LOOPQUEUE_H
#include<iostream>
using namespace std;
constexpr auto MAX_LENGTH = 5;

typedef int	Date;
typedef struct LoopQueue {
	Date* arr;
	int front; int rear;
	LoopQueue();
}lQue;

void initLoopQueue();
int addLoopQueue(LoopQueue* q, Date date);
int subLoopQueue(LoopQueue* q);
void printfLoopQueue(LoopQueue* q);
#endif // !LOOPQUEUE_H
