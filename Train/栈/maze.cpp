#include"Maze.h"

	//SQ_STACK::SQ_STACK() {
	//	top = nullptr; base = nullptr;
	//	//front = nullptr;
	//	mapValue = 1;
	//}
LinkStack::LinkStack() {
	length = 0;
	top = nullptr; mapValue = 1;
}
DateLink::DateLink() {
	//date = new DateType();
	//date.x = 0; date.y = 0;
	front = nullptr;
	next = nullptr;
}

	//bool initSqStack(SQ_STACK& sqStack, size_t maxSize) {
	//	if (maxSize < 1)return false;
	//	sqStack.base = new Position[maxSize]();
	//	sqStack.top = sqStack.base;
	//	return true;
	//}

	//bool pushSqStack(SQ_STACK& sqStack, Position date) {
	//	if (sqStack.top - sqStack.base == MAX_SIZE || !sqStack.base)return false;
	//	*sqStack.top = date; ++sqStack.top; ++sqStack.mapValue;
	//	map[date.y][date.x] = sqStack.mapValue;
	//	return true;
	//}

	//bool popSqStack(SQ_STACK& sqStack, Position& frontPosition) {//接收前一个位置
	//	if (sqStack.top - sqStack.base == 0 || !sqStack.base)return false;
	//	--sqStack.top;
	//	frontPosition = *(sqStack.top-1); --sqStack.mapValue;
	//	map[sqStack.top->y][sqStack.top->x] = sqStack.mapValue;
	//	return true;
	//}
	//size_t sqStackCount(SQ_STACK& sqStack) {
	//	return size_t(sqStack.top - sqStack.base);
	//}

	//bool deleteSqStack(SQ_STACK& sqStack) {
	//	if (!&sqStack)return false;
	//	sqStack.top = sqStack.base;
	//	delete sqStack.base;
	//	return true;
	//}
	Position::Position() {
		x = 0; y = 0;
	}
	bool pushLinkStack(LinkStack& linkStack, DateLink& dateNode, DLhead& head) {
		if (linkStack.length == MAX_SIZE)return false;
		if (head.next == nullptr) {
			head.next = &dateNode; dateNode.front = &head;
			linkStack.top = &dateNode; linkStack.length++;
			return true;
		}
		linkStack.top->next = &dateNode; dateNode.front = linkStack.top;
		linkStack.top = &dateNode; linkStack.length++;
		return true;
	}

	bool popLinkStack(LinkStack& linkStack, DateLink& popNode) {
		if (linkStack.length == 0)return false;
		DateLink* tp = linkStack.top;
		popNode = *tp;
		linkStack.top = tp->front;
		linkStack.top->next = nullptr; delete tp;
		linkStack.length--;
		return true;
	}

	size_t LinkStackCount(LinkStack& linkStack) {
		return size_t(linkStack.length);
	}

	bool deleteLinkStack(LinkStack& linkStack) {
		if (linkStack.length == 0)return false;
		while ((linkStack.length) > 0) {
			DateLink* tp = linkStack.top;
			linkStack.top = tp->front;
			linkStack.top->next = nullptr; delete tp;
			linkStack.length--;
		}
		linkStack.top = nullptr;
		return true;
	}
	bool initLinkStack(LinkStack& linkStack, DLhead& head) {
		if (&linkStack == nullptr || !&head)return false;
		linkStack.top = &head;
		return true;
	}

