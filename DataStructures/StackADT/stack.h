#define TAMANOMAXIMO 100
template <class genType>
class Stack
{
    private:
        int largo;
        genType lista[TAMANOMAXIMO];
        int stackTop;
        

    public:
        Stack();//Constructor, inicializa los valores a 0

        genType valorParaInsertar();//Funcion de tipo elemType que pide un valor al usuario y lo devuelve
        void push(genType);//Funcion tipo void que recibe un elemento tipo elemType y lo inserta en el stack
        void peek();//Funcion para mirar el top del stack
        void pop();//funcion que elimina el primer valor del stack

        void oldPop();//funcion que elimina y printea el primer valor del stack

        bool isEmpty();//funcion tipo bool que devuelve true si la lista esta vacia o devuelve false si tiene valores
        bool isFull();//Funcion tipo bool que devuelve true si la lista esta llena o devuelve false si le queda espacio
        
        void setTop(int);//Setea el largo del stack
        int getLargo();//Funcion tipo int que le da return al largo del stack
        int getStackTop();//Funcion tipo int que le da return al valor actual del stack (stackTop)
};
