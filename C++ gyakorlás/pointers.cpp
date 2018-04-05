#include <iostream>

using namespace std;

void gyak1();
void gyak2();
void gyak3();
void gyak4();


int main()
{
    //cout << "Feladatok helye: https://erlerobotics.gitbooks.io/erle-robotics-cpp-gitbook/pointers/exercises_pointers.html" << endl;
    //gyak1();
    //gyak2();
    //gyak3();
    gyak4();



    return 0;
}

void gyak1()
{
    //kiiratás pointerekkel
    int a, b, *pa, *pb;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    pa = &a;
    pb = &b;
    cout << *pa << " " << *pb << endl;
}

void gyak2()
{
    //max a tömbben pointerben elmentve
    int db;
    cout << "Vektor mérete: ";
    cin >> db;
    
    int v[db];
    for (int j = 0; j < db; j++)
    {
        cout << j << ". elem: ";
        cin >> v[j];
    }

    int *pmax = &v[0];
    for (int j = 1; j < db; j++)
    {
        if (*pmax < v[j])
            pmax = &v[j];
    }

    cout << *pmax << endl;
}

void gyak3()
{
    int a;
    cout<<"Enter number:";
    cin>>a;
    int *b=&a;

    cout<< " The pointer values is "<< *b << " the memory address is: "<<  b << endl;

}

void gyak4()
{
   char str[] = "A string.";
   char *pc = str;

   cout << str[0] <<' '<< *pc <<' '<<pc[3]<<"\n";
   pc += 2;
   cout <<*pc<<' '<< pc[2] <<' '<< pc[5] << '\n';

}



