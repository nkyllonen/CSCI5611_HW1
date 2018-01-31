#ifndef NODE_INCLUDED
#define NODE_INCLUDED

template<class T>
class Node
{
public:
	//CONSTRUCTORS AND DESTRUCTORS
	Node();
	Node(T data, Node<T> * next);
	~Node();

	//SETTERS
	void setData(T data);
	void setNext(Node<T> * next);

	//GETTERS
	T getData();
	Node<T> * getNext();

	//OTHERS
	void insertAfter(Node<T> * node);
	Node<T> * deleteAfter();

private:
	T data;
	Node<T> * next;
};

#endif