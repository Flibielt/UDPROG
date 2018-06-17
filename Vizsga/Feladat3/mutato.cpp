#include <iostream>
#include <string>

/*
1. (*1) Vezessük be a következõket: karakterre hivatkozó mutató, 10 egészbõl álló
tömb, 10 egészbõl álló tömb referenciája, karakterláncokból álló tömbre hivatkozó
mutató, karakterre hivatkozó mutatóra hivatkozó mutató, konstans egész,
konstans egészre hivatkozó mutató, egészre hivatkozó konstans mutató. 
Mindegyiknek adjunk kezdeti értéket.
*/

int main()
{
	char betu = 'x';
	int szam = 10;
	
	char *cm = &betu;
	int tomb = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::string &tombr[9];
	char **cmm = &cm;
	int const konstans = 10;
	int const * konstansM = &konstans;
	int *const Mkonstans;
}
