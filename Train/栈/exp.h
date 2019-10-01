#pragma once
#pragma once
#include<stdio.h> 
#include<stdlib.h> 
#include<string>
#include <iostream> 
#define MAXSIZE 100 
#define MaxSize 128 //预先分配空间，这个数值根据实际需要预估确定 
using namespace std;
typedef int ElemType;
typedef struct _SqStack {
	ElemType* base; //栈底指针
	ElemType* top; //栈顶指针 
}SqStack;
bool InitStack(SqStack& S) //构造一个空栈 S
{
	S.base = new ElemType[MaxSize];//为顺序栈分配一个最大容量为 Maxsize 的空间
	if (!S.base)return false; //空间分配失败 		 
	S.top = S.base;
	//top 初始为 base，空栈 
	return true;
}
bool isLarger(const int& lhs, const int& rhs);
int operate(int left, int right, int op);
bool PushStack(SqStack& S, ElemType e)
// 插入元素 e 为新的栈顶元素 
{
	if (S.top - S.base == MaxSize)return false; //栈满 
	*(S.top) = e; //元素 e 压入栈顶，然后栈顶指针加 1，等价于*S.top=e; 
	++S.top; return true;
}
bool PopStack(SqStack& S, ElemType& e) //删除 S 的栈顶元素，暂存在变量 e 中
{
	if (S.base == S.top) { //栈空 
		return false;
	}e = *(--S.top); //栈顶指针减 1，将栈顶元素赋给 e 
	return true;
}
ElemType* GetTop(SqStack& S) //返回 S 的栈顶元素，栈顶指针不变 
{
	if (S.top != S.base) { //栈非空
		return S.top - 1; //返回栈顶元素的值，栈顶指针不变
	}
	else { return NULL; }
}
int GetSize(SqStack& S) {//返回栈中元素个数 
	return (S.top - S.base);
}
bool IsEmpty(SqStack& S) {//判断栈是否为空 
	if (S.top == S.base) { return true; }
	else { return false; }
}
void DestoryStack(SqStack& S) {//销毁栈 
	if (S.base) { free(S.base); S.base = NULL; S.top = NULL; }
}

bool isLarger(const int& lhs, const int& rhs) {//比较 lhs 的优先级是否不高于 rhs，rhs 表示栈顶的符号 
	if ((rhs == '+' || rhs == '-') && (lhs == '*' || lhs == '/')) {
		return true;
	}
	return false;
}
int operate(int left, int right, int op)//对运算符求值
{
	int result = 0; cout << "left:" << left << (char)op << " right:" << right  << endl;
	switch (op) {
	case '+': result = left + right; break;
	case '-': result = left - right; break;
	case '*': result = left * right; break;
	case '/': result = left / right; break;
	default: break;
	}
	cout << "result: " << result << endl;
	return result;
}
int calculate(string input) {
	SqStack data_stack;//操作数堆栈
	SqStack opt_stack; //运算符堆栈 
	int status = 0; //0-接受左操作数 1-接受运算符 "+-*/" 2-接受右操作数 
	int ldata = 0, rdata = 0; char last_opt = '\0';

	InitStack(data_stack); InitStack(opt_stack);//初始化栈：操作数和操作符 
	for (size_t i = 0; i < input.length(); i++) {
		if (isspace(input[i])) continue;//空格键等忽略掉 
		switch (status) {
		case 0: if (isdigit(input[i])) { //如果是0-9之间的数，就返回非0的数值，否则返回0
			ldata *= 10; ldata += input[i] - '0';
		}
				else {
			cout << "得到左操作数:" << ldata << endl; PushStack(data_stack, ldata);//左操作数入栈 
			i--; status = 1;//遇到运算符跳回前一个继续。
		}
				break;
		case 1:
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
				if (IsEmpty(opt_stack)) {//第一个运算符,暂时不做任何处理，运 算符先入栈保存 
					cout << "符号栈为空" << endl; PushStack(opt_stack, input[i]);//操作符入栈 
					cout << "符号" << (char)input[i] << "入栈" << endl; status = 2;
				}
				else {//非第一个运算符，则与之前的运算符比较优先级 
					cout << "当前符号栈最高:" << (char)(*GetTop(opt_stack)) << " &对比新符号 " << input[i] << endl;
					if (isLarger(input[i], *GetTop(opt_stack))) {//新运算符是否比前一个大
						cout << "true" << endl; PushStack(opt_stack, input[i]);//操作符入栈 
						cout << "符号" << (char)input[i] << "入栈" << endl; status = 2; rdata = 0;
					}
					else {//当前运算符的优先级不高于前一个运算符，则计算 前一个运算符的值 
						int left = 0, right = 0;
						int opt;
						cout << "false" << endl;
						do {
							PopStack(data_stack, right);
							PopStack(data_stack, left); PopStack(opt_stack, opt);
							cout << "符号" << (char)opt << "出栈" << endl;
							cout << "计算前一个运算符" << (char)opt << endl;
							int result = operate(left, right, opt);
							PushStack(data_stack, result);
						}
						while (!IsEmpty(opt_stack) && !isLarger(input[i], *GetTop(opt_stack)));
						PushStack(opt_stack, input[i]);
						cout << "符号" << (char)input[i] << "入栈" << endl;
						status = 2; rdata = 0;
					}
				}
			}
			else if (input[i] == '=') {//计算结果 
				int opt, result;
				do {
					PopStack(data_stack, rdata);
					PopStack(data_stack, ldata);
					PopStack(opt_stack, opt);
					result = operate(ldata, rdata, opt);
					PushStack(data_stack, result);
				}
				while (!IsEmpty(opt_stack)); return result;
			}
			else { cerr << "输入运算符错误！" << endl; }break;
		case 2: if (isdigit(input[i])) { rdata *= 10; rdata += input[i] - '0'; }
				else {
			cout << "得到右操作数:" << rdata << endl; PushStack(data_stack, rdata);//右操作数入栈 
			i--;
			status = 1;
		}break;
		}
	}return -1;//最后的结果为栈顶元素
}
