#include "poruka.h"
#include <set>
#include <string>
#include <utility>
#include <iostream>

Kategorija::Kategorija(std::string const & opis):mopis(opis) { /*std::cout << "konstruktor kategorija" << std::endl;*/}

void Kategorija::dodaj_poruku(Poruka * p)
{
    mporuke.insert(p);
}

void Kategorija::ukloni_poruku(Poruka * p)
{
    mporuke.erase(p);
}

Kategorija::~Kategorija()
{
    std::cout << "Destruktor kategorije " << mporuke.size() << "  " << mopis << std::endl;
    std::set<Poruka*>::iterator it;
    for(it=mporuke.begin();it!=mporuke.end();it++)
        (*it)->ukloni(*this);
    mporuke.clear();
}


Poruka::Poruka(std::string const & sadrzaj):msadrzaj(sadrzaj){/*std::cout << "konstruktor poruka" << std::endl;*/}

void Poruka::dodaj(Kategorija& k)
{
    mkategorije.insert(&k); //dodamo poruci novu kategoriju
    k.dodaj_poruku(this); // dodamo poruku u tu kategoriju
}
void Poruka::ukloni(Kategorija& k)
{
    mkategorije.erase(&k);   //izbacimo kategoriju
    k.ukloni_poruku(this);   //izbacimo poruku iz te kategorije
}
std::string Poruka::kategorije() const
{
    std::string str;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin();it!=mkategorije.end();it++)
        str+=(*it)->opis()+" ";
    return str;
}
Poruka::~Poruka()
{
    //std::cout << "destruktor poruka" << std::endl;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin();it!=mkategorije.end();it++)
        (*it)->ukloni_poruku(this);
    mkategorije.clear();
}

Poruka::Poruka(Poruka const & p):msadrzaj(p.sadrzaj()), mkategorije(p.mkategorije)
{
    //std::cout << "copy const" << std::endl;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin();it!=mkategorije.end(); it++)
    {
        //ubacimo ovu poruku u sve kategorije
        (*it)->dodaj_poruku(this);
    }
}
Poruka& Poruka::operator=(Poruka const& p)
{
    //std::cout << "copy op" << std::endl;
    if(this!=&p)
    {
        //moramo izbaciti this iz svih kategorija u kojima je trenutno
        std::set<Kategorija*>::iterator it;
        for(it=mkategorije.begin();it!=mkategorije.end(); it++)
        {
            (*it)->ukloni_poruku(this);
        }
        mkategorije.clear();
        msadrzaj=p.sadrzaj();
        mkategorije=p.mkategorije;
        for(it=mkategorije.begin();it!=mkategorije.end(); it++)
        {
            (*it)->dodaj_poruku(this);    //moramo novu poruku dodati u sve kategorije
        }
    }
    return *this;
}
Poruka::Poruka(Poruka && p):msadrzaj(std::move(p.sadrzaj())), mkategorije(std::move(p.mkategorije))
{
    //std::cout << "copy movy" <<std::endl;
    //std::cout << "velicina u p.kategorije sada je " << p.mkategorije.size() << std::endl;
    std::set<Kategorija*>::iterator it;
    for(it=mkategorije.begin();it!=mkategorije.end(); it++)
    {
        (*it)->ukloni_poruku(&p);
        (*it)->dodaj_poruku(this);
    }

}
Poruka& Poruka::operator=(Poruka&& p)
{
    //std::cout << "mov op" << std::endl;
    if(this!=&p)
    {
        //ocistimo this
        std::set<Kategorija*>::iterator it;
        for(it=mkategorije.begin();it!=mkategorije.end();it++)
        {
            (*it)->ukloni_poruku(this);
        }
        mkategorije.clear();
        mkategorije=std::move(p.mkategorije);
        msadrzaj=std::move(p.sadrzaj());
        for(it=mkategorije.begin();it!=mkategorije.end();it++)
        {
            (*it)->ukloni_poruku(&p);
            (*it)->dodaj_poruku(this);
        }
    }
    return *this;
}
