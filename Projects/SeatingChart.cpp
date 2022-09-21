/*
 *  Program that simulates an airlines seating chart
 *
 *  Joel M. Gonzalez Rodriguez
*/
#include <iostream>
#include <iomanip>
#include <cctype>

enum columnas {A, B, C, D, E, F};

using namespace std;
int main()
{	
    columnas column;
    int fila, numSilla = 0;
    char continuar = 'x';
    char silla;
    char asientos[13][6] = {{'*','*','X','*','X','X'}, 
                            {'*','X','*','X','*','X'}, 
                            {'*','*','X','X','*','X'}, 
                            {'X','*','X','*','X','X'},
                            {'*','X','*','X','*','*'}, 
                            {'*','X','*','*','*','X'}, 
                            {'X','*','*','*','X','X'}, 
                            {'*','X','*','X','X','*'},
                            {'X','*','X','X','*','X'}, 
                            {'*','X','*','X','X','X'}, 
                            {'*','*','X','*','X','*'}, 
                            {'*','*','X','X','*','X'},
                            {'*','*','*','*','X','*'}};
    do
    {
        cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl<<endl;
        cout<<"Asientos disponibles representados con asterisco (*) "<<endl;
        cout<<"Asientos no disponibles representados con una X "<<endl;
        cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
        cout<<"           A    B    C    D    E    F "<<endl;    

        for(int k=0; k<13; k++)
        {
            cout<<setw(5)<<"Fila "<<setw(2)<<left<<k+1;
            for (column = A; column <= F; column = static_cast<columnas>(column+1))
                cout<<setw(5)<<right<<asientos[k][column];

            cout<<endl;
        }

        cout<<"Ingrese el numero de fila y letra de asiento deseado: "<<endl;
        cin>>fila>>silla;
        
        fila = fila-1;

        if(fila < 0 || fila > 13)
        {
            cout<<"Error: el numero de fila que ingreso no existe, ingrese un numero de fila del 1 al 13..."<<endl;
            return 0;
        }
        silla = toupper(silla);

        switch(silla)
        {
            case 'A':
                numSilla = 0;
                break;
            
            case 'B':
                numSilla = 1;
                break;
            
            case 'C':
                numSilla = 2;
                break;
            
            case 'D':
                numSilla = 3;
                break;
            
            case 'E':
                numSilla = 4;
                break;
            
            case 'F':
                numSilla = 5;
                break;
            
            default:
                cout<<"Error: letra incorrecta, ingrese una letra de la A a la F..."<<endl;
                return 0;
        }

        if(asientos[fila][numSilla] != 'X')
        {
            asientos[fila][numSilla] = 'X';
            cout<<"El asiento "<<fila+1<<silla<<" ha sido reservado..."<<endl;
            cout<<"Gracias por viajar con nosotros!"<<endl;
        }
        
        else 
            cout<<"El asiento "<<fila+1<<silla<<" no esta disponible..."<<endl;

        cout<<"Presione la C si desea continuar"<<endl;
        cout<<"Para salir del programa oprima X"<<endl;
        
        cin>>continuar;
        continuar = toupper(continuar);
    }
    while(continuar == 'C');
    

    return 0;
}
