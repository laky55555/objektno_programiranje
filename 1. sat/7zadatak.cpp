#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include "math.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

using namespace std;

//u class-i trebalo bi jos napraviti konstruktor, destruktor, te funkcije za ubacivanje, trazenje i izbacivanje elemenata iz skupa

class klasa{
private:
    set<std::string> skup;
    set<std::string>::iterator si;

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

public:
    void ispis_skupa(set<string> & skup)
    {
        for_each(skup.begin(), skup.end(), [] (string s){cout << s << endl;});
    }




    void ucitavanje(string imeDatoteke)
    {
        ifstream is;
        is.open(imeDatoteke.c_str());
        const string a = "Ne moze otvoriti tekstualnu datoteku";
        if(is.is_open())
            throw runtime_error(a);
        char c;
        string tekst;
        while (is.get(c))
            tekst += c;
        separator(tekst, skup);
        is.close();
        ispis_skupa(skup);
    }

    double podudaranje(klasa skup2)
    {
        set<string> presjek;
        set_intersection (skup.begin(), skup.end(), skup2.skup.begin(), skup2.skup.end(), inserter(presjek, presjek.end()));
        ispis_skupa(presjek);
        return  presjek.size() / (sqrt(skup.size()) * sqrt(skup2.skup.size()));

    }





};


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
    klasa text, rijeci;
    text.ucitavanje(in1);
    rijeci.ucitavanje(in2);
    double x = text.podudaranje(rijeci);

    std::cout << "Podudaranje iznosi " << x << std::endl;

    return 0;
}


