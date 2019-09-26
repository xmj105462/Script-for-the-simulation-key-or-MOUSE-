#include"AllType2WayLoopQueue.h"
//inline void initAllType2WayLLN(AllType2WayLLN* ll1, AllType2WayH& lllh);
namespace allType2WayLoopQ{
	AllType2WayLoopQueue::AllType2WayLoopQueue() { 
		length = 0; qHead = nullptr; rear = nullptr; maxPriority = MAX_PRIORITY;
	}
	qNode::qNode() {
		next = nullptr; front = nullptr;
	}
	void addAllType2WayLoopQueue(qNode& qn, QnH& head, AllType2WayLoopQueue& lq) {
		if (head.next == nullptr || lq.qHead == nullptr) { head.next = &qn; lq.qHead = &qn; lq.length++; cout << "添加成功\n"; return; }
		qNode* p = head.next;
		while (1) {
			if (p->next == nullptr) {
				p->next = &qn;  break;
			}
			else {
				p = p->next;
			}
		}lq.rear = &qn; lq.length++;
		cout << "添加成功\n";/*if (lllh.p_next == &lllh || lllh.p_next == nullptr) {
		lllh.p_next = &ll1; ll1.p_front = &lllh;
		ll1.p_next = &lllh;//尾连头
		lllh.p_front = &ll1;
	}
	else {
		ll1.p_next = lllh.p_next; lllh.p_next->p_front = &ll1; ll1.p_front = &lllh;
		initAllType2WayLLN(lllh.p_next, lllh);
		lllh.p_next = &ll1;

	}*/
	}

	void subAllType2WayLoopQueue(AllType2WayLoopQueue& pq, QnH& head) {
		if (pq.qHead == nullptr) { cout << "移除失败\n"; return; }
		qNode* p = &head; qNode* tp = pq.qHead;
		qNode* dp = p->next;
		if (tp->next) {
			while (tp->next) {
				if (p->next->priority == pq.maxPriority)break;
				if ((p->next->priority) < (tp->next->priority)) {
					p = tp;
				}
				tp = tp->next;
			}
			dp = p->next;
			if (dp->next) {
				if (p->next == pq.qHead) {//第一个节点优先级最高,后面有节点
					pq.qHead = dp->next; cout << "第一个节点（后有）";
				}
				else {
					cout << "其他节点（后有）";
				}
				p->next = dp->next;
			}
			else {
				pq.rear = p; p->next = nullptr; cout << "最后节点";
			}
		}
		else {
			if (p->next == pq.qHead) {//第一个节点优先级最高,后面无节点
				pq.qHead = nullptr; pq.rear = nullptr; p->next = nullptr; cout << "第一个节点（后无）";
			}
		}delete dp; cout << "移除成功\n";
		pq.length--;/*if (llh.p_next == NULL || i <= 0 || llh.p_next == &lllh) { cout << "移除失败\n"; return NULL; }
	size_t j = 2;
	AllType2WayLLN* p = llh.p_next;
	while ((p) != &lllh || p != nullptr) {
		if (i == 1) {
			if (p) {
				AllType2WayLLN* tp = p->p_next;
				llh.p_next = p->p_next; tp->p_front = &llh;
				  cout << "移除成功\n"; return tp;
			}
		}
		else if (j == i) {
			if (p->p_next == nullptr || p->p_next == &lllh) { cout << "移除失败\n"; return NULL; }
			AllType2WayLLN* tp = (*(p)).p_next->p_next;
			AllType2WayLLN* tp1 = (*(p)).p_next;
			p->p_next = tp; tp->p_front = p;
			   cout << "移除成功\n"; return tp;
		}
		else if (j < i) {
			if ((*(p)).p_next == NULL || (*(p)).p_next == &lllh) {
				cout << "移除失败\n"; return NULL;
			}
			p = (*(p)).p_next; j++;
		}
	}cout << "移除失败\n";
	return nullptr;*/
	}

	bool deleteAllType2WayLoopQueue(AllType2WayLoopQueue& lq, QnH head) {
		if (head.next == NULL || lq.qHead == nullptr) { cout << "没有元素删除失败,如果头节点在堆请自行清空\n"; return false; }
		qNode* p;
		p = head.next;
		while (p) {
			qNode* tp = p;
			p = p->next;
			delete tp;
		}head.next = NULL; lq.qHead = nullptr; lq.rear = nullptr;
		cout << "删除成功\n"; return true;
	}

	qNode** findQn(AllType2WayLoopQueue& llh, Date date) {
		if (llh.qHead == NULL) { cout << "查找失败\n"; return NULL; }
		qNode* p; qNode** pArr = new qNode * [FIND_COUNT](); int count = 0;
		p = llh.qHead;
		while (p) {
			if ((p->date) == date) {
				cout << "查找成功\t所在节点地址为" << p << endl; pArr[count] = p; count++;
				p = p->next;
				//continue;
			}
			else {
				p = p->next;
			}
		}if (pArr[0]) {
			return pArr;
		}
		else {
			cout << "查找失败\n"; return NULL;
		}/*if (llh.p_next == NULL || llh.p_next == &llh) { cout << "查找失败\n"; return NULL; }
	AllType2WayLLN* p; AllType2WayLLN** pArr = new AllType2WayLLN * [FIND_COUNT](); int count = 0;
	p = llh.p_next;
	while (p != &llh) {
		////if (*(p->date) == i) {
		//	cout << "查找成功\t所在节点地址为" << p << endl; pArr[count] = p; count++;
		//	p = p->p_next;
		////}
		//else {
		//	p = p->p_next;
		//}
	}if (pArr[0]) {
		return pArr;
	}
	else {
		cout << "查找失败\n"; return nullptr;
	}*/
	}

	void printfAllType2WayLoopQueue(AllType2WayLoopQueue& lq) {
		if (!lq.qHead) {
			cout << "队列为空"; return;
		}
		qNode* qn = lq.qHead;
		cout << lq.qHead->date << "\tqHead优先级：" << lq.qHead->priority << endl;
		cout << lq.rear->date << "\trear优先级：" << lq.rear->priority << endl;
		for (int i = 0; i < lq.length; i++) {
			cout << qn->date << "优先级：" << qn->priority << "\t";
			qn = qn->next;
		}/*if (llh.p_next == NULL || llh.p_next == &llh) { cout << "输出失败\n"; return; }
	AllType2WayLLN* p;
	p = llh.p_next;
	while (p != &llh) {
		cout << *((int*)(((int)p)-4)) << "\t";
		p = p->p_next;
	}cout << "正向输出成功\n";
	p = llh.p_front;
	while (p != &llh) {
		cout << *((int*)(((int)p) - 4)) << "\t";
		p = p->p_front;
	}cout << "反向输出成功\n";*/
	}
}
//inline void initAllType2WayLLN(AllType2WayLLN* ll1, AllType2WayH& llh) {
//	if (ll1->p_next == nullptr) {
//		ll1->p_next = &llh;
//		llh.p_front = ll1;
//	}
//}
