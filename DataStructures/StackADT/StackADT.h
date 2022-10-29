/***********************************************
 * StackADT.h
 *
 * Stack ADT defined as an abstract base class.
 *
 * Author: Joel M. Gonzalez
 **********************************************/

#ifndef STACKADT_H
#define STACKADT_H

template<class Type>
class StackADT
{
    public:
        virtual void push(const Type&) = 0; // adds an element to top of the stack
        virtual Type top() const = 0; // returns the element at the top of the stack
        virtual Type pop() = 0; // removes and returns the element at the top of the stack
        virtual void clear() = 0; // clears the stack

        int size() const; // returns the size of the stack
        bool isEmpty() const; // checks if the list is empty

    protected:
        int currentSize;
};

template<class Type>
int StackADT<Type>::size() const
{
    return currentSize;
}

template<class Type>
bool StackADT<Type>::isEmpty() const
{
    return size() == 0;
}

#endif
