/***********************************************
 * LinkedList.h
 *
 * List ADT implementation using a linked list.
 *
 * Authors: Juan O. Lopez & Joel M. Gonzalez
 **********************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListADT.h"

template <class Type>
struct nodeType
{
	Type data;
	nodeType *next;
};

template <class Type>
class LinkedList : public ListADT<Type> // public members of ListADT are also public here
{
public:
	LinkedList();
	~LinkedList();

	void add(const Type &);		   // append at the end
	void addAt(int, const Type &); // add at position
	bool remove(const Type &);	   // remove first copy of element
	bool removeAt(int);			   // remove at position
	int removeAll(const Type &);   // remove all copies of element
	Type getAt(int) const;		   // retrieve at position
	void setAt(int, const Type &); // set at position
	Type getFirst() const;		   // retrieve first element
	Type getLast() const;		   // retrieve last element
	int firstIndex(const Type &) const;
	int lastIndex(const Type &) const;
	int count(const Type &) const; // # of times element appears in list
	void clear();				   // empty the list
	/* These methods are inherited from ListADT:
	int size() const;
	bool isEmpty() const;
	bool contains(const Type&) const; */
	void print() const; // For testing
private:
	nodeType<Type> *head, *tail;
};

/* Constructor */
template <class Type>
LinkedList<Type>::LinkedList()
{
	head = tail = nullptr;
	/* Since currentSize was declared in ListADT, need to use "this->"
	 * to avoid error: 'currentSize' was not declared in this scope.
	 * Same thing for size() and isEmpty(). */
	this->currentSize = 0;
}

/* Destructor */
template <class Type>
LinkedList<Type>::~LinkedList()
{
	clear(); // removes nodes and sets head & tail
}

/*
 * add
 *
 * Add an element at the end of the list
 *
 * Parameters: e - Element to be inserted to the list
 */
template <class Type>
void LinkedList<Type>::add(const Type &e)
{
	nodeType<Type> *newNode = new nodeType<Type>;
	newNode->data = e;
	newNode->next = nullptr;

	/* TODO: Handle case when the list is empty!!!
			 Note that in this case, head & tail point to null. */
	if (head == nullptr && tail == nullptr)
	{
		head = newNode;
		tail = newNode;
		this->curren	
	}

	else
	{
		/* Make last node point to new node (when list isn't empty) */
		tail->next = newNode;

		/* New node becomes the tail */
		tail = newNode;
	}
	this->currentSize++;
}	

/*
 * addAt
 *
 * Add an element to the list at a particular position
 *
 * Parameters: pos - Position at which the element is to be inserted
 *             e   - Element to be inserted to the list
 */
template <class Type>
void LinkedList<Type>::addAt(int pos, const Type &e)
{
	if (pos > this->currentSize || pos < 0)
	{
		std::cout<<"ERROR POSITION OUT OF BOUNDS"<<std::endl;
		return;		
	}

	if (pos == this->currentSize)
	{
		add(e);
		return;		
	}

	nodeType<Type> *current;
	current = head;

	nodeType<Type> *newNode = new nodeType<Type>;
	newNode->data = e;
	newNode->next = nullptr;

	if (pos == 0)
	{
		newNode->next = head;
		head = newNode;

		this->currentSize++;
	}

	else
	{
		for (int i = 0; i < pos - 1; i++)
			current = current->next;

		newNode->next = current->next;
		current->next = newNode;
		this->currentSize++;
	}
}

/*
 * remove
 *
 * Remove from the list one copy of an element if it's there.
 *
 * Parameters: e - Element to be removed
 * Returns: true if the element was removed, false otherwise
 */
template <class Type>
bool LinkedList<Type>::remove(const Type &e)
{
	nodeType<Type> *current, *prev;
	current = head;
	prev = head;

	if (head == nullptr)
	{
		std::cout << "ERROR EMPTY LIST" << std::endl;
		return false;
	}

	else if (current->data == e)
	{
		head = head->next;
		this->currentSize--;
		delete current;

		return true;
	}

	else
	{
		current = head->next;

		while (current != nullptr)
		{
			if (current->data == e)
			{
				prev->next = current->next;
				this->currentSize--;
				delete current;

				if (tail == current)
					tail = prev;

				return true;
			}

			else
			{
				prev = current;
				current = current->next;
			}
		}
	}
	return false;
}

/*
 * removeAt
 *
 * Remove from the list the element at the specified position
 *
 * Parameters: pos - Position from which to remove the element
 * Returns: true if the element was removed, false otherwise
 */
template <class Type>
bool LinkedList<Type>::removeAt(int pos)
{
	nodeType<Type> *current, *prev;
	current = head;
	prev = head;

	if (pos > this->currentSize - 1)
		std::cout << "ERROR POSITION OUT OF BOUNDS" << std::endl;

	else if (pos == 0)
	{
		head = head->next;

		this->currentSize--;
		delete current;
		return true;
	}

	else
	{
		int i = 0;
		while (i < pos - 1)
		{
			current = current->next;
			i++;
		}

		prev = current;
		current = current->next;

		if (i == this->currentSize - 2)
		{
			prev->next = nullptr;
			tail = prev;

			this->currentSize--;
			delete current;
			return true;
		}

		else
		{
			prev->next = prev->next->next;

			this->currentSize--;
			delete current;
			return true;
		}
	}

	return false;
}

/*
 * removeAll
 *
 * Remove from the list all copies of an element.
 *
 * Parameters: e - Element to be removed
 * Returns: Amount of copies of the element that were removed.
 */
template <class Type>
int LinkedList<Type>::removeAll(const Type &e)
{
	int c;
	c = 0;

	while (remove(e))
		c++;

	return c;
}

template <class Type>
Type LinkedList<Type>::getAt(int pos) const
{
	nodeType<Type> *current = head;
	int i = 0;

	if (pos < 0 || pos > this->currentSize - 1)
	{
		std::cout << "ERROR POSITION OUT OF BOUNDS, ENTER A VALID POSITION" << std::endl;
		return (Type)NULL;
	}

	while (i < pos)
	{
		current = current->next;
		i++;
	}

	return (Type)current->data;
}

/*
 * setAt
 *
 * Sets the element at the specified position
 *
 * Parameters: pos - Position at which the element should be stored
 *             e   - Element to store
 */
template <class Type>
void LinkedList<Type>::setAt(int pos, const Type &e)
{
	nodeType<Type> *current = head;
	int i = 0;

	if (pos < 0 || pos > this->currentSize - 1)
		std::cout << "ERROR POSITION OUT OF BOUNDS, ENTER A VALID POSITION" << std::endl;

	else
	{
		while (i < pos)
		{
			current = current->next;
			i++;
		}

		current->data = e;
	}
}

/*
 * getFirst
 *
 * Retrieves the first element of the list.
 *
 * Returns: The first element of the list.
 */
template <class Type>
Type LinkedList<Type>::getFirst() const
{
	if(this->currentSize > 0)
		return (Type) head->data;

	std::cout<<"ERROR THE LIST IS EMPTY"<<std::endl;
	return (Type) NULL;
}

/*
 * getLast
 *
 * Retrieves the last element of the list.
 *
 * Returns: The last element of the list.
 */
template <class Type>
Type LinkedList<Type>::getLast() const
{
	if(this->currentSize > 0)
		return (Type) tail->data;

	std::cout<<"ERROR THE LIST IS EMPTY"<<std::endl;
	return (Type) NULL;
}

/*
 * firstIndex
 *
 * Determines the first position in which a specific element may be found.
 *
 * Parameters: e - Element to search for
 * Returns: The first position of the specified element, or -1 if not found
 */
template <class Type>
int LinkedList<Type>::firstIndex(const Type &e) const
{
	nodeType <Type> *current = head;
	int i = 0;

	while(current != nullptr)
	{
		if(current->data == e)
			return i;

		else
        {
			i++;
            current = current->next;
        }
	}

	return -1;
}

/*
 * lastIndex
 *
 * Determines the last position in which a specific element may be found.
 *
 * Parameters: e - Element to search for
 * Returns: The last position of the specified element, or -1 if not found
 */
template <class Type>
int LinkedList<Type>::lastIndex(const Type &e) const
{
    nodeType<Type> *current = head;
	int i, c;
	i=c=0;

	while(current != nullptr)
	{
		if(current->data == e)
            c = i;

        i++;
        current = current->next;
	}

    if(c)
        return c;

    else
        return -1;
}

/*
 * count
 *
 * The amount of occurrences of a particular element.
 *
 * Parameters: e - Element to look for
 * Returns: Amount of times the element appears in the list
 */
template <class Type>
int LinkedList<Type>::count(const Type &e) const
{
    nodeType<Type> *current = head;
    int c=0;

    while(current != nullptr)
    {
        if(current->data == e)
            c++;

        current = current->next;
    }

	if(c)
        return c;

    else
        return -1;
}

/*
 * clear
 *
 * Remove all elements from the list
 */
template <class Type>
void LinkedList<Type>::clear()
{
	while (!this->isEmpty())
		removeAt(0);
	/* It's important for removeAt to correctly handle the
	   removal of the first node and also when there's only 1 node. */
}

/*
 * print
 *
 * Prints all of the elements in the list (for testing purposes).
 */
template <class Type>
void LinkedList<Type>::print() const
{
	nodeType<Type> *current = head;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}

	std::cout << std::endl;

	/* THIS IS FOR TESTING PURPOSES! MUST BE REMOVED LATER! */
	if (!this->isEmpty())
	{
		/* Test to confirm that head & tail were set correctly. */
		std::cout << "Head node contains: " << head->data << std::endl;
		std::cout << "Tail node contains: " << tail->data << std::endl;
	}

	/* CHANGE THE TESTER TO CALL PRINT WHEN YOU ARE TESTING THE
	   SPECIAL CASES TO ENSURE HEAD & TAIL ARE CORRECT! */
}

#endif
