#ifdef __APPLE__
#include "include/Node.h"
#else
#include "Node.h"
#endif

#include <iostream>

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
template<class T>
Node<T>::Node()
{
	data = NULL;
	next = NULL;
}

template<class T>
Node<T>::Node(T data_, Node<T> * next_)
{
	data = data_;
	next = next_;
}

template<class T>
Node<T>::~Node()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
template<class T>
void Node<T>::setData(T data_)
{
	data = data_;
}

template<class T>
void Node<T>::setNext(Node<T> * next_)
{
	next = next_;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
template<class T>
T Node<T>::getData()
{
	return data;
}

template<class T>
Node<T> * Node<T>::getNext()
{
	return next;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
template<class T>
void Node<T>::insertAfter(Node<T> * n)
{
	//insert a node n just after the node that the method belongs to
	n->setNext(next);
	next = n;
}

template<class T>
Node<T> * Node<T>::deleteAfter()
{
	//if there is a node after the node the method belongs to, delete it
	//returns the node being deleted (or null)
	Node<T> * temp = next;
	if (next != NULL) next = next->getNext();
	return temp;
}
