/******************************************
* StaticBag.h
*
* Static Bag class (using template).
*
* Author: Juan O. Lopez
******************************************/

//!CLASS PROVIDED BY PROFESSOR TO BUILD SET ADT USING OBJECT COMPOSITION!

#include <iostream>

template <class Type>
class StaticBag
{
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const StaticBag<T>&);

	public:
		StaticBag(int = 10); // constructor with default parameter
		StaticBag(const StaticBag<Type> &); // Copy constructor
		const StaticBag<Type>& operator=(const StaticBag<Type> &); // Overload =
		~StaticBag(); // destructor
		
		void add(const Type &);
		bool remove(const Type &); // remove a single copy
		int removeAll(const Type &); // remove ALL copies
		void clear();
		int count(const Type &) const;
		bool isElement(const Type &) const;
		int size() const; // amount of elements
		bool isEmpty() const;
		Type* asArray() const;
	private:
		int currentSize, capacity;
		Type *elements;
};

/* Implementation included in the same file due to the use of templates. */

/* Constructor */
template <class Type>
StaticBag<Type>::StaticBag(int initialCapacity)
{
	if (initialCapacity < 1) // Make sure we get a valid number
		initialCapacity = 10; // Same as default parameter
	capacity = initialCapacity;
	elements = new Type[initialCapacity];
	currentSize = 0; // Bag is initially empty
}

/* Copy constructor */
template <class Type>
StaticBag<Type>::StaticBag(const StaticBag<Type>& otherBag)
{
	/* No need to clear out elements, because when a copy
	 * constructor is invoked, the object is empty. */
	currentSize = otherBag.currentSize;
	capacity = otherBag.capacity;
	elements = new Type[otherBag.capacity];
	for (int i = 0; i < currentSize; i++)
		elements[i] = otherBag.elements[i];
}

/* Overloading assignment operator (=) */
template <class Type>
const StaticBag<Type>& StaticBag<Type>::operator=(const StaticBag<Type>& otherBag)
{
	if (this != &otherBag) // Avoid self-assignment (e.g. bag1 = bag1;)
	{
		/* Unlike the copy constructor, we are going to copy to an existing bag which
		may have elements, so we first delete the existing elements. */
		delete [] elements;
		/* Note that the following code is identical to the copy constructor.
		   In future classes, we will avoid duplicating similar code. */
		currentSize = otherBag.currentSize;
		capacity = otherBag.capacity;
		elements = new Type[otherBag.capacity];
		for (int i = 0; i < currentSize; i++)
			elements[i] = otherBag.elements[i];
	}

	return *this;
}

/* Destructor */
template <class Type>
StaticBag<Type>::~StaticBag()
{
	delete [] elements; // Avoid memory leak
}

/*
 * add
 *
 * Add an element to the bag if there's room left.
 * 
 * Parameters: e - Element to be added to the bag
 */
template <class Type>
void StaticBag<Type>::add(const Type& e)
{
	/* First, check if there's room */
	if (currentSize < capacity)
		elements[currentSize++] = e; // currentSize incremented
}

/*
 * remove
 *
 * Remove from the bag one copy of an element if it's there.
 *
 * Parameters: e - Element to be removed
 * Returns: true if element was removed, false otherwise
 */
template <class Type>
bool StaticBag<Type>::remove(const Type& e)
{
	/* First, need to find the element */
	for (int i = 0; i < currentSize; i++)
		if (elements[i] == e) // Found it!
		{
			/* Move last element to position i to avoid gaps */
			elements[i] = elements[currentSize - 1];
			elements[currentSize - 1] = 0; // "delete" duplicate
			currentSize--;
			return true;
		}
	/* If we make it here, the element wasn't found */
	return false;
}

/*
 * removeAll
 *
 * Remove from the bag all copies of an element.
 *
 * Parameters: e - Element to be removed
 * Returns: Amount of copies removed (could be 0)
 */
template <class Type>
int StaticBag<Type>::removeAll(const Type& e)
{
	int counter = 0;
	while (remove(e))
		counter++;
	return counter;
}

/*
 * clear
 *
 * Remove all elements from the bag
 */
template <class Type>
void StaticBag<Type>::clear()
{
	/* First clear out the data */
	for (int i = 0; i < currentSize; i++)
		elements[i] = 0;
	/* Now reset currentSize */
	currentSize = 0;
}

/*
 * count
 *
 * The amount of occurrences of a particular element.
 *
 * Parameters: e - Element to look for
 * Returns: Amount of times the element appears in the bag
 */
template <class Type>
int StaticBag<Type>::count(const Type& e) const
{
	int counter = 0;
	for (int i = 0; i < currentSize; i++)
		if (elements[i] == e)
			counter++;
	return counter;
}

/*
 * isElement
 *
 * Determines if an element is present in the bag.
 *
 * Parameters: e - Element to look for
 * Returns: True if the element is in the bag, false otherwise
 */
template <class Type>
bool StaticBag<Type>::isElement(const Type& e) const
{
	return (count(e) > 0);
}

/*
 * size
 *
 * Determines the amount of elements in the bag.
 *
 * Returns: Amount of elements in the bag
 */
template <class Type>
int StaticBag<Type>::size() const
{
	return currentSize;
}

/*
 * asArray
 *
 * Returns: Contents of the bag as an array.
 * (Useful due to the lack of an iterator).
 */
template <class Type>
Type* StaticBag<Type>::asArray() const
{
	Type *elementsCopy = new Type[currentSize];

	for (int i = 0; i < currentSize; i++)
		elementsCopy[i] = elements[i];
	return elementsCopy;
	/* THINK: Why can't we simply return the elements array? */
}

/*
 * isEmpty
 *
 * Determines whether the bag is empty.
 *
 * Returns: True if the bag is empty, false otherwise
 */
template <class Type>
bool StaticBag<Type>::isEmpty() const
{
	return (currentSize == 0);
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
std::ostream& operator<<(std::ostream& os, const StaticBag<Type>& bag)
{
	for (int i = 0; i < bag.currentSize; i++)
		os << bag.elements[i] << " ";
	os << "\n";

	return os;
}
