#include <iostream>

using namespace std;

int main()
{

    int i = 12;
    int *pI = &i;
    int **pPI = &pI;
    
    cout << "i: " << **pPI << endl;
    cout << "*pI: " << pI << endl;
    cout << "**pPI: " << pPI << " " << *pPI << endl;


    return 0;
}
