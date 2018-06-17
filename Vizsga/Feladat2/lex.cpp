#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

int main(int argc, char * argv[]){
	
	if (argc < 1)
	{
		cout << "Adj meg egy fájlt\n";
		return -1;
	}
	
	ifstream fin;
	fin.open(argv[1]);
	
	char ch;

	int betu = 0;
	int sor = 0;
	int szam = 0;
	int space = 0;
	int spec = 0;

	while(fin.get(ch)){
 		if(ch == ' ' || ch == '\t'){
			space++;
		}
		//Az ékezetes betűket nem számolja bele,
		//mert azok nem 1 bájton tárolódnak
		if(isalpha(ch)){
			betu++;
		}
		if(isdigit(ch)){
			szam++;
		}
		if(ch == '\n'){
			sor++;
		}
		//Speciális karakter, mint például a :
		if(ispunct(ch)){
			spec++;
		}	

	}
	fin.close();
	cout << "Szam: " << szam << "\nBetu: " << betu << "\nSpace: " << space << "\nSor: " << sor << "\nSpec: " << spec << endl;
	
}
