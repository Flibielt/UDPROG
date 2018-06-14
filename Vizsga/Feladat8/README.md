### Beugró:
<p>A második védési program képet adjon vissza és azt mentsd ki a fájlrendszerbe<br>
A működéshez szükséges a png++ könyvtár:<br>
http://download.savannah.nongnu.org/releases/pngpp/<br>
Valamint telepíteni kell a libpng könyvtárat:<br>
<code>sudo apt-get install libpng-dev</code></p>

<p>Elsőnek készíts el egy mandelbrot halmazt:<br>
<code>g++ mandelpng.cpp `libpng-config --ldflags` -o mandelpng</code><br>
<code>./mandelpng fájlnév</code><br>
Ezután jöhet a lényeg:<br>
<code>g++ mlp.hpp main.cpp -o perc -lpng -std=c++11</code><br>
<code>./perc kép</code><br></p>
<p>Lehet, hogy rosszul értelmeztem a feladatot és akkor valami olyasmi kell, mint a png.c<br>
<code>gcc png.c -o png -lpng</code><br>
<code>./png</code></p><br>

### Főtéma:
<p>Az első védési program kimenő állományának a kezelése.<br>
  <code>g++ z3a9.cpp -o binfa -std=c++11</code><br>
  <code>./binfa</code></p>

