#include <iostream>
#include <string>
#include <set>
#include <fstream>

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
    is.open(imeDatoteke.c_str());
    char c;
    string tekst;
    while (is.get(c))
        tekst += c;
    separator(tekst, skup);
    is.close();
}


int main (void)
{
    set<string> skup;
    string ime="mojaDatoteka.txt";
    ucitavanje(ime, skup);
    set<string>::iterator si;
    for(si = skup.begin(); si != skup.end(); si++)
        cout << *si <<endl;
    cout << skup.size() <<endl;



    return 0;
}
