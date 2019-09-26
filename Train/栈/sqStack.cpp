#include"SqStack.h"

SQ_STACK::SQ_STACK() {
	top = nullptr; base = nullptr;
}

bool initSqStack(SQ_STACK& sqStack,size_t maxSize) {
	if(&sqStack==nullptr||maxSize<1)return false;
	sqStack.base = new DateType[maxSize]();
	sqStack.top = sqStack.base;
	return true;
}

bool pushSqStack(SQ_STACK& sqStack, DateType date) {
	if (!&sqStack || sqStack.top - sqStack.base == MAX_SIZE || !sqStack.base)return false;
	*sqStack.top = date; sqStack.top++;
	return true;
}

bool popSqStack(SQ_STACK& sqStack,DateType& popDate) {
	if (!&sqStack || sqStack.top - sqStack.base == 0 || !sqStack.base)return false;
	popDate = *--sqStack.top;
	return true;
}

size_t sqStackCount(SQ_STACK& sqStack) {
	return size_t(sqStack.top-sqStack.base);
}

bool deleteSqStack(SQ_STACK& sqStack) {
	if (!&sqStack)return false;
	sqStack.top = sqStack.base;
	delete sqStack.base;	
	return true;
}
