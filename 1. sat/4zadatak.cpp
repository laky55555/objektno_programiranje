#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include "math.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

using namespace std;


void separator(string const & text, set<string> & skup)
{
    int i;
    for(i=0; i<text.length(); i++)
    {
        string rijec;
        while(isalnum(text[i]))
        {
            rijec += text[i];
            i++;
        }
        if (rijec.length())
            skup.insert(rijec);
        rijec.clear();
    }
}

void ucitavanje(string imeDatoteke, set<string> & skup)
{
    ifstream is;
    if(!is)
        runtime_error("Ne moze otvoriti tekstualnu datoteku");
    is.open(imeDatoteke.c_str());
    char c;
    string tekst;
    while (is.get(c))
        tekst += c;
    separator(tekst, skup);
    is.close();
}

double podudaranje(set<string> & skup1, set<string> & skup2)
{
    set<string> presjek;
    set_intersection (skup1.begin(), skup1.end(), skup2.begin(), skup2.end(), inserter(presjek, presjek.end()));
    return  presjek.size() / (sqrt(skup1.size()) * sqrt(skup2.size()));

}

int main(int argc, char** argv)
{
    if(argc < 2){
        std::cerr << " Ocekujem dva argumenta\n" << argv[0] << " ime1 ime2\n"
                  << " ime1 = ulazna datoteka s tekstom\n ime2 = datoteka s trazenim rijecima."
                  << std::endl;
        std::exit(1);
    }
    std::string in1(argv[1]);
    std::string in2(argv[2]);

    std::set<std::string> text, rijeci;
    ucitavanje(in1, text);
    ucitavanje(in2, rijeci);
    double x = podudaranje(text, rijeci);

    std::cout << "Podudaranje iznosi " << x << std::endl;

    return 0;
}
