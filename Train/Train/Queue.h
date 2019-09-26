#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
using namespace std;
constexpr auto MAX_LENGTH = 10;

typedef int	Date;
typedef struct Queue { 
	Date* arr ; 
	int front; int rear; 
	Queue();	
}Que;

void initQueue();
int addQueue(Queue* q, Date date);
int subQueue(Queue* q);
void printfQueue(Queue*q);
#endif // !QUEUE_H
