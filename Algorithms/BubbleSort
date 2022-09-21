/* 
 *  Bubble Sort Algorithm using class
 *
 *  Joel M. Gonzalez Rodriguez
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

class Bubble
{
    private:
        int arr[5];

    public:
        void asignValue();
        void sort();
        void printArr();
};

using namespace std;
int main()
{   
    Bubble sorteoArray;

    sorteoArray.asignValue();

    cout<<"Array antes del Bubble Sort "<<endl;

    sorteoArray.printArr();

    cout<<"Array luego del Bubble Sort "<<endl;

    sorteoArray.sort();

    sorteoArray.printArr();

    return 0;
}

void Bubble::asignValue()
{
    srand(time(0));

    for(int i=0; i<5; i++)
    {
        arr[i] = rand() % 100;
    }
}

void Bubble::sort()
{     
    for(int i=1; i<5; i++)
    {
        for(int j=0; j<5-i; j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void Bubble::printArr()
{
    for(int i=0; i<5; i++)
    {
        cout<<arr[i]<<" ";
    }

    cout<<endl;
}
