#ifndef __STACK_H__
#define __STACK_H__

#include<iostream>

using namespace std;

template <class ValType>
class Stack
{
	int Top;//вершина стека
	ValType *Mem;//память для стека
	int SizeMem;//размер стека
	bool isArend;//берётся ли память самостоятельно или арендуется?
public:

	Stack(int n = 100);//
	Stack(ValType *Mem, int n);//
	~Stack();
	void Push(ValType val);//положить элемент в стек
	bool isFull();//проверка полноты стека
	ValType Pop();//вернуть значение элемента из стека и удалить вершину
	ValType top();//вернуть значение элемента из стека 
	bool isEmpty();//проверка пустоты стека
};


template <class ValType>
Stack<ValType>::Stack(int n)
{
	Top = -1;
	isArend = false;
	SizeMem = n;
	Mem = new ValType[n];
}

template <class ValType>
Stack<ValType>::Stack(ValType *Mem, int n)
{
	Top = -1;
	isArend = true;
	this->Mem = Mem;
	SizeMem = n;
}

template <class ValType>
Stack<ValType>::~Stack()
{
	if (!isArend)
		delete[] Mem;
}

template <class ValType>
void Stack<ValType>::Push(ValType val)
{
	if (isFull())
		throw"stack is full";
	Top++;
	Mem[Top] = val;
}

template <class ValType>
bool Stack<ValType>::isFull()
{
	return(Top >= SizeMem);

}

template <class ValType>
ValType Stack<ValType>::Pop()
{
	if (isEmpty())
		throw"stack is empty";
	Top--;
	return Mem[Top + 1];
}

template <class ValType>
bool Stack<ValType>::isEmpty()
{
	return(Top < 0);
}

template <class ValType>
ValType Stack<ValType>::top()
{
	if (isEmpty())
		throw "error!!!!";
	return Mem[Top];
}

#endif
