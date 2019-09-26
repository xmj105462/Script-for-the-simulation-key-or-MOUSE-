#pragma once
#ifndef SQ_STACK_H
#define SQ_STACK_H

#define MAX_SIZE 20
typedef int DateType;
typedef struct SQ_STACK {
	DateType* top;
	DateType* base;
	SQ_STACK();
}SQ_S;
bool initSqStack(SQ_STACK& sqStack, size_t maxSize);
bool pushSqStack(SQ_STACK& sqStack,DateType date);
bool popSqStack(SQ_STACK& sqStack, DateType& popDate);
size_t sqStackCount(SQ_STACK& sqStack);
bool deleteSqStack(SQ_STACK& sqStack);
#endif // !SQ_STACK_H
