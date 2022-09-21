/* 
Joel M. Gonzalez Rodriguez	840-21-9588
*/

#include <ctime>
#include <iostream>
#include "stackHeader.h"
#define TAMANOMAXIMO 100

using namespace std;

template <class genType>//Constructor, inicializa los valores a 0
Stack <genType>::Stack()
{
    largo = TAMANOMAXIMO;
    stackTop = 0;
}

template <class genType>//funcion que elimina y printea el primer valor del stack
void Stack <genType>::oldPop()
{
    if(isEmpty())
        cout<<"Error el stack esta vacio"<<endl;

    else
        cout<<"EL elemento "<<lista[stackTop-1]<<" ha sido eliminado del stack"<<endl;

    stackTop--;

    if(stackTop<0)
        stackTop = 0;
}  

template <class genType>//funcion que elimina el primer valor del stack
void Stack <genType>::pop()
{
    if(!isEmpty())
        stackTop--;

    else
        cout<<"Error: El stack esta vacio"<<endl;
    
    if(stackTop<0)
        stackTop = 0;
}

template <class genType>//funcion tipo bool que devuelve true si la lista esta vacia o devuelve false si tiene valores
bool Stack <genType>::isEmpty()
{
    if(stackTop == 0)
        return true;

    else    
        return false;
}

template <class genType>//Funcion tipo bool que devuelve true si la lista esta llena o devuelve false si le queda espacio
bool Stack <genType>::isFull()
{
    if(stackTop == 100)
        return true;

    else    
        return false;
}

template <class genType>//Setea el largo del stack
void Stack <genType>::setTop(int t)
{
    if(t>TAMANOMAXIMO || t<1)
    {
        cout<<"Error el nuevo tamano no puede ser mayor que "<<TAMANOMAXIMO;
        cout<<" ni menor que 1"<<endl;
        cout<<"Oprima cualquier letra para continuar"<<endl;
        getch();
    }

    else
        if(t<largo)
        {
            cout<<"El nuevo tamano va a eliminar "<<largo-t<<" valores "<<endl;
        }
}

template<class genType>//Funcion de tipo elemType que pide un valor al usuario y lo devuelve
genType Stack <genType>::valorParaInsertar()
{
    genType valor;

    cout<<"Ingrese el valor"<<endl;
    cin>>valor;  

    return valor;
}

template<class genType>//Funcion tipo void que recibe un elemento tipo elemType y lo inserta en el stack
void Stack <genType>::push(genType n)
{
    if(!isFull())
    {
        lista[stackTop] = n;
        stackTop++;
    }
    
    else 
        cout<<"Error: La lista esta llena"<<endl;
}

template<class genType>//Funcion para mirar el top del stack
void Stack <genType>::peek()
{
    if(isEmpty())
        cout<<"La lista esta vacia!"<<endl;
        
    else
        cout<<lista[stackTop-1]<<endl;
}

template<class genType>//Funcion tipo int que le da return al largo del stack
int Stack<genType>::getLargo()
{
    return largo;
}

template<class genType>//Funcion tipo int que le da return al valor actual del stack (stackTop)
int Stack<genType>::getStackTop()
{
    return stackTop;
}
