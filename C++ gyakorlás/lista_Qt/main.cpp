#include <iostream>
#include <lista.h>

using namespace std;

int main()
{

    lista list;
    cout << "Láncolt lista objektumokkal megvalósítva:\n" << "Add meg a lista elemienek a számát: ";
    int n = 0;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cout << i << ". elem: ";
        int x = 0;
        cin >> x;


        //list.adatFeltolt(x);
        list << x;  /*Hát mennyivel szebb már így?!*/
    }

    cout << "Adatok kiírása:\n";
    list.kiiras();

    //cout << "Lista típus mérete: " << sizeof(list) << endl;

    //lista létrehozva másoló konstruktorral
    lista list2(list);
    list2.kiiras();

    //lista létrehozva mozgató konstruktorral
    lista list3 = std::move(list);
    list3.kiiras();

    return 0;
}

