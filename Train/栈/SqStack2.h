#pragma once
#ifndef SQ_STACK2_H
#define SQ_STACK2_H

#define MAX_SIZE 20
typedef int DateType;
typedef struct SQ_STACK2 {
	size_t top;
	DateType* base;
	SQ_STACK2();
}SQ_S2;
bool initSqStack2(SQ_STACK2& sqStack, size_t maxSize);
bool pushSqStack2(SQ_STACK2& sqStack, DateType date);
bool popSqStack2(SQ_STACK2& sqStack, DateType& popDate);
size_t sqStackCount2(SQ_STACK2& sqStack);
bool deleteSqStack2(SQ_STACK2& sqStack);
#endif // !SQ_STACK2_H