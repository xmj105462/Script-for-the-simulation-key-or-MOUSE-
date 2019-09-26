#include"SqStack2.h"
SQ_STACK2::SQ_STACK2() {
	top = 0; base = nullptr;
}

bool initSqStack2(SQ_STACK2& sqStack, size_t maxSize) {
	if (&sqStack == nullptr || maxSize < 1)return false;
	sqStack.base = new DateType[maxSize]();
	return true;
}

bool pushSqStack2(SQ_STACK2& sqStack, DateType date) {
	if (!&sqStack || sqStack.top == MAX_SIZE || !sqStack.base)return false;
	*(sqStack.base+ sqStack.top) = date; sqStack.top++;
	return true;
}

bool popSqStack2(SQ_STACK2& sqStack, DateType& popDate) {
	if (!&sqStack || sqStack.top == 0 || !sqStack.base)return false;
	popDate = *(sqStack.base + --sqStack.top);
	return true;
}

size_t sqStackCount2(SQ_STACK2& sqStack) {
	return size_t(sqStack.top);
}

bool deleteSqStack2(SQ_STACK2& sqStack) {
	if (!&sqStack)return false;
	sqStack.top = 0;
	delete sqStack.base;
	return true;
}
