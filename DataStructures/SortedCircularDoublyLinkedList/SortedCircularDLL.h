/****************************************************
 * SortedCircularDLL.h
 *
 * Sorted Circular Doubly Linked List using ListADT
 *
 * Author: Joel M. Gonzalez
 ***************************************************/

#ifndef SORTEDCIRCULARDLL_H2
#define SORTEDCIRCULARDLL_H

#include "ListADT.h"

template <class Type>
struct nodeType
{
    Type data;
    nodeType<Type> *prev, *next;
};

template <class Type>
class SortedCircularDLL : public ListADT<Type>
{
    template <class T>
    friend std::ostream &operator<<(std::ostream &, const SortedCircularDLL<T> &); // operator overload << (for printing the lsit)

public:
    SortedCircularDLL();  // constructor
    ~SortedCircularDLL(); // destructor

    
    SortedCircularDLL(const SortedCircularDLL<Type> &); // Copy constructor
    const SortedCircularDLL<Type>& operator=(const SortedCircularDLL<Type> &); // operator overload =

    void add(const Type &);// append at correct position (maintain order)
    void addAt(int, const Type &);// invokes add method
    void setAt(int, const Type &);// set element at correct position
    
    bool remove(const Type &);// remove first copy of element
    bool removeAt(int);// remove at position
    int removeAll(const Type &);// remove all copies of element

    Type getAt(int) const;// retrieve at position
    Type getFirst() const;// retrieve first element of the list
    Type getLast() const;// retrieve last element of the list
    int firstIndex(const Type &) const;// retrieves the first index of an element
    int lastIndex(const Type &) const;// retrieves the last index of an element

    int count(const Type &) const;// # of times element appears in list

    void clear();// deletes all the nodes in the list

    void print() const;// prints the contents of the list
    void printReverse() const;// prints the contents of the list in reverse order

private:
    nodeType<Type> *dummyNode;
    void copyList(const SortedCircularDLL<Type>&); // copies the elements of a list into this list
};

/*
 *
 *  Constructor
 *  Initializes dummyNode and currentSize
 *
 */
template <class Type>
SortedCircularDLL<Type>::SortedCircularDLL()
{
    dummyNode = new nodeType<Type>;
    dummyNode->prev = dummyNode;
    dummyNode->next = dummyNode;
    dummyNode->data = (Type)NULL;
    this->currentSize = 0;
}

/*
 *
 *  Destroys the list
 *
 */
template <class Type>
SortedCircularDLL<Type>::~SortedCircularDLL()
{
    clear();
    delete dummyNode;
}

/*
 *  Add's an element to it's correct position
 *
 *  Parameter:  e - element to be inserted
 *
 */
template <class Type>
void SortedCircularDLL<Type>::add(const Type &e)
{
    // Creating a node and initializing it's pointers to null
    // Assigning the data field of this node to the element that we want to insert
    nodeType<Type> *temp = new nodeType<Type>;
    temp->data = e;
    temp->prev = nullptr;
    temp->next = nullptr;

    // Check If the list is empty
    if (dummyNode->next == dummyNode)
    {
        // If true the we add element to the list and update dummy pointers
        temp->prev = dummyNode;
        temp->next = dummyNode;
        dummyNode->next = temp;
        dummyNode->prev = temp;
    }

    // Check if the element we want to insert is to be inserted at the end
    // of the list
    else if (dummyNode->prev->data <= e)
    {
        // If true then we insert the new element at the end of the list
        temp->prev = dummyNode->prev;
        temp->next = dummyNode;
        dummyNode->prev->next = temp;
        dummyNode->prev = temp;
    }

    // If the list is not empty and the element is not to be inserted at the end we need to 
    // search for the correct position to insert the node at
    else
    {
        // Create pointer to traverse the list
        nodeType<Type> *current = dummyNode->next;

        while (current != dummyNode)
        {
            // If the current element is larger or equal than the one we have
            // we want to add our element before this node
            if (current->data >= e)
            {
                temp->prev = current->prev;
                temp->next = current;
                current->prev->next = temp;
                current->prev = temp;
                break;
            }

            // Continue traversing list
            current = current->next;
        }
    }
    this->currentSize++;
}

/*
 *  addAt
 *
 *  Invokes add method
 * 
 *  Parameters: pos - index of element to be set (we will not use this pos because
 *  we want to maintain order in the lis)
 *  Parameters: e - Element to be inserted
 *
 */
template <class Type>
void SortedCircularDLL<Type>::addAt(int pos, const Type &e)
{
    add(e);
}

/*
 *  setAt
 *
 *  Sets element at an correct position
 *
 *  Parameters: pos - index of element to be set (we will not use this pos because
 *  we want to maintain order in the lis)
 *  Parameters: e - element to be inserted
 *
 */
template <class Type>
void SortedCircularDLL<Type>::setAt(int pos, const Type &e)
{ 
    if(pos < 0 || pos > this->currentSize-1)
    {
        std::cout<<"ERROR: position out of bounds"<<std::endl;
        return;
    }
    
    removeAt(pos);
    add(e);
}

/*
 *  remove 
 * 
 *  Removes one copy of an element
 * 
 *  Parameter:  e - element to be removed 
 *  Returns:    true - if the element was found
 * 
 */
template<class Type>
bool SortedCircularDLL<Type>::remove(const Type &e)
{
    nodeType<Type> *current = dummyNode->next;

    // Make sure the list is not empty
    if(dummyNode->next == dummyNode)
    {
        std::cout<<"ERROR: The list is empty"<<std::endl;
        return false;
    }

    // Traverse the list 
    while(current != dummyNode)
    {
        if(current->data == e)
        {
            // Remove node from the list
            nodeType<Type> *temp = current;

            current->prev->next = current->next;
            current->next->prev = current->prev;

            delete temp;
            this->currentSize--;
            return true;
        }

        else
            current = current->next;
    }

    std::cout<<"The element "<<e<<" was not found in the list"<<std::endl;
    return false;
}

/*
 *  removeAt
 *
 *  Removes an element given it's index
 *
 *  Parameters: pos - index of element to be removed
 *  Returns:    True - if the element was removed
 *
 */
template <class Type>
bool SortedCircularDLL<Type>::removeAt(int pos)
{
    nodeType<Type> *current = dummyNode->next;

    // Handle the special cases
    if(dummyNode->next == dummyNode)
    {
        std::cout<<"ERROR: The list is empty"<<std::endl;
        return false;
    }

    if(pos > this->currentSize-1 || pos < 0)
    {
        std::cout<<"ERROR: Position out of bounds"<<std::endl;
        return false;
    }

    // Find the node that we want to remove
    // given it's position
    // If the pos is 0 it doesn't run because current
    // already points to the first node
    for(int i=0; i<pos; i++)
        current = current->next;

    // Delete the node
    current->prev->next = current->next;
    current->next->prev = current->prev;

    nodeType<Type> *temp = current;

    delete temp;
    this->currentSize--;
    return true;
}

/*
 *  removeAll
 *
 *  Removes all copies of an element
 *
 *  Parameters: e - element to be removed
 *  Returns:    number of copies that where removed
 *
 */
template <class Type>
int SortedCircularDLL<Type>::removeAll(const Type &e)
{
    if(dummyNode->next == dummyNode)
    {
        std::cout<<"ERROR: The list is empty"<<std::endl;
        return -1;      
    }

    // O(n) approach
    nodeType<Type> *current = dummyNode->next;
    int c = 0;

    while(current != dummyNode)
    {
        if(current->data == e)
        {
            Type element = current->data;
            while(element == e)
            {
                nodeType<Type> *temp = current;
                element = current->next->data; 

                current->prev->next = current->next;
                current->next->prev = current->prev;
                current = current->next;

                delete temp;
                c++;
                this->currentSize--;                
            }

            return c;
        }

        current = current->next;
    }

    return c;

    // O(n^2) approach
    /* 
    int c = 0;

    while(remove(e))
        c++;

    return c; 
    */
}

/*
 *  getAt
 *
 *  Retrieves element at an index
 *
 *  Parameters: pos - index of element to be retrieved
 *  Returns:    element found at position
 *
 */
template <class Type>
Type SortedCircularDLL<Type>::getAt(int pos) const
{
    // Check if the list is empty
    if(dummyNode->next == dummyNode)
    {
        std::cout<<"ERROR: The list is empty";
        return (Type)NULL;
    }

    // Validate position
    if(pos < 0 || pos > this->currentSize-1)
    {
        std::cout<<"ERROR: Position out of bounds";
        return (Type)NULL;
    }

    nodeType<Type> *current = dummyNode->next;

    // Search for the node at given index
    for(int i=0; i<pos; i++)
        current = current->next;

    return current->data;
}

/*
 *  getFirst
 *
 *  Retrieves the first element of the list
 *
 *  Returns: first element in the list
 *
 */
template <class Type>
Type SortedCircularDLL<Type>::getFirst() const
{
    // Check if the list is empty   
    if(dummyNode->next == dummyNode)
        return (Type)NULL;
    
    return dummyNode->next->data;
}

/*
 *  getLast
 *
 *  Retrieves the last element of the list
 *
 *  Returns: Last element in the list
 *
 */
template <class Type>
Type SortedCircularDLL<Type>::getLast() const
{
    // Check if the list is empty
    if(dummyNode->next == dummyNode)
        return (Type)NULL;

    return dummyNode->prev->data;
}

/*
 *  firstIndex
 *
 *  Retrieves the first index of an element in the list
 *
 *  Parameters: e - element to be searched in the list
 *  Returns: index of the first appearance of this element in the list
 *
 */
template <class Type>
int SortedCircularDLL<Type>::firstIndex(const Type &e) const
{
    // Check if the list is empty
    if(dummyNode->next == dummyNode)
        return -1;

    nodeType<Type> *current = dummyNode->next;
    for(int i=0; i<this->currentSize; i++)
    {
        if(current->data == e)
            return i;

        current = current->next;
    }

    return -1;
}

/*
 *  lastIndex
 *
 *  Retrieves the last index of an element in the list
 *
 *  Parameters: e - element to be searched in the list
 *  Returns: index of the last appearance of this element in the list
 *
 */
template <class Type>
int SortedCircularDLL<Type>::lastIndex(const Type &e) const
{
    // Check if the list is empty
    if(dummyNode->next == dummyNode)
        return -1;

    nodeType<Type> *current = dummyNode->prev;
    for(int i=this->currentSize-1; i>=0; i--)
    {
        if(current->data == e)
            return i;

        current = current->prev;
    }

    return -1;
}

/*
 *  count
 *
 *  Number of times an element is in the list
 *
 *  Parameters: e - element to be searched in the list
 *  Returns: number of time this element was found in the list
 *
 */
template <class Type>
int SortedCircularDLL<Type>::count(const Type &e) const
{
    // Check if the list is empty
    if(dummyNode->next == dummyNode)
    {
        std::cout<<"ERROR: The List is empty"<<std::endl;
        return -1;
    }

    nodeType<Type> *current = dummyNode->next;
    int c = 0;

    while(current != dummyNode)
    {
        if(current->data == e)
            c++;

        current = current->next;
    }
    return c;
}

/*
 *  clear
 * 
 *  Deletes all the nodes in the list
 *  
 */
template<class Type>
void SortedCircularDLL<Type>::clear()
{ 
    for(int i=0; i<=this->currentSize; i++)
        removeAt(0);
    
    dummyNode->next = dummyNode;
    dummyNode->prev = dummyNode;
    this->currentSize = 0;

}

/*
 *
 * Print the contents of the list in reverse order
 *
 */
template <class Type>
void SortedCircularDLL<Type>::printReverse() const
{
    nodeType<Type> *current = dummyNode->prev;

    while (current != dummyNode)
    {
        std::cout << current->data << " ";
        current = current->prev;
    }
    std::cout << std::endl;
}

/*
 *
 *  Print the elements in the list
 *
 */
template <class Type>
void SortedCircularDLL<Type>::print() const
{
    nodeType<Type> *current = dummyNode->next;
    while (current != dummyNode)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/*
 * operator<<
 *
 * Overload the << operator to output the list using an output stream.
 *
 * Parameters: os  - Output stream to use
 *             list - list to output
 * Returns: Output stream that was used
 *
 */
template <class Type>
std::ostream &operator<<(std::ostream &os, const SortedCircularDLL<Type> &list)
{
    nodeType<Type> *current = list.dummyNode->next;

    while (current != list.dummyNode)
    {
        os << current->data << " ";
        current = current->next;
    }

    os << "\n";

    return os;
}

/*
 *  copyList
 *  
 *  adds the elements of a list into another list
 *  
 *  Parameters: list - list to copy the elements from
 *  
 */
template<class Type>
void SortedCircularDLL<Type>::copyList(const SortedCircularDLL<Type>& otherList)
{
    // Create pointer of type node to traverse the list
    nodeType<Type> *current = otherList.dummyNode->next;
    // Add the elements of our other list into our list
    while (current != otherList.dummyNode)
    {
        this->add(current->data);
        current = current->next;
    }
}
/*
 *  Overloading the = operator
 * 
 *  Copies the elements of a list into another list
 * 
 *  Parameter:  otherList - the list that we want to copy from
 *  Return:     *this -  our copy of otherList
 */
template<class Type>
const SortedCircularDLL<Type>& SortedCircularDLL<Type>::operator=(const SortedCircularDLL<Type> &otherList) 
{
    // Avoid self-assignment
    if (this != &otherList) 
	{
        // Delete the elements of the list
        this->clear();
        // Add all of the elements of our list to the new copy list
        this->copyList(otherList);
    }

    return *this;
}

/*
 *  Copy Constructor
 *  Creates a copy of our list
 *  Parameters: otherList - list to apply copy constructor to(this will be our copy of the original list)
 *
 */
template <class Type>
SortedCircularDLL<Type>::SortedCircularDLL(const SortedCircularDLL<Type> &otherList)
{
    this->dummyNode = new nodeType<Type>;
    this->dummyNode->prev = dummyNode;
    this->dummyNode->next = dummyNode;
    this->dummyNode->data = (Type)NULL;
    this->currentSize = 0;

    // Add all of the elements of our list to the new copy list
    this->copyList(otherList);
}

#endif
