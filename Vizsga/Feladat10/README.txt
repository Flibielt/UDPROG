Beugró:
A harmadik védési program laborjegy kiszámoló része.
Bátfai fénykardjából a feladathoz szükséges részek. A teljes fénykardja:
https://github.com/nbatfai/future/blob/master/cs/F9F2/fenykard.cpp

A feladathoz szükséges a Boost könyvtár:
    sudo apt-get install libboost-all-dev

A fénykard használata:
    g++ fenykard.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -std=c++14
    ./fenykard adatbázisfájl

Főtéma:
Mandelbrot halmaz számolás több szálon.
A működéshez szükséges a png++ könyvtár:
http://download.savannah.nongnu.org/releases/pngpp/
Valamint telepíteni kell a libpng könyvtárat:
    sudo apt-get install libpng-dev

A Mandelbrot halmaz számolás:
    g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -o pmandelpngt
    g++ pmandelpngt.cpp `libpng-config --ldflags` -lpthread -O3 -o pmandelpngt
Az első fordítás a forráskódban volt, viszont a második fordítás a Párhuzamos programozás Linux/GNU környezetben című könyvben volt, a 47. oldaltól magyarázza a mandelbrotos példát.
http://docplayer.hu/14462879-Parhuzamos-programozas-gnu-linux-kornyezetben.html
Futtatni ugyanúgy lehet, mint a szekvenciális változatot:
     ./pmandelpngt kép
Az első változat nagyából kétszer annyi ideig számol, mint a második. Valószínűleg a második változat a szálak számán/használatán változtat.
