/***********************************************
 * LinkedStackADT.h
 *
 * Stack implementation using a linked structure.
 *
 * Author: Joel M. Gonzalez
 **********************************************/

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "StackADT.h"

template<class Type>
struct nodeType
{
    Type data;
    nodeType *next;
};

template<class Type>
class LinkedStack : public StackADT<Type>
{
    public:
        LinkedStack(); // constructor
        ~LinkedStack(); // destructor
        void push(const Type&); // adds an element to top of the stack
        Type top() const; // returns the element at the top of the stack
        Type pop(); // removes and returns the element at the top of the stack
        void clear(); // clears the stack

    private:
        nodeType<Type> *head;
};

template<class Type>
LinkedStack<Type>::LinkedStack() // constructor
{
    head = nullptr;
    this->currentSize = 0;
}

template<class Type>
LinkedStack<Type>::~LinkedStack() // destructor
{
    delete head;
}

template<class Type>
void LinkedStack<Type>::push(const Type& e) // adds an element to top of the stack
{
    nodeType<Type> *node = new nodeType<Type>;
    node->data = e;
    
    if(this->isEmpty())
    {
        head = node;
        node->next = nullptr;
    }

    else
    {
        node->next = head;
        head = node;
    }

    this->currentSize++;
}

template<class Type>
Type LinkedStack<Type>::top() const // returns the element at the top of the stack
{
    if(!this->isEmpty())
        return head->data;

    else
    {
        std::cout<<"ERROR: The stack is empty"<<std::endl;
        return (Type)NULL;
    }
}

template<class Type>
Type LinkedStack<Type>::pop() // removes and returns the element at the top of the stack
{
    if(!this->isEmpty())
    {
        int temp = head->data;
        head = head->next;
        this->currentSize--;
        return temp;
    }

    else
    {
        std::cout<<"ERROR: The stack is empty"<<std::endl;
        return (Type)NULL;        
    }
}

template<class Type>
void LinkedStack<Type>::clear() // clears the stack
{
    if(!this->isEmpty())
    {
        while(head != nullptr)
        {
            nodeType<Type> *temp = head;
            head = head->next;
            delete temp;
            this->currentSize--;
        }

        std::cout<<"The stack was successfully cleared!"<<std::endl;
    }

    else
    {
        std::cout<<"ERROR: The stack is empty"<<std::endl;
        return;        
    }    
}

#endif
