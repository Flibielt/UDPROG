Beugró:
A második védési program képet adjon vissza és azt mentsd ki a fájlrendszerbe

A működéshez szükséges a png++ könyvtár:
http://download.savannah.nongnu.org/releases/pngpp/

Elsőnek készíts el egy mandelbrot halmazt:
    g++ mandelpng.cpp `libpng-config --ldflags` -o mandelpng
    ./mandelpng fájlnév
Ezután jöhet a lényeg:
    g++ mlp.hpp main.cpp -o perc -lpng -std=c++11
    ./perc kép fájlnév

Lehet, hogy rosszul értelmeztem a feladatot és akkor valami olyasmi kell, mint a png.c
    gcc png.c -o png -lpng
    ./png
