#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
//https://theboostcpplibraries.com/boost.filesystem-iterators


int pontokBegyujtese(boost::filesystem::path file)
{
	int pontok = 0;
	
	boost::filesystem::ifstream ifs{file};
	
	std::string sor;
	
	while (std::getline(ifs, sor))
	{
		int r = sor.find_last_of ( "0123456789" );
		int l = sor.find_last_not_of ( "0123456789", r );
		
		std::string val = sor.substr ( l, r );
		
		pontok += std::stoi ( val );
	}
	
	return pontok;
}

int main()
{
	
	boost::filesystem::path future = boost::filesystem::current_path().string() + "/City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1";
	boost::filesystem::path aktualis;
	if (boost::filesystem::exists(future))
	{
		boost::filesystem::recursive_directory_iterator rIt{future};
		while (rIt != boost::filesystem::recursive_directory_iterator{})
		{
			aktualis = *rIt++;
			if (boost::filesystem::is_regular_file(aktualis) && aktualis.extension().string() == ".props")
			{
				std::cout << aktualis.string() << '\n';
				std::cout << "Szerezhető pontok: " << pontokBegyujtese(aktualis) << '\n';
			}
		}
	}
	
	return 0;
}
