/*****************************************************
 *
 *  StaticSetADT
 *  
 *  Using Object Composition (StaticBag<Type>)
 *
 *  Joel M. Gonzalez Rodriguez
 *
*/****************************************************

#ifndef STATICSET_H
#define STATICSET_H

#pragma once

template <class Type>
class StaticSet
{
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const StaticSet<T>&);

	public:
		StaticSet(int = 10); // constructor with default parameter
		StaticSet(const StaticSet<Type>&); // copy constructor
		const StaticSet<Type>& operator=(const StaticSet<Type>&); // Overload =
		//~StaticSet();  Destructor of Static Bag will be automatically invoked

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
		int capacity;
		/* Instead of directly manipulating an elements array,
		 * we use a StaticBag object to handle everything for us
		 * (except the add method in case the bag is full). */
		//Type *elements;
		StaticBag<Type> theBag; // object composition
};

#endif

#include <iostream>
#include "StaticBag.h"



/* Implementation included in the same file due to the use of templates. */

/* Constructor */
template <class Type>
StaticSet<Type>::StaticSet(int initialCapacity)
{
	if (initialCapacity < 1) // Make sure we get a valid number
		initialCapacity = 10; // Same as default parameter
	capacity = initialCapacity;
	theBag = StaticBag<Type>(initialCapacity); // Uses operator=
}

/* Copy constructor */
template <class Type>
StaticSet<Type>::StaticSet(const StaticSet<Type>& otherBag)
{
	capacity = otherBag.capacity;
	theBag = otherBag.theBag; // Use Static Bag's overloaded =
}

/* Overloading assignment operator (=) */
template <class Type>
const StaticSet<Type>& StaticSet<Type>::operator=(const StaticSet<Type>& otherBag)
{
	if (this != &otherBag) // Avoid self-assignment
	{
		capacity = otherBag.capacity;
		theBag = otherBag.bag; // Use Static Bag's overloaded =
	}

	return *this;
}

/*
 * add
 *
 * Add an element to the bag if there's room left.
 * 
 * Parameters: e - Element to be added to the bag
 */
template <class Type>
void StaticSet<Type>::add(const Type& e)
{
	/* First, check if there's room */
	if (theBag.size() == capacity)
	{
		/* Bag is full, need to "grow"
		 * New bag should hold twice as many elements */
		Type *bagAsArray = theBag.asArray();
		theBag = StaticBag<Type>(2*capacity); // uses StaticBag's overloaded =
		for (int i = 0; i < capacity; i++)
			theBag.add(bagAsArray[i]);
		capacity *= 2;
	}
	theBag.add(e);
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
bool StaticSet<Type>::remove(const Type& e)
{
	return theBag.remove(e);
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
int StaticSet<Type>::removeAll(const Type& e)
{
	return theBag.removeAll(e);
}

/*
 * clear
 *
 * Remove all elements from the bag
 */
template <class Type>
void StaticSet<Type>::clear()
{
	theBag.clear();
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
int StaticSet<Type>::count(const Type& e) const
{
	return theBag.count(e);
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
bool StaticSet<Type>::isElement(const Type& e) const
{
	return theBag.isElement(e);
}

/*
 * size
 *
 * Determines the amount of elements in the bag.
 *
 * Returns: Amount of elements in the bag
 */
template <class Type>
int StaticSet<Type>::size() const
{
	return theBag.size();
}

/*
 * isEmpty
 *
 * Determines whether the bag is empty.
 *
 * Returns: True if the bag is empty, false otherwise
 */
template <class Type>
bool StaticSet<Type>::isEmpty() const
{
	return theBag.isEmpty();
}

/*
 * asArray
 *
 * Returns: Contents of the bag as an array.
 * (Useful due to the lack of an iterator).
 */
template <class Type>
Type* StaticSet<Type>::asArray() const
{
	return theBag.asArray();
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
std::ostream& operator<<(std::ostream& os, const StaticSet<Type>& bag)
{
	return (os << bag.theBag); // this invokes operator<< for Static Bag
}
