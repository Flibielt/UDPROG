#include <iostream>

//g++ int.cpp -o int -std=c++11
//./int

class Int
{
private:
	int ertek;
	
public:
	Int()
	{
		std::cout << "Int elem létrehozva\n";
		ertek = 0;
	}
	Int(int szam)
	{
		std::cout << "Int elem létrehozva, tárolt szám értéke: " << szam << std::endl;
		ertek = szam;
	}
	~Int()
	{
		std::cout << "Int elem felszabadítva\n";
		std::cout << "Tárolt érték: " << ertek << "\n\n";
	}
	
	int getErtek()
	{
		return ertek;
	}
	
	
	int operator+(int x)
	{
		return ertek + x;
	}
	
	int operator+(Int& x)
	{
		return ertek + x.getErtek();
	}
	
	int operator-(int x)
	{
		return ertek - x;
	}
	int operator-(Int& x)
	{
		return ertek - x.getErtek();
	}
	
	int operator*(int x)
	{
		return ertek * x;
	}
	int operator*(Int& x)
	{
		return ertek * x.getErtek();
	}
	
	
	Int & operator+=(int x)
	{
		ertek += x;
	}
	Int & operator+=(Int& x)
	{
		ertek += x.getErtek();
	}
	Int & operator-=(int x)
	{
		ertek -= x;
	}
	Int & operator-=(Int& x)
	{
		ertek -= x.getErtek();
	}
	Int & operator*=(int x)
	{
		ertek *= x;
	}
	Int & operator*=(Int& x)
	{
		ertek *= x.getErtek();
	}
	
	
	bool operator==(int x)
	{
		if(ertek == x)
			return true;
		else
			return false;
	}
	bool operator==(Int& x)
	{
		if(ertek == x.getErtek())
			return true;
		else
			return false;
	}
	bool operator>(int x)
	{
		if(ertek > x)
			return true;
		return false;
	}
	bool operator>(Int& x)
	{
		if(ertek > x.getErtek())
			return true;
		return false;
	}
	bool operator>=(int x)
	{
		if(ertek >= x)
			return true;
		return false;
	}
	bool operator>=(Int& x)
	{
		if(ertek >= x.getErtek())
			return true;
		return false;
	}
	
	bool operator<(int x)
	{
		if(ertek < x)
			return true;
		return false;
	}
	bool operator<(Int& x)
	{
		if(ertek < x.getErtek())
			return true;
		return false;
	}
	bool operator<=(int x)
	{
		if(ertek <= x)
			return true;
		return false;
	}
	bool operator<=(Int& x)
	{
		if(ertek <= x.getErtek())
			return true;
		return false;
	}
	
	
};

std::ostream & operator<< ( std::ostream & os, Int & x )
{
	os << x.getErtek();
	return os;
}

std::istream & operator>> (std::istream & is, Int & x)
{
	int szam;
	is >> szam;
	x = szam;
}

int main()
{
	Int x = 10;
	Int y = 20;
	std::cout << x << std::endl;
	x+= 5;
	
	std::cout << x << std::endl;
	std::cout << "x + 5 = " << x + 5 << std::endl;
	std::cout << x << std::endl;
	
	//std::cout << "Destruktálod?!\n";
	//Elsőnek érték szerint adtam át az Int objektumot, így létrehozott, majd felszabadított egy Int objektumot
	//Ha referenciával van átadva, akkor sokkal hatékonyabb
	if (x < y)
		std::cout << x << " kisebb, mint " << y << std::endl;
	if (y > x)
		std::cout << x << " kisebb, mint " << y << std::endl;
	
	std::cout << "x + y = " << x + y << std::endl;
	Int z = x * y;
	std::cout << x << "*" << y <<"=" << z << std::endl;
	
	
	Int q;
	std::cout << "\nAdj meg egy számot: ";
	std::cin >> q;
	std::cout << "Q értéke: " << q << std::endl;
	return 0;
}
