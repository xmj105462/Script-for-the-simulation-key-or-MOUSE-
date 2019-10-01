#pragma once
#ifndef MAZE_H
#define MAZE_H

#define MAX_SIZE 30

	typedef struct Position {
		int x; int y;
		Position();
	}Pos; 
	/*typedef struct SQ_STACK {
		Position* top;
		Position* base;
		size_t mapValue;
		SQ_STACK();
	}SQ_S;*/
	typedef struct DateLink {
		//DateType* date;
		Position date;
		DateLink* front;
		DateLink* next;
		DateLink();
		/*DateLink(const DateLink& other);
		const DateLink& operator=(const DateLink& other);
		~DateLink();*/
	}DLhead;
	typedef DateLink* DateLink_ptr;
	typedef struct LinkStack {
		size_t length;
		DateLink_ptr top;//当前人物位置
		size_t mapValue;
		LinkStack();
	}LS;
	/*bool initSqStack(SQ_STACK& sqStack, size_t maxSize);
	bool pushSqStack(SQ_STACK& sqStack, Position date);
	bool popSqStack(SQ_STACK& sqStack, Position& frontPosition);	
	size_t sqStackCount(SQ_STACK& sqStack);
	bool deleteSqStack(SQ_STACK& sqStack);*/
	bool initLinkStack(LinkStack& linkStack, DLhead& head);
	bool pushLinkStack(LinkStack& linkStack, DateLink& dateNode, DLhead& head);
	bool popLinkStack(LinkStack& linkStack, DateLink& dateNode);
	size_t LinkStackCount(LinkStack& linkStack);
	bool deleteLinkStack(LinkStack& linkStack);
	


#endif // !MAZE_H
