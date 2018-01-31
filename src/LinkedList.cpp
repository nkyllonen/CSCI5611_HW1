#ifdef __APPLE__
#include "include/LinkedList.h"
#else
#include "LinkedList.h"
#endif

#include <iostream>

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
template<class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template<class T>
LinkedList<T>::LinkedList(Node<T> * head_)
{
	head = head_;
	tail = head_;
}

template<class T>
LinkedList<T>::~LinkedList()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
template<class T>
void LinkedList<T>::setHead(Node<T> * n)
{
	head = n;
}

template<class T>
void LinkedList<T>::setTail(Node<T> * n)
{
	tail = n;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
template<class T>
Node<T> * LinkedList<T>::getHead()
{
	return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail()
{
	return tail;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
template<class T>
void LinkedList<T>::addAfterTail(Node<T> * n)
{
	tail->setNext(n);
	tail = n;
}

template<class T>
void LinkedList<T>::addBeforeHead(Node<T> * n)
{
	Node<T> * temp = head;
	head = n;
	head->setNext(temp);
}

template<class T>
Node<T> * LinkedList<T>::deleteHead()
{
	//sets head as second node in linked list and deletes original head
	Node<T> * temp = head;
	head = head->getNext();
	return temp;
}





