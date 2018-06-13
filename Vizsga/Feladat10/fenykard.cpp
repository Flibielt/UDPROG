#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/program_options.hpp>

///g++ fenykard.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -std=c++14
///./fenykard adatbazis

using Submarks = std::map< std::string, std::map< std::string, int > >;
// act_per_day["user"][ "vedes?" ] = jegy



std::map <std::string, int> get_marks ( Submarks & submarks )
{

        std::map <std::string, int> marks;

        for ( auto & user : submarks ) {


                int sum = std::accumulate ( user.second.begin(), user.second.end(), 0,
                [] ( int total, std::pair<std::string, int> pair ) {
                        return total + pair.second;
                } );

                marks[user.first] = sum / user.second.size();

        }

        return marks;

}

std::vector<std::pair<std::string, int>> sort_map ( std::map <std::string, int> &rank )
{
        std::vector<std::pair<std::string, int>> ordered;

        for ( auto & i : rank ) {
                if ( i.second ) {
                        std::pair<std::string, int> p {i.first, i.second};
                        ordered.push_back ( p );
                }
        }

        std::sort (
                std::begin ( ordered ), std::end ( ordered ),
        [ = ] ( auto && p1, auto && p2 ) {
                return p1.second > p2.second;
        }
        );

        return ordered;
}

void print_marks ( Submarks & submarks )
{
        for ( auto & user : submarks ) {


                int sum = std::accumulate ( user.second.begin(), user.second.end(), 0,
                [] ( int total, std::pair<std::string, int> pair ) {
                        return total + pair.second;
                } );


                std::cout << user.first << " #" << user.second.size() << " mark: " << sum / user.second.size() << std::endl;

        }
}

bool repl_mark ( Submarks & submarks, std::string name, std::string act, std::string root, std::string marks, int markv )
{
        bool replaced {false};


        if ( !act.find ( root ) ) {
            ///Így nem fordulhat elő az, hogy a II. védés eredményét beírja az I. védéshez is
            ///A 2. védésnek az eredményét enélkül beírná az 1. védéshez is
            ///A 3. védést, pedig a 2. és az 1.-höz is
            if (act.substr(0, act.find_last_of("/")) == root)
            {

                auto i = act.find ( marks );

                if ( i != std::string::npos ) {
                    //std::cout << marks << " " << i << std::endl;

                        if ( submarks[name].find ( root ) != submarks[name].end() ) {

                                if ( submarks[name][root] < markv ) {

                                        submarks[name][root] = markv;
                                        replaced = true;
                                }

                        }

                        else
                        {

                                submarks[name][root] = markv;
                                replaced = true;
                        }
                }
            }

        }

        return replaced;
}

Submarks get_submarks(std::string adatbazis)
{
	//Itt kell keresnie a védésekért
	std::vector<std::string> folder_names;
	folder_names.push_back("City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/I");
	folder_names.push_back("City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/II");
	folder_names.push_back("City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/III");
	
	Submarks submarks;

        std::ifstream db ( adatbazis );

        std::string line;
	
	while ( std::getline ( db, line ) ) {

                boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

                auto iter = tokens.begin();
                std::string name = *iter;
                std::string act = *++iter;
                std::string tstamp = *++iter;

                act = act.substr ( 2 );


                for ( const auto & node : folder_names ) {      ///Az I részstringje az II-nek, ezért többször is lefut

                        if ( repl_mark ( submarks, name, act, node, "jeles", 5 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "jó", 4 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "közepes", 3 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "elégséges", 2 ) )
                                ;
                        else if ( repl_mark ( submarks, name, act, node, "elégtelen", 1 ) )
                                ;


                }

        }
        return submarks;
	
}


int main( int argc, char *argv[] )
{
	std::cout << "Tradicionális labor jegy\n";
	
	if (argc < 2)
	{
		std:: cout << "Használat:\nAdd meg az adatbázis fájl nevét\n";
		return -1;
	}
	
	std::string adatbazis;
	adatbazis = argv[1];
	std::cout << adatbazis << std::endl;
	
	Submarks submarks = get_submarks(adatbazis);
	
	/*
	std::cout << "Védések:\n";
	for (auto & user : submarks)
	{
		std::cout << user.first << " " << user.second.size() << std::endl;
		//user.first: név	user.second.size(): védések száma
	}
	std::cout << "\n\n";
	*/
	
	print_marks ( submarks );
	std::cout << std::endl;
	
	std::map <std::string, int> marks = get_marks ( submarks );
	
	/*
	for (auto & user : marks)
		std::cout << user.first << " " << user.second << std::endl;
		//user.first: név	user.second: védések átlaga
	*/
	
	//Védési átlag szerinti rendezés a sort_map Használatával
	std::vector<std::pair<std::string, int>> res = sort_map ( marks );
	std::cout << std::endl;
	for (auto & user : res)
		std::cout << user.first << " " << user.second << std::endl;
	
	return 0;
}
