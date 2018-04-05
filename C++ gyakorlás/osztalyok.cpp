#include <iostream>

using namespace std;

class Rectangle
{
    private:
    double x, y;

    public:
    void sideLength(double x, double y);
    double area();
};

void Rectangle::sideLength(double x, double y)
{
    this -> x = x; //a this az adott objektumra mutat
    this -> y = y;
}

double Rectangle::area()
{
    return x * y;
}

int main()
{
    //cout << "A feladatok: https://erlerobotics.gitbooks.io/erle-robotics-cpp-gitbook/classes_and_structs/exercises_classes.html" << endl;
    Rectangle teglalap;
    double x, y;
    cout << "Téglalap adatai:\n";
    cout << "Magasság: ";
    cin >> x;
    cout << "Hosszúság: ";
    cin >> y;

    teglalap.sideLength(x,y);
    cout << "Téglalap területe: "<< teglalap.area() << endl;
    //teglalap.x = 10; hibás, az x private

    return 0;
}






