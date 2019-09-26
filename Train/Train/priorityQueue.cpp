#include"PriorityQueue.h"
 namespace priorityQ{
	 PriorityQueue::PriorityQueue() {
		 length = 0; front = nullptr; rear = nullptr; maxPriority = MAX_PRIORITY;
	 }
	 qNode::qNode() {
		 date = 0; next = nullptr; priority = 0;
	 }
	 void addPriorityQueue(qNode& qn, QnH& head, PriorityQueue& lq) {
		 if (head.next == nullptr || lq.front == nullptr) { head.next = &qn; lq.front = &qn; lq.length++; cout << "添加成功\n"; return; }
		 qNode* p = head.next;
		 while (1) {
			 if (p->next == nullptr) {
				 p->next = &qn;  break;
			 }
			 else {
				 p = p->next;
			 }
		 }lq.rear = &qn; lq.length++;
		 cout << "添加成功\n";
	 }


	 void subPriorityQueue(PriorityQueue& pq, QnH& head) {
		 if (pq.front == nullptr) { cout << "移除失败\n"; return; }
		 qNode* p = &head; qNode* tp = pq.front;
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
				 if (p->next == pq.front) {//第一个节点优先级最高,后面有节点
					 pq.front = dp->next; cout << "第一个节点（后有）";
				 }
				 else {
					 cout << "其他节点（后有）";
				 }
				 p->next = dp->next;  
			 }
			 else {
				 
				 //else {//最后节点优先级最高
					 pq.rear = p; p->next = nullptr; cout << "最后节点";
				// }

			 }
			 
		 }
		 else {
			 if (p->next == pq.front) {//第一个节点优先级最高,后面无节点
				 pq.front = nullptr; pq.rear = nullptr; p->next = nullptr; cout << "第一个节点（后无）";
			 }
		 }delete dp; cout << "移除成功\n";
		 pq.length--;
	 }

	 bool deletePriorityQueue(PriorityQueue& lq, QnH head) {
		 if (head.next == NULL || lq.front == nullptr) { cout << "没有元素删除失败,如果头节点在堆请自行清空\n"; return false; }
		 qNode* p;
		 p = head.next;
		 while (p) {
			 qNode* tp = p;
			 p = p->next;
			 delete tp;
		 }head.next = NULL; lq.front = nullptr; lq.rear = nullptr;
		 cout << "删除成功\n"; return true;
	 }

	 qNode** findQn(PriorityQueue& llh, Date date) {
		 if (llh.front == NULL) { cout << "查找失败\n"; return NULL; }
		 qNode* p; qNode** pArr = new qNode * [FIND_COUNT](); int count = 0;
		 p = llh.front;
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
		 }
	 }

	 void printfPriorityQueue(PriorityQueue& lq) {
		 if (!lq.front) {
			 cout << "队列为空"; return;
		 }
		 qNode* qn = lq.front;
		 cout << lq.front->date << "\tfront优先级：" << lq.front->priority << endl;
		 cout << lq.rear->date << "\trear优先级：" << lq.rear->priority << endl;
		 for (int i = 0; i < lq.length; i++) {
			 cout << qn->date << "优先级："<<qn->priority<<"\t";
			 qn = qn->next;
		 }
	 }
 }

