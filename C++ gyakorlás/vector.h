//header fájl a classes.cpp-hez
class Point
{
public:
    double x, y;
    void print();
    void offset(double offsetX, double offsetY);
    Point(); //konstruktor
    Point(double nx, double ny); //2 paraméteres konstruktor
    Point(Point *p); //pointeres konstruktor
};


class Vector
{
public:
    Point start, end;
    void offset(double offsetX, double offsetY);
    void print();
};
