#ifndef LINKEDLIST_INCLUDED
#define LINKEDLIST_INCLUDED

#include "Node.h"

template<class T>
class LinkedList
{
public:
	//CONSTRUCTORS AND DESTRUCTORS
	LinkedList();
	LinkedList(Node<T> * head_);
	~LinkedList();

	//SETTERS
	void setHead(Node<T> * n);
	void setTail(Node<T> * n);

	//GETTERS
	Node<T> * getHead();
	Node<T> * getTail();

	//OTHERS
	void addAfterTail(Node<T> * n);
	void addBeforeHead(Node<T> * n);
	Node<T> * deleteHead();

private:
	Node<T> * head;
	Node<T> * tail;
};

#endif