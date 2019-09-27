#pragma once
#ifndef LINK_STACK_H
#define LINK_STACK_H
namespace xmj{
#define MAX_SIZE 20
	/*
	******作业思路
	******采用双向链表
	*****栈底指向头节点，栈顶指向入栈的节点。出栈：栈顶指针利用节点反方向指针折返
	*/
	typedef int DateType;
	typedef struct DateLink {
		//DateType* date;
		DateType date;
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
		DateLink_ptr top;		
		LinkStack();
	}LS;
	bool initLinkStack(LinkStack& linkStack, DLhead& head);
	bool pushLinkStack(LinkStack& linkStack, DateLink& dateNode, DLhead& head);
	bool popLinkStack(LinkStack& linkStack, DateLink& dateNode);
	size_t LinkStackCount(LinkStack& linkStack);
	bool deleteLinkStack(LinkStack& linkStack);
}

#endif // !LINK_STACK_H
