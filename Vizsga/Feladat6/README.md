### Beugró:
<p>Második védési programban funktor az input képet adja vissza.<br>
A működéshez szükséges a png++ könyvtár:<br>
http://download.savannah.nongnu.org/releases/pngpp/<br>
Valamint telepíteni kell a libpng könyvtárat:<br>
<code>sudo apt-get install libpng-dev</code></p>

<p>Elsőnek készíts el egy mandelbrot halmazt:<br>
<code>g++ mandelpng.cpp `libpng-config --ldflags` -o mandelpng</code><br>
<code>./mandelpng fájlnév</code></p>

<p>Ezután jöhet a lényeg:<br>
<code>g++ mlp.hpp main.cpp -o perc -lpng -std=c++11</code><br>
<code>./perc kép</code></p>

### Főtéma:
<p>Saját Int osztály nyomkövető üzenetekkel.<br>
<code>g++ int.cpp -o int -std=c++11</code><br>
<code>./int</code></p>
