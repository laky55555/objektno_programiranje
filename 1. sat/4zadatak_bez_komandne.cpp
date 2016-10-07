#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include "math.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

using namespace std;

void ispis_skupa(set<string> & skup)
{
    for_each(skup.begin(), skup.end(), [] (string s){cout << s << endl;});
}


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

double podudaranje(set<string> & skup1, set<string> & skup2)
{
    set<string> presjek;
    set_intersection (skup1.begin(), skup1.end(), skup2.begin(), skup2.end(), inserter(presjek, presjek.end()));
    ispis_skupa(presjek);
    return  presjek.size() / (sqrt(skup1.size()) * sqrt(skup2.size()));

}

int main()
{
    std::set<std::string> text, rijeci;
    string in1="mojaDatotekaff.txt", in2="trazeneRijeci.txt";
    ucitavanje(in1, text);
    ucitavanje(in2, rijeci);
    double x = podudaranje(text, rijeci);

    std::cout << "Podudaranje iznosi " << x << std::endl;

    return 0;
}

