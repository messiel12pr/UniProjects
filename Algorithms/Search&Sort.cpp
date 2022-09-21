/* 
 *  Search & Sort
 *
 *  Using Selection Sort and Binary Search
 * 
 *  Joel M. Gonzalez Rodriguez	
*/

#include <iostream>
#include <cstdlib>
#include <time.h>

class SorteoBusqueda
{
    private:
        int nums[20];
        int first, last;

    public:
        void setNum(int []);
        void setNumABuscar(int);
        void showNum(int []);
        int minLocation(int [ ], int, int);
        void swap(int [ ], int, int);
        void selectionSort(int []);
        void binarySearch(int, int []);
};

using namespace std;

int main()
{   
    SorteoBusqueda selSortBinSearch;
    int numRand[20];
    int numABuscar = 0;

    selSortBinSearch.setNum(numRand);

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"Array antes de ser sorteado "<<endl;

    selSortBinSearch.showNum(numRand);
    selSortBinSearch.selectionSort(numRand);

    cout<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

    cout<<"Array despues de ser sorteado "<<endl;

    selSortBinSearch.showNum(numRand);

    cout<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

    cout<<"Entre el numero a buscar en el array: "<<endl;
    cin>>numABuscar;
    

    selSortBinSearch.binarySearch(numABuscar, numRand);

    return 0;
}

void SorteoBusqueda::setNum(int nums[])
{
    srand(time(0));

    for(int i=0; i<20; i++)
    {
        nums[i] = rand(   ) % 100;
    }
}

void SorteoBusqueda::showNum(int nums[])
{
    for(int i=0; i<20; i++)
    {
        cout<<nums[i]<<" ";
    }
}

int SorteoBusqueda::minLocation(int nums[ ], int first, int last)
{
    int index;
    index = first;

    for(int i = first + 1; i <= last; i++)
        if(nums[i] < nums[index])
            index = i;
    
    return index;
}

void SorteoBusqueda::swap(int nums[ ], int first, int last)
{
    int temp;

    temp = nums[first];
    nums[first] = nums[last];
    nums[last] = temp;
}

void SorteoBusqueda::selectionSort(int nums[])
{
    int index;

    for(int i=0; i<20; i++)
    {
        index = minLocation(nums, i, 20-1);
        swap(nums, i, index);
    }
}

void SorteoBusqueda::binarySearch(int n, int nums[])
{
    int left, right, middle;
    bool found = false;

    left = 0;
    right = 19;

    while(!found && left <= right)
    {
        middle = (left+right)/2; 

        if (nums[middle] == n)
        {
            found = true;
            break;
        }

        else if (nums[middle] > n)
            right = middle - 1;

        else 
            left = middle + 1;
    }

    if (found)
        cout<<"El indice del #"<<n<<" en el array es "<<middle;

    else
        cout<<"Este numero no fue encontrado"<<endl;

}
