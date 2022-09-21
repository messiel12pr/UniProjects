/* 
 *  This program calculates a ditch max area to hold water
 *  with a given base and vertex.
 *
 *  Joel M. Gonzalez Rodriguez
*/

#include <iostream>
#include <iomanip>
#include <locale>
#include <cmath>
#define PI 3.14159
using namespace std;

double areaTriangulo(double, double);
double baseTriangulo(double, double);
double alturaTriangulo(double, double);
double areaCuadrado(double, double);
double areaDique(double, double);
void imprimirEncabezamientoPrograma(double&, double&);
void imprimirEncabezamientoTabla();
void imprimirTabla(double, double, double, double, double, double);
double areaMax(double);

int main()
{
    double altura, base, baseT, vertice, angulo, arT, arC, arD, areaMax, anguloMax;

    cout<<fixed<<setprecision(2);

    cout<<"-------------------------------------------------------------------"<<endl;

    imprimirEncabezamientoPrograma(base, vertice);
    imprimirEncabezamientoTabla();

    cout<<"-------------------------------------------------------------------"<<endl;

    for(angulo = 90.0; angulo >= 0.0; angulo--)
    {
        baseT = baseTriangulo(angulo, vertice);
        altura = alturaTriangulo(angulo, vertice);
        arT = areaTriangulo(altura, baseT);
        arC = areaCuadrado(altura, base);
        arD = areaDique(arT, arC);

        if(arD > areaMax)
        {
            areaMax = arD;
            anguloMax = angulo;
        }
        
        imprimirTabla(angulo, baseT, altura, arT, arC, arD);
        
    }
    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"El angulo con mayor area es "<<anguloMax<<" con un area total de: "<<areaMax<<endl;

    return 0;
}

double baseTriangulo(double angulo, double vertice)
{
    double b=0;
    double rad = (PI/180)*angulo;
    b = vertice * cos(rad);

    return b;
}

double alturaTriangulo(double angulo, double vertice)
{
    double a = 0;
    double rad = (PI/180)*angulo;
    a = vertice * sin(rad);
     
    return a;
}

double areaTriangulo(double altura, double baseT)
{
    double areaT = 0;

    areaT = (baseT * altura)/2;
    
    return areaT;
}

double areaCuadrado(double altura, double base)
{
    double areaC = altura * base;

    return areaC;
}

double areaDique(double arT, double arC)
{
    double areaD = (arT*2) + arC;

    return areaD;
}

void imprimirEncabezamientoPrograma(double&base, double&vertice)
{
    cout<<"Ingrese la base y el vertice del trapesio"<<endl;
    cin>>base>>vertice;
}

void imprimirEncabezamientoTabla()
{
    cout<<"Angulo"<<setw(8)<<"Base"<<setw(10)<<"Altura"<<setw(16)<<"Area Triangulo"<<setw(15)<<"Area Cuadrado"<<setw(12)<<"Area Dique"<<endl;
}

void imprimirTabla(double angulo, double baseT, double altura, double arT, double arC, double arD)
{
    cout<<left<<fixed<<setprecision(2)<<setw(10)<<angulo<<setw(8)<<baseT<<setw(8)<<altura<<setw(16)<<arT<<setw(15)<<arC<<setw(12)<<arD<<endl;
}
