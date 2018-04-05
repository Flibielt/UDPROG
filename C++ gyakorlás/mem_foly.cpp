#include <iostream>

using namespace std;

int main()
{

    //int *a; /* Szegmentációs hiba*/
              /*   Nincs lefoglalt tárhely*/

    int *a = new int;
    *a = 69;
    cout << "Cím: " << a << endl << "Érték: " << *a << endl;

    delete a;
    cout << a << endl;
    cout << *a << endl;   
 
    cout << sizeof(a) << endl;    
}
