#!/bin/bash

echo "" > Makefile
echo "GCC = g++" >> Makefile
echo "FLAGS = -O" >> Makefile
echo "" >> Makefile
echo ".cpp.o: ; \$(GCC) \$(FLAGS) -o \$*.o -c \$*.cpp" >> Makefile
echo "" >> Makefile
echo -n "all: " >> Makefile

ls | sed -n /".cpp$"/p > fajlok.txt
while IFS='' read -r line || [[ -n "$line" ]]; do
    hossz=${#line}
    echo -n "${line:0:hossz-4} " >> Makefile
done < fajlok.txt
echo "" >> Makefile
echo "" >> Makefile

ls | sed -n /".cpp$"/p > fajlok.txt
while IFS='' read -r line || [[ -n "$line" ]]; do
    hossz=${#line}
    echo "${line:0:hossz-4}: ${line:0:hossz-4}.o" >> Makefile
    echo "	g++ -o \$@ \$@.o" >> Makefile
    echo "" >> Makefile
done < fajlok.txt

make

if test $# -eq 0; then
    echo "Tipp:"
    echo "Argumentumként megadathatod a futtatni kívánt programot"
else
    prog=$1
    if test ${prog:${#prog}-4:4} == ".cpp"
    then
        ./${prog:0:${#prog}-4}
    elif test ${prog:${#prog}-2:2} == ".o"
    then
        ./${prog:0:${#prog}-2}
    else
        ./$prog
    fi
fi




