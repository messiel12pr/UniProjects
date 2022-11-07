/***********************************************
 * QueueADT.h
 *
 * Queue ADT defined as an abstract base class.
 *
 * Author: Joel M. Gonzalez
 **********************************************/

#ifndef QUEUEADT_H
#define QUEUEADT_H

template<class Type>
class QueueADT
{
    public:
        virtual Type front() const = 0; // returns the element at the front of the queue
        virtual void enqueue(const Type&) = 0; // adds an element to the front of the queue
        virtual Type dequeue() = 0; // removes and return the element at the front of the queue

        int size() const; // returns the size of the queue
        bool isEmpty() const; // returns true if the queue is empty
        void clear(); // deletes all the elements in the queue

    protected:
        int currentSize;
};

template<class Type>
int QueueADT<Type>::size() const
{
    return currentSize;
}

template<class Type>
bool QueueADT<Type>::isEmpty() const
{
    return currentSize == 0;
}

template<class Type>
void QueueADT<Type>::clear()
{
    while(!isEmpty())
        dequeue();
    std::cout<<"The queue was successfully cleared"<<std::endl;
}

#endif
