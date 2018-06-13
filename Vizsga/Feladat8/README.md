### Beugró:
<p>A második védési program képet adjon vissza és azt mentsd ki a fájlrendszerbe<br>
A működéshez szükséges a png++ könyvtár:<br>
http://download.savannah.nongnu.org/releases/pngpp/<br>
Valamint telepíteni kell a libpng könyvtárat:<br>
<code>sudo apt-get install libpng-dev</code><br>

Elsőnek készíts el egy mandelbrot halmazt:</p>
<code>g++ mandelpng.cpp `libpng-config --ldflags` -o mandelpng</code>
<code>./mandelpng fájlnév</code>
<p>Ezután jöhet a lényeg:<br>
<code>g++ mlp.hpp main.cpp -o perc -lpng -std=c++11
  
./perc kép fájlnév</code><br>
Lehet, hogy rosszul értelmeztem a feladatot és akkor valami olyasmi kell, mint a png.c<br>
<code>gcc png.c -o png -lpng</code><br>
<code>./png</code></p><br>
