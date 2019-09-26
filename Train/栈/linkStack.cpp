#include"LinkStack.h"
#include<string.h>
namespace xmj{
	LinkStack::LinkStack() {
		length = 0;
		top = nullptr; base = nullptr;
	}
	DateLink::DateLink() {
		//date = new DateType();
		date = 0;
		front = nullptr;
		next = nullptr;
	}
	//DateLink::DateLink(const DateLink& other) {
	//	date = new DateType();
	//	memcpy(date, other.date, sizeof(DateType));
	//	next = nullptr;
	//}
	//const DateLink& DateLink::operator=(const DateLink& other) {
	//	date = new DateType();
	//	memcpy(date, other.date, sizeof(DateType));
	//	next = nullptr; return other;
	//}
	//DateLink::~DateLink() { delete date; }
	bool pushLinkStack(LinkStack& linkStack, DateLink& dateNode, DLhead& head) {
		if (linkStack.length == MAX_SIZE)return false;		
		if (head.next == nullptr&&linkStack.base== linkStack.top) {
			head.next = &dateNode; dateNode.front = &head;
			linkStack.top = &dateNode; linkStack.length++;
			return true; 
		}
		linkStack.top->next = &dateNode; dateNode.front = linkStack.top;
		linkStack.top = &dateNode; linkStack.length++;
		return true;
	}

	bool popLinkStack(LinkStack& linkStack, DateLink& dateNode) {
		if (linkStack.length == 0)return false;	
		 DateLink* tp = linkStack.top;
		 dateNode = *tp;
		 linkStack.top = tp->front;
		 linkStack.top->next = nullptr; delete tp;
		 linkStack.length--;
		return true;
	}

	size_t LinkStackCount(LinkStack& linkStack) {
		return size_t(linkStack.length);
	}

	bool deleteLinkStack(LinkStack& linkStack) {
		if (linkStack.length==0)return false;
		while ((linkStack.length)>0) {
			DateLink* tp = linkStack.top;			
			linkStack.top = tp->front;
			linkStack.top->next = nullptr; delete tp;
			linkStack.length--;
		}
		linkStack.base=nullptr; linkStack.top = linkStack.base;
		return true;
	}	
	bool initLinkStack(LinkStack& linkStack, DLhead& head) {
		if (&linkStack == nullptr || !&head)return false;
		linkStack.base = &head;
		linkStack.top = linkStack.base;
		return true;
	}
}





