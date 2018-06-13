Beugró:
A harmadik védési program laborjegy kiszámoló része.
Bátfai fénykardjából a feladathoz szükséges részek. A teljes fénykardja:
https://github.com/nbatfai/future/blob/master/cs/F9F2/fenykard.cpp

A feladathoz szükséges a Boost könyvtár:
    sudo apt-get install libboost-all-dev

A fénykard használata:
    g++ fenykard.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -std=c++14
    ./fenykard adatbázisfájl

