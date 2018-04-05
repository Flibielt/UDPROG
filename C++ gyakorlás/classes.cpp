#include <iostream>
#include "vector.h" //a header fájlokat így kell hozzáfűzni

using namespace std;

Point::Point()
{
    x = y = 0.0;
    cout << "Új pont létrehozva\n";
}

Point::Point(double nx, double ny)
{
    x = nx;
    y = ny;
    cout << "Új pont létrehozva 2 paraméteres konstruktorrral\n";
}

Point::Point(Point *p)
{
    x = p -> x;
    y = p -> y;
    cout << "Új pont létrehozva pointeres koinstruktorral\n";
}

void Point::print()
{
    cout << "(" << x << ", " << y << ")\n";
}

void Point::offset(double offsetX, double offsetY)
{
    x += offsetX;
    y += offsetY;
}

void Vector::offset(double offsetX, double offsetY)
{
    start.x += offsetX;
    end.x += offsetX;
    start.y += offsetY;
    end.y += offsetY;
}

void Vector::print()
{
    cout << "(" << start.x << ", " << start.y << ") -> ";
    cout << "(" << end.x << ", " << end.y << ")\n";
}

void offsetPoint (Point &p, double x, double y);
void offsetPoint (Point *p, double x, double y);

int main()
{

    Point p;
    p.x = 3.0;
    p.y = 4.0;
    offsetPoint(p, 1.0, 2.0);
    cout << "(" << p.x << ", " << p.y << ")" << endl;
    offsetPoint(&p, 1.0, 2.0);
    cout << "(" << p.x << ", " << p.y << ")" << endl;

    
    Vector v;
    v.start.x = 1.0;
    v.start.y = 2.5;
    v.end.x = 10.7;
    v.end.y = 7.5;
    v.print();
    v.offset(1.0, 2.0);
    v.print();

    Point p2(5.5, 6.6);
    p2.print();
    Point p3(&p2);
    p3.print();
    p3.offset(1.0, 1.0);
    p3.print();
    return 0;
}

/*
void offsetPoint (Point p, double x, double y)
{
    //ez az eljárás nem csinál semmit, mert csak egy másolaton dolgozik
    p.x += x;
    p.y += y;
}
*/

void offsetPoint (Point &p, double x, double y)
{
    //ha viszont referenciaként adjuk át, akkor működik
    p.x += x;
    p.y += y;
}
void offsetPoint (Point *p, double x, double y)
{
    //pointerekkel is működik
    p -> x += x;
    p -> y += y;
}



