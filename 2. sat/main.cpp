#include "Tocka.h"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>



double najmanji_put=-1;
std::vector<tocka> najkraci;


double prolaz(std::vector<tocka> vek)
{
    double zbroj = 0;
    for(int i=0;i<vek.size()-1;i++)
        zbroj+=vek[i].udaljenost(vek[i+1]);
    return zbroj;
}

double permutacije(std::vector<tocka> vek)
{
    double minimalno=-1, zbroj;
    do
    {
        zbroj=0;
        zbroj = prolaz(vek);
        if(minimalno==-1)
            minimalno=zbroj;
        else if(minimalno>zbroj)
            minimalno=zbroj;
    }while(std::next_permutation(vek.begin(), vek.end()));

    return minimalno;
}



void izjednacavanje_vektora(std::vector<tocka> prazni, std::vector<tocka> puni)
{
    najkraci.clear();
    std::vector<tocka>::iterator vi;
    for (vi=puni.begin(); vi!=puni.end(); vi++)
        najkraci.push_back(*vi);
}

void rekurzija(tocka a, std::set<tocka> neposjeceni, double prijedeni_put, std::vector<tocka> posjecene)
{
    std::set<tocka>::iterator vi;
    std::vector<tocka>::iterator vi2;
    posjecene.push_back(a);
    neposjeceni.erase(a);
    if(neposjeceni.size() == 0)
    {
        if (najmanji_put == -1)
        {
            najmanji_put = prijedeni_put;
            izjednacavanje_vektora(najkraci ,posjecene);
        }
        else if(prijedeni_put < najmanji_put )
        {
            najmanji_put = prijedeni_put;
            izjednacavanje_vektora(najkraci, posjecene);
        }
        return;
    }

    for (vi=neposjeceni.begin(); vi!=neposjeceni.end(); vi++)
    {
        rekurzija(*vi, neposjeceni, prijedeni_put+a.udaljenost(*vi), posjecene);
    }
}



int main (void)
{
    std::vector<tocka> lista;
    std::vector<tocka> put;
    std::vector<tocka>::iterator vi;
    std::set<tocka> vrhovi;

    int n;
    std::cout << "Upisite prirodni broj manji od 15." << std::endl;
    std::cin >> n;
    for(int i=0; i<n; i++)
    {
        tocka a;
        a.upis_tocke();
        lista.push_back(a);
        vrhovi.insert(a);
    }

    std::cout << "Popis svih tocaka: " << std::endl;
    for (vi=lista.begin(); vi!=lista.end(); vi++)
    {
        vi->ispis_tocke();
    }


    for (vi=lista.begin(); vi!=lista.end(); vi++)
    {
        rekurzija(*vi, vrhovi, 0, put);
    }
    std::cout << "Najmanji put pomocu rekurzije je: " << najmanji_put << std::endl;
    std::cout << "Najmanji put bez rekurzije je: " << permutacije(lista) << std::endl;

    std::cout << "Najkraci put kroz sve tocke prolazi iducim tockama: " << std::endl;
    for (vi=najkraci.begin(); vi!=najkraci.end(); vi++)
    {
        vi->ispis_tocke();

    }



    return 0;
}

