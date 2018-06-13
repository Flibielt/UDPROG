### Beugró:
<p>A harmadik védési program laborjegy kiszámoló része.<br>
Bátfai fénykardjából a feladathoz szükséges részek. A teljes fénykardja:<br>
https://github.com/nbatfai/future/blob/master/cs/F9F2/fenykard.cpp</p>

<p>A feladathoz szükséges a Boost könyvtár:<br>
<code>sudo apt-get install libboost-all-dev</code></p>

<p>A fénykard használata:<br>
<code>g++ fenykard.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -std=c++14</code><br>
<code>./fenykard adatbázisfájl</code></p>

### Főtéma:
<p>Mandelbrot halmaz számolás több szálon.<br>
A működéshez szükséges a png++ könyvtár:<br>
http://download.savannah.nongnu.org/releases/pngpp/<br>
Valamint telepíteni kell a libpng könyvtárat:<br>
<code>sudo apt-get install libpng-dev</code></p>

<p>A Mandelbrot halmaz számolás:<br>
<code>g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -o pmandelpngt</code><br>
<code>g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -O3 -o pmandelpngt</code><br>
Az első fordítás a forráskódban volt, viszont a második fordítás a Párhuzamos programozás Linux/GNU környezetben című könyvben volt, a 47. oldaltól magyarázza a mandelbrotos példát.<br>
http://docplayer.hu/14462879-Parhuzamos-programozas-gnu-linux-kornyezetben.html<br>
Futtatni ugyanúgy lehet, mint a szekvenciális változatot:<br>
<code>./pmandelpngt kép</code><br>
Az első változat nagyából kétszer annyi ideig számol, mint a második. Valószínűleg a második változat a szálak számán/használatán változtat.</p>
