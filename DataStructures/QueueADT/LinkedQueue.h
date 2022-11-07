/********************************************************
 * LinkedQueueADT.h
 *
 * QueueADT implementation using a linked structure.
 *
 * Author: Joel M. Gonzalez
 *******************************************************/

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "QueueADT.h"

template<class Type>
struct nodeType
{
    Type data;
    nodeType *next;
};

template<class Type>
class LinkedQueue : public QueueADT<Type>
{
    public:
        LinkedQueue(); // constructor
        ~LinkedQueue(); // destructor

        Type front() const; // returns the element at the front of the queue
        void enqueue(const Type&); // adds an element to the front of the queue
        Type dequeue(); // removes and return the element at the front of the queue

    private:
        nodeType<Type> *head, *tail;
};

template<class Type>
LinkedQueue<Type>::LinkedQueue()
{
    head = nullptr;
    tail = nullptr;
    this->currentSize = 0;
}

template<class Type>
LinkedQueue<Type>::~LinkedQueue()
{
    this->clear();
}

template<class Type>
Type LinkedQueue<Type>::front() const // returns the element at the front of the queue
{
    if(head == nullptr)
    {
        std::cout<<"ERROR: The list is empty"<<std::endl;
        return (Type) NULL;        
    }

    return head->data;
}

template<class Type>
void LinkedQueue<Type>::enqueue(const Type& e) // adds an element to the front of the queue
{
    nodeType<Type> *temp = new nodeType<Type>;
    temp->data = e;
    temp->next = nullptr;

    if(head == nullptr)
    {
        head = temp;
        tail = temp;
    }

    else
    {
        tail->next = temp;
        tail = temp;
    }

    this->currentSize++;
}

template<class Type>
Type LinkedQueue<Type>::dequeue() // removes and return the element at the front of the queue
{
    Type val = head->data;

    if(head == nullptr)
    {
        std::cout<<"ERROR: The list is empty"<<std::endl;
        return (Type) NULL;        
    }

    else
    {
        nodeType<Type> *temp = head;

        head = head->next;
        delete temp;
        this->currentSize--;
        
        if(head == nullptr)
            tail = nullptr;
    }

    return val;
}

#endif
