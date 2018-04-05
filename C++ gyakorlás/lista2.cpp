#include <iostream>

using namespace std;

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
        elem()
        {
            ertek = 0;
            kovetkezo = NULL;
        }
        //konstruktor paraméterrel
        elem(int x)
        {
            ertek = x;
            kovetkezo = NULL;
        }

        //visszaadja az elem által tárolt számot, kiiratáshoz kell
        //const, tehát nem tud megváltoztatni semmit
        int getErtek() const
        {
            return ertek;
        }

        //a szabadit függvényhez kell, mert közvetlenül nem tudja elérni a kovetkezo-t
        elem * kovetkezik() const
        {
            return kovetkezo;
        }

        //az új elem hozzáfűzése a listához
        //itt a már létrehozott elemet fűzzük hozzá
        void ujElem(elem * uj)
        {
            kovetkezo = uj;
        }


    };
    elem *fej;  //ha a fej is egy pointer
    elem x; //mindig kell valami, amire tud mutatni


    public:
    lista()
    {
        //létrehozásnál az aktuális a fejre mutat, hogy el tudjuk érni a lista többi elemét
        
        fej = &x;
        aktualis = fej; //itt egy változás
        cout << fej << '\n' << aktualis << '\n';
    }
    ~lista()
    {
        szabadit(fej -> kovetkezik());  //itt is egy változás
    }

    //ez mutat a lista aktuális elemére
    elem* aktualis;

    void szabadit(elem* elem)
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


    //új elem létrehozása
    void adatFeltolt(int x)
    {
        //pointerként hozzuk létre, mert az elem kovetkezo tagja is pointer
        elem *uj = new elem(x);
        //hozzáfűzzük a lsitához az új elemet
        aktualis -> ujElem(uj);
        //az aktuális mostmár az új elemre mutat
        aktualis = aktualis -> kovetkezik();
    }
    void operator<< (int x)
    {
        //ekvivalens az adatFeltolt függvénnyel
        elem *uj = new elem(x);
        aktualis -> ujElem(uj);
        aktualis = aktualis -> kovetkezik();
    }

    void kiiras()
    {
        //az aktuális a következő elemre fog mutatni
        //az elem objektumban a kovetkezo is egy pointer, ezért nem kell &
        //itt az aktuális a fej utáni első elemre mutat, tehát az első listelemre
        aktualis = fej -> kovetkezik();
        int i = 0;
        while(aktualis != NULL)
        {
            i++;
            cout << i << ". elem: " << aktualis -> getErtek() << endl;
            aktualis = aktualis -> kovetkezik();
        }
    }
    
};


int main()
{

    lista list;
    cout << "Láncolt lista objektumokkal megvalósítva:\n(A fej most egy pointer)\n" << "Add meg a lista elemienek a számát: ";
    int n = 0;
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cout << i << ". elem: ";
        int x;
        cin >> x;
        
        list << x;
    }
    
    cout << "Adatok kiírása:\n";
    list.kiiras();
    
    return 0;
}















