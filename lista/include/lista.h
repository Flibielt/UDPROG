#ifndef LISTA_H
#define LISTA_H


class lista
{
    private:
    //a listában definiáljuk az elem objektumot, így jelezvén az összetartozást
    //az elem tartalmazza az értéket és a következő elem helyét pointerben tárolva
    class elem
    {
        private:
        int ertek;
        elem * kovetkezo;


        public:
        //konstruktor
        elem();
        //konstruktor paraméterrel
        elem(int x);


        //visszaadja az elem által tárolt számot, kiiratáshoz kell
        //const, tehát nem tud megváltoztatni semmit
        int getErtek() const;

        //a szabadit függvényhez kell, mert közvetlenül nem tudja elérni a kovetkezo-t
        elem * kovetkezik() const;

        //az új elem hozzáfűzése a listához
        //itt a már létrehozott elemet fűzzük hozzá
        void ujElem(elem * uj);




    };
    elem fej;


    public:
    lista();
    //másoló konstruktor
    lista(const lista & regi);
    //mozgató konstruktor
    lista(lista && regi);
    ~lista();

    //ez mutat a lista aktuális elemére
    elem* aktualis;

    void szabadit(elem* elem);

    //új elem létrehozása
    void adatFeltolt(int x);
    //új elem létrehozása a << operátor túlterhelésével
    void operator<< (int x);

    //A másoló konstruktorhoz
    elem * masol (elem * egyed, elem * regiFej);

    void kiiras();
    void memoriaHely();

    //a fejet adja vissza értékül
    lista::elem getFej();

};
#endif // LISTA_H
