#include <iostream>
#include<vector>

using namespace std;

class lista
{
private:
    class elem
    {
    private:
        int ertek;
        elem * kovetkezo;

    public:
        elem()
        {
            ertek = 0;
            kovetkezo = NULL;
        }
        elem(int x)
        {
            ertek = x;
            kovetkezo = NULL;
        }

        int getErtek() const
        {
            return ertek;
        }
        elem* kovetkezik() const
        {
            return kovetkezo;
        }

        void ujElem(elem* uj)
        {
            kovetkezo = uj;
        }
    };


    elem* fej = new elem();

public:
    elem* aktualis;

    lista()
    {
        std::cout << "Konstruktor\n";
        aktualis = fej;
    }

    ~lista()
    {
        std::cout << "Destruktor\n";
        szabadit(fej);
    }

    void szabadit(elem* aktElem)
    {
        if(aktElem != NULL)
        {
            szabadit(aktElem->kovetkezik());
            delete aktElem;
        }
    }

    lista& operator <<(int x)
    {
        elem* uj = new elem(x);


        while (aktualis->kovetkezik() != NULL)
            aktualis = aktualis->kovetkezik();

        aktualis->ujElem(uj);
        aktualis = aktualis->kovetkezik();

        return *this;
    }

    void kiiras()
    {
        aktualis = fej->kovetkezik();
        int i = 0;

        while (aktualis->kovetkezik() != NULL)
        {
            i++;
            cout << i << ". elem: " << aktualis->getErtek() << '\n';
            aktualis = aktualis->kovetkezik();
        }
        cout << ++i << ". elem: " << aktualis->getErtek() << '\n';
    }


    lista(const lista& regi)
    {
        std::cout << "Copy ctor\n";

        /*
        fej = masol(regi.fej);
        aktualis = fej;
        */
        *this = regi;
    }

    lista& operator=(const lista& regi)
    {
        std::cout << "Copy assign\n";
        fej = masol(regi.fej);
        return *this;
    }

    elem* masol(elem* egyed)
    {
        elem* ujElem = NULL;
        if(egyed != NULL)
        {

            ujElem = new elem(egyed->getErtek());

            ujElem->ujElem(masol(egyed->kovetkezik()));


        }
        return ujElem;
    }

    lista(lista&& regi)
    {
        std::cout << "Move ctor\n";
        //fej = std::move(other.fej);
        fej = nullptr;
        *this = std::move(regi);
    }
    lista& operator=(lista&& regi)
    {
        std::cout << "Move assign\n";
        std::swap(fej, regi.fej);
        return *this;
    }

};

int main()
{
    lista lista1;

    lista1 << 51;
    lista1 << 10;
    lista1 << 49;
    lista1 << 34;
    lista1 << 75;

    std::cout << "\nLista1:\n";
    lista1.kiiras();

    lista lista2 = lista1;
    std::cout << "\nLista2:\n";
    lista2.kiiras();
    lista2 << 69;
    std::cout << "\nLista2:\n";
    lista2.kiiras();
    std::cout << "\nLista1:\n";
    lista1.kiiras();

    lista lista3 = std::move(lista1);
    std::cout << "\nLista3:\n";
    lista3.kiiras();
    lista3 << 20;
    std::cout << "\nLista3:\n";
    lista3.kiiras();
    std::cout << "\nLista1:\n";
    lista1.kiiras();

    return 0;
}

