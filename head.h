#ifdef HEAD_H
#define HEAD_H
#endif // HEAD_H


#include <stdio.h>
#include<iostream>
#include<exception>
#include<string>
using namespace std;

class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "please write again";
	}
}myex;

void Assert(bool val, string s) {
	if (!val) {
		cout << s << endl;
		throw myex;
	}
}

template<typename E>class Stack {
private:
	void operator = (const Stack&) {}
	Stack(const Stack&) {}
public:
	Stack() {}
	virtual ~Stack() {}

	virtual void clear() = 0;

	virtual void push(const E& it) = 0;

	virtual E pop() = 0;

	virtual const E& topValue() const = 0;

	virtual int length() const = 0;
};

template<typename E>class Link {
private:
	static Link<E>* freelist;
public:
	E element;
	Link* next;

	Link(const E& elemval, Link* nextval = NULL) {
		element = elemval; next = nextval;
	}

	Link(Link* nextval = NULL) {
		next = nextval;
	}

	void* operator new(size_t) {
		if (freelist == NULL) return ::new Link;
		Link<E>* temp = freelist;
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr) {
		((Link<E>*)ptr)->next = freelist;
		freelist = (Link<E>*)ptr;
	}
};

template<typename E>
Link<E>* Link<E>::freelist = NULL;

template<typename E>class LStack : public Stack<E> {
private:
	Link<E>* top;
	int size;
public:
	LStack(int sz = 50) {
		top = NULL;
		size = 0;
	}

	~LStack() { clear(); }

	void clear() {
		while (top != NULL) {
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E&it) {
		top = new Link<E>(it, top);
		size++;
	}

	E pop() {
		Assert(top != NULL, "wrong format in expression");
		E it = top->element;
		Link<E>* ltemp = top->next;
		delete top;
		top = ltemp;
		size--;
		return it;
	}

	const E& topValue() const {
		Assert(top != NULL, "wrong format in expression");
		 return top->element;
	}

	int length() const { return size; }
};
#pragma once
