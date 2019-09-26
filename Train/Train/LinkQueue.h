#pragma once
#ifndef LINKQUEUE_H
#define LINKQUEUE_H//¡¥±Ì∂”¡–
namespace linkQ{
	typedef int Date;

	typedef struct qNode {
		Date date; qNode* next;
		qNode();
	}QnH;

	typedef qNode* qNodePtr;

	typedef struct LinkQueue {

		int length; qNodePtr front; qNodePtr rear;
		LinkQueue();
	}LQ;
	void addLinkQueue(qNode& qn, QnH& head, LinkQueue& lq);
	void subLinkQueue(LinkQueue& lq, QnH& head);
	bool deleteLinkQueue(LinkQueue& lq, QnH head);
	qNode** findQn(LinkQueue& llh, Date date);
	void printfLinkQueue(LinkQueue& lq);
}



#endif // !LINKQUEUE_H
