/*****************************************************
 *
 *  ArrayList.h
 *  
 *  Using Inheritance (ListAdt.h)
 *
 *  Joel M. Gonzalez Rodriguez
 *
*/****************************************************

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "listAdt.h"

template <class Type>
class ArrayList : public ListADT<Type> // public members of ListADT are also public here
{
	public:
        template <class T>
        friend std::ostream& operator<<(std::ostream&, const ArrayList<T>&);

		ArrayList(int = DEFAULTSIZE); // constructor with default parameter
		~ArrayList();

		void add(const Type&); // append at the end
		void addAt(int, const Type&); // add at position
		bool remove(const Type&); // remove first copy of element
		bool removeAt(int); // remove at position
		int removeAll(const Type&); // remove all copies of element
		Type getAt(int) const; // retrieve at position
		void setAt(int, const Type&); // set at position
		Type getFirst() const; // retrieve first element
		Type getLast() const; // retrieve last element
		int firstIndex(const Type&) const;
		int lastIndex(const Type&) const;
		int count(const Type&) const; // # of times element appears in list
		void clear(); // empty the list
		/* These methods are inherited from ListADT:
		int size() const;
		bool isEmpty() const;
		bool contains(const Type&) const; */
		void print() const; // For testing
	private:
		Type* elements; // dynamic array
		int capacity; // size of array
		static const int DEFAULTSIZE = 10;
};

/* Constructor */
template <class Type>
ArrayList<Type>::ArrayList(int initialCapacity)
{
	if (initialCapacity < 1)
		initialCapacity = DEFAULTSIZE;
	capacity = initialCapacity;
	elements = new Type[capacity];
	/* Since currentSize was declared in ListADT, need to use "this->"
	 * to avoid error: 'currentSize' was not declared in this scope.
	 * Same thing for size() and isEmpty(). */
	this->currentSize = 0;
}

/* Destructor */
template <class Type>
ArrayList<Type>::~ArrayList()
{
	delete [] elements;
}

/*
 * add
 *
 * Add an element at the end of the list
 *
 * Parameters: e - Element to be inserted to the list
 */
template <class Type>
void ArrayList<Type>::add(const Type& e)
{
	if (this->size() == capacity) // Array is full, need a bigger one
	{
		/* NOTE: Something similar needs to be done in addAt if the array is full.
		 *       Should we duplicate the code? */
		capacity *= 2;
		Type* biggerArray = new Type[capacity]; // using bigger capacity
		/* Copy elements to the new bigger array */
		for (int i = 0; i < this->currentSize; i++)
			biggerArray[i] = elements[i];
		/* Now we discard the old array and use the new one */
		delete [] elements;
		elements = biggerArray; // Copying pointers; not duplicating arrays
	}
	elements[this->currentSize] = e;
	this->currentSize++; // Note that -> has higher precedence than ++
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
void ArrayList<Type>::addAt(int pos, const Type& e)
{
    if (this->size() == capacity) // Array is full, need a bigger one
	{
		/* NOTE: Something similar needs to be done in addAt if the array is full.
		 *       Should we duplicate the code? */
		capacity *= 2;
		Type* biggerArray = new Type[capacity]; // using bigger capacity
		/* Copy elements to the new bigger array */
		for (int i = 0; i < this->currentSize; i++)
			biggerArray[i] = elements[i];
		/* Now we discard the old array and use the new one */
		delete [] elements;
		elements = biggerArray; // Copying pointers; not duplicating arrays
	}


	if(pos == this->currentSize)
    {
        elements[this->currentSize] = e;
        this->currentSize++;
    }

    else if(!(pos > this->currentSize))
    {
        for(int i=0; i<this->currentSize-pos; i++)
            elements[this->currentSize-i] = elements[(this->currentSize-1)-i];

        elements[pos] = e;
        this->currentSize++;
    }

    else
        std::cout<<"Error, the position "<<pos<<" is not available to add an element \n";
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
bool ArrayList<Type>::remove(const Type& e)
{
    for(int i=0; i<this->currentSize; i++)
    {
        if(elements[i] == e && i == this->currentSize)
        {
            elements[i] = 0;
            this->currentSize--;
            return true;
        }

        else if(elements[i] == e && i != this->currentSize)
        {
            for(int j=0; j<this->currentSize-i; j++)
                elements[i+j] = elements[(i+1)+j];

            this->currentSize--;
            return true;
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
bool ArrayList<Type>::removeAt(int pos)
{
    if(pos == this->currentSize-1)
    {
        elements[pos] = 0;
        this->currentSize--;
        return true;
    }

    else if(!(pos > this->currentSize-1))
    {
        for(int i=pos; i<this->currentSize-pos; i++)
            elements[i] = elements[i+1];
        this->currentSize--;
        return true;
    }

    else
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
int ArrayList<Type>::removeAll(const Type& e)
{
    int c = 0;
    bool r = true;

    while(r)
    {
        if(remove(e))
            c++;
        else
            r = false;
    }
    return c;
}

/*
 *  getAt
 *
 *  Retrieves element at position
 *
 *  Parameters: pos - Index to retrieve element from
 *  Returns: If the index is valid it returns the item at the index
 *           else it returns null
*/
template <class Type>
Type ArrayList<Type>::getAt(int pos) const
{
    if(!(pos>this->currentSize-1))
        return elements[pos];

    else
        return (Type)NULL;
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
void ArrayList<Type>::setAt(int pos, const Type& e)
{
    if(!(pos>this->currentSize-1))
    {
        elements[pos] = e;
        std::cout<<e<<" was added to the index "<<pos<<" in the list \n";
    }

    else
        std::cout<<"The index entered is out of bounds \n";
}

/*
 * getFirst
 *
 * Retrieves the first element of the list.
 *
 * Returns: The first element of the list.
 */
template <class Type>
Type ArrayList<Type>::getFirst() const
{
	if(!this->isEmpty())
        return elements[0];
    else
        return (Type)NULL;
}

/*
 * getLast
 *
 * Retrieves the last element of the list.
 *
 * Returns: The last element of the list.
 */
template <class Type>
Type ArrayList<Type>::getLast() const
{
    if(!this->isEmpty())
        return elements[this->currentSize-1];
    else
        return (Type)NULL;
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
int ArrayList<Type>::firstIndex(const Type& e) const
{
    for(int i=0; i<this->currentSize; i++)
        if(elements[i] == e)
            return i;
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
int ArrayList<Type>::lastIndex(const Type& e) const
{
    for(int i=this->currentSize-1; i>=0; i--)
        if(elements[i] == e)
            return i;
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
int ArrayList<Type>::count(const Type& e) const
{
    int c = 0;

    for(int i=0; i<this->currentSize; i++)
        if(elements[i] == e)
            c++;

	return c;
}

/*
 * clear
 *
 * Remove all elements from the list
 */
template <class Type>
void ArrayList<Type>::clear()
{
    for(int i=0; i<this->currentSize; i++)
        elements[i] = 0;
    this->currentSize = 0;
}

/*
 * print
 *
 * Prints all of the elements in the list (for testing purposes).
 */
template <class Type>
void ArrayList<Type>::print() const
{
	for (int i = 0; i < this->size(); i++)
		std::cout << elements[i] << " ";
	std::cout << std::endl;
}

/*
 * operator<<
 *
 * Overload the << operator to output the bag using an output stream.
 *
 * Parameters: os  - Output stream to use
 *             bag - Bag to output
 * Returns: Output stream that was used
 */
template <class Type>
std::ostream& operator<<(std::ostream& os, const ArrayList<Type>& arrList)
{
	for (int i = 0; i < arrList.currentSize; i++)
		os << arrList.elements[i] << " ";
	os << "\n";

	return os;
}

#endif
