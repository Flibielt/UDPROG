#include <iostream>
#include "lista.h"

using namespace std;

lista::lista()
{
    //létrehozásnál az aktuális a fejre mutat, hogy el tudjuk érni a lista többi elemét
    aktualis = &fej;
}
lista::lista(const lista &regi)
{
    cout << "Másoló konstruktor\n";

    fej.ujElem(masol(regi.fej.kovetkezik(), regi.aktualis));

    if(regi.aktualis == &(regi.fej))
        aktualis = &fej;
}

lista::lista(lista && regi)
{
    cout << "Mozgató konstruktor\n";
    fej.ujElem(regi.fej.kovetkezik());
}

lista::~lista()
{
    cout << "Destruktor\n";
    szabadit(fej.kovetkezik());
}

void lista::szabadit(lista::elem* elem)
{
    if(elem != NULL)
    {
        ///szabadit(elem -> kovetkezo);
        //közvetlenül nem lehet elérni, mert a kovetkezo private tartományban van
        //ezért kell egy függvény, ami public és visszatérési értéke a kovetkezo
        szabadit(elem -> kovetkezik());
        delete elem;
    }
}

void lista::adatFeltolt(int x)
{
    //pointerként hozzuk létre, mert az elem kovetkezo tagja is pointer
    elem *uj = new elem(x);
    //hozzáfűzzük a lsitához az új elemet
    aktualis -> ujElem(uj);
    //az aktuális mostmár az új elemre mutat
    aktualis = aktualis -> kovetkezik();
}

void lista::operator<< (int x)
{
    //ekvivalens az adatFeltolt függvénnyel
    elem *uj = new elem(x);
    aktualis -> ujElem(uj);
    aktualis = aktualis -> kovetkezik();
}

void lista::kiiras()
{
    //az aktuális a következő elemre fog mutatni
    //az elem objektumban a kovetkezo is egy pointer, ezért nem kell &
    //itt az aktuális a fej utáni első elemre mutat, tehát az első listelemre
    aktualis = fej.kovetkezik();
    int i = 0;
    while(aktualis != NULL)
    {
        i++;
        cout << i << ". elem: " << aktualis -> getErtek() << endl;
        aktualis = aktualis -> kovetkezik();
    }

}

void lista::memoriaHely()
{
    aktualis = fej.kovetkezik();
    int i = 0;
    while(aktualis != NULL)
    {
        i++;
        cout << i << ". elem helye: " << aktualis << endl;
        aktualis = aktualis -> kovetkezik();
    }
}

lista::elem::elem()
{
    ertek = 0;
    kovetkezo = NULL;
}

lista::elem::elem(int x)
{
    ertek = x;
    kovetkezo = NULL;
}

int lista::elem::getErtek() const
{
    return ertek;
}

lista::elem * lista::elem::kovetkezik() const
{
    return kovetkezo;
}

void lista::elem::ujElem(elem * uj)
{
    kovetkezo = uj;
}

lista::elem *lista::masol(lista::elem * egyed, lista::elem * regiFej)
{
    //Másoló konstruktorhoz
    lista::elem * ujElem = NULL;
    if(egyed != NULL)
    {
        ujElem = new lista::elem(egyed -> getErtek());

        ujElem->ujElem(masol(egyed->kovetkezik(), regiFej));

        if(regiFej == egyed)
            fej = *ujElem;
    }
    return ujElem;
}

lista::elem lista::getFej()
{
    return fej;
}


