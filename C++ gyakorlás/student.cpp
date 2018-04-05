#include <iostream>
#include "student.h"

using namespace std;

Student::Student(string name, double mark1, double mark2)
{
    (*this).name = name;   //ez a módszer ekvivalens
    this -> mark1 = mark1; //ezzel a módszerrel
    this -> mark2 = mark2;
}

void Student::disp()
{
    cout << "Diák neve: " << name << endl;
    cout << "Média jegyeinek átlaga: " << (mark1 + mark2) / 2 << endl;
}

int main()
{

    string name;
    double mark1, mark2;

    cout << "Diák neve: ";
    cin >> name;

    cout << "Jegyek: \n";
    cout << "1. jegy: ";
    cin >> mark1;
    cout << "2. jegy: ";
    cin >> mark2;

    Student diak(name, mark1, mark2);
    diak.disp();

    return 0;
}
