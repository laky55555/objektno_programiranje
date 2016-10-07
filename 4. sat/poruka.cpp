#include <iostream>

#include "poruka.h"
#include <string>
#include <set>

Kategorija::Kategorija(std::string const & opis)
{
    //std::cout << "Konstruktor kategorije" << std::endl;
    mopis = opis;
}

Kategorija::Kategorija(Kategorija const& kate)
{
    //std::cout << "Copy konstruktor kategorije" << std::endl;
    mopis = kate.mopis;
    mporuke = kate.mporuke;

}

void Kategorija::dodaj_poruku(Poruka *por)
{
    mporuke.insert(por);
}

void Kategorija::ukloni_poruku(Poruka *por)
{
    mporuke.erase(por);
}

Kategorija::~Kategorija()
{
    //std::cout << "Destruktor kategorije " << mporuke.size() << "  " << mopis << std::endl;
    std::set<Poruka*>::iterator it;
    for(it=mporuke.begin();it!=mporuke.end();it++)
        (*it)->ukloni(*this);
}


Poruka::Poruka(std::string const & sadrzaj): msadrzaj(sadrzaj)
{
    //std::cout << "Konstruktor poruke" << std::endl;
}

Poruka::Poruka(Poruka const & por)
{
    std::set<Kategorija*>::iterator it;
    //std::cout << "Copy konstruktor poruke" << std::endl;
    msadrzaj = por.sadrzaj();
    mkategorije = por.mkategorije;
    for(it=mkategorije.begin();it!=mkategorije.end(); it++)
        (*it)->dodaj_poruku(this);
}

Poruka::Poruka(Poruka && por)
{
    std::set<Kategorija*>::iterator it;
    //std::cout << "Konstruktor poruke premijestanjem" << std::endl;
    msadrzaj = std::move(por.sadrzaj());
    mkategorije = std::move(por.mkategorije);
    for(it=mkategorije.begin();it!=mkategorije.end(); it++)
    {
        (*it)->dodaj_poruku(this);
        (*it)->ukloni_poruku(&por);
    }

}

Poruka& Poruka:: operator=(Poruka const& por)
{
    std::set<Kategorija*>::iterator it;
    //std::cout << "Operator pridruzivanja kopiranjem poruke" << std::endl;
    if (this != &por)
    {
        for(it=mkategorije.begin();it!=mkategorije.end(); it++)
            (*it)->ukloni_poruku(this);
        mkategorije.clear();
        mkategorije = por.mkategorije;
        msadrzaj = por.sadrzaj();
        for(it=mkategorije.begin();it!=mkategorije.end(); it++)
            (*it)->dodaj_poruku(this);
    }
    return *this;
}

Poruka& Poruka::operator=(Poruka&& por)
{
    std::set<Kategorija*>::iterator it;
    //std::cout << "Operator pridruzivanja premijestanjem poruke" << std::endl;
    if(this != &por)
    {
        mkategorije.clear();
        msadrzaj = std::move(por.sadrzaj());
        mkategorije = std::move(por.mkategorije);
        for(it=mkategorije.begin();it!=mkategorije.end(); it++)
        {
            (*it)->dodaj_poruku(this);
            (*it)->ukloni_poruku(&por);
        }
    }
    return *this;
}

Poruka::~Poruka()
{
    //std::cout << "Destruktor poruke" << std::endl;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin();it!=mkategorije.end();it++)
        (*it)->ukloni_poruku(this);
}

void Poruka::dodaj(Kategorija& kate)
{
    kate.dodaj_poruku(this);
    mkategorije.insert(&kate);
}


void Poruka::ukloni(Kategorija& kate)
{
    kate.ukloni_poruku(this);
    mkategorije.erase(&kate);
}

std::string Poruka::kategorije() const
{
    std::string sve_kategorije;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin(); it!=mkategorije.end(); it++)
        sve_kategorije = sve_kategorije + ((*it)->opis()) + " ";
    return sve_kategorije;
}





