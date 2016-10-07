#include "m.h"
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <typeinfo>
#include <assert.h>
#include <stdlib.h>
Datum::Datum(std::string str)
{
    m_dan=prvi_broj(str);
    std::size_t found = str.find(":");
    str=str.substr(found+1);
    m_mjesec=prvi_broj(str);
    found = str.find(":");
    str=str.substr(found+1);
    m_godina=prvi_broj(str);
    std::cout << "konstruktor DATUM"  << std::endl;
}
int Datum::dan()const{return m_dan;}
int Datum::mjesec()const {return m_mjesec;}
int Datum::godina()const {return m_godina;}
std::string Datum::to_string() const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << m_dan << ":" <<
            std::setfill('0') << std::setw(2) << m_mjesec << ":" <<
                std::setfill('0') << std::setw(4) << m_godina;
    std::string str;
    ss >> str;
    return str;
}
int Datum::prvi_broj(std::string str)const
{
    int i;
    std::stringstream ss;
    ss << str;
    ss >> i;
    return i;
}
bool operator==(Datum const & left, Datum const & right)
{
    if(left.dan()==right.dan() && left.mjesec()==right.mjesec() && left.godina()==right.godina())return true;
    return false;
}
bool operator!=(Datum const & left, Datum const & right)
{
    if(left==right) return false;
    return true;
}
std::ostream& operator<<(std::ostream& out, Datum const & d)
{
    std::string str=d.to_string();
    out << str;
    return out;
}
Osoba::Osoba(std::string ime, std::string prezime):m_ime(ime), m_prezime(prezime)
{
    std::cout << "konstruktor OSOBA" << std::endl;
}
std::string Osoba::ime() const
{
    return m_ime;
}

std::string Osoba::prezime() const
{
    return m_prezime;
}
void Osoba::print(std::ostream& out)const
{
    out << ime() << std::endl << prezime() << std::endl;
}
bool Osoba::jednak(const Osoba& o)const
{
    if(ime()==o.ime() && prezime()==o.prezime())return true;
    return false;
}
Zaposlenik::Zaposlenik(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja):Osoba(ime, prezime),
                            m_radnoMjesto(radnoMjesto), m_pocetakZaposlenja(Datum(pocetakZaposlenja))
{
    std::cout << "konstruktor ZAPOSLENIK" << std::endl;
}
int Zaposlenik::radnoMjesto()const
{
    return m_radnoMjesto;
}
Datum Zaposlenik::pocetakZaposlenja() const
{
    return m_pocetakZaposlenja;
}
void Zaposlenik::print(std::ostream& out)const
{
    Osoba::print(out);
    out << radnoMjesto() << std::endl;
    out << pocetakZaposlenja() << std::endl;
}
bool Zaposlenik::jednak(const Osoba& o)const
{
    const Zaposlenik & rd = dynamic_cast<const Zaposlenik &>(o);
    if(Osoba::jednak(o))
    {
        if(rd.radnoMjesto()==radnoMjesto() && rd.pocetakZaposlenja()==pocetakZaposlenja())return true;
        else return false;
    }
    return false;
}

Student::Student(std::string ime, std::string prezime, int godina):Osoba(ime, prezime), m_godina(godina)
{
    std::cout << "konstruktor STUDENT" << std::endl;
}
int Student::godina()const
{
    return m_godina;
}
void Student::print(std::ostream& out)const
{
    Osoba::print(out);
    out << godina() << std::endl;
}
bool Student::jednak(const Osoba& o)const
{
    const Student & rd = dynamic_cast<const Student &>(o);
    if(Osoba::jednak(o))
    {
        if(rd.godina()==godina())return true;
        else return false;
    }
    return false;
}

PrivremeniZaposlenik::PrivremeniZaposlenik(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja, std::string krajZaposlenja):
            Osoba(ime, prezime), Zaposlenik(ime, prezime, radnoMjesto, pocetakZaposlenja), m_krajZaposlenja(Datum(krajZaposlenja))
{
    std::cout << "konstruktor PRIVREMENI ZAPOSLENIK" << std::endl;
}
Datum PrivremeniZaposlenik::krajZaposlenja() const
{
    return m_krajZaposlenja;
}
void PrivremeniZaposlenik::print(std::ostream& out)const
{
    Zaposlenik::print(out);
    out << krajZaposlenja() << std::endl;
}
bool PrivremeniZaposlenik::jednak(const Osoba& o)const
{
    const PrivremeniZaposlenik & rd = dynamic_cast<const PrivremeniZaposlenik &>(o);
    if(Zaposlenik::jednak(o))
    {
        if(rd.krajZaposlenja()==krajZaposlenja())return true;
        else return false;
    }
    return false;
}

AngaziraniStudent::AngaziraniStudent(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja, std::string krajZaposlenja, int godina):
            Osoba(ime, prezime),
            PrivremeniZaposlenik(ime, prezime, radnoMjesto, pocetakZaposlenja, krajZaposlenja),
            Student(ime, prezime, godina)
{
    std::cout << "konstruktor ANGAZIRANI STUDENT" << std::endl;
}
void AngaziraniStudent::print(std::ostream& out)const
{
    PrivremeniZaposlenik::print(out);
    out << godina() << std::endl;
}
bool AngaziraniStudent::jednak(const Osoba& o)const
{
    if(PrivremeniZaposlenik::jednak(o) && Student::jednak(o))return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, Osoba const& o)
{
    o.print(out);
    return out;
}
bool operator==(Osoba const & left, Osoba const & right)
{
    if(typeid(left) != typeid(right)) return false;
    if(left.jednak(right)) return true;
    return false;
}
bool operator!=(Osoba const & left, Osoba const & right)
{
    if(left==right)return false;
    return true;
}
int main()
{
    AngaziraniStudent  as1("Ivo", "Josic", 17, "12:02:2015", "12:03:2015", 2);

    std::cout << "----------------------------------------\n";
    std::cout << as1 << std::endl;
    std::cout << "----------------------------------------\n";

    AngaziraniStudent as2(as1);
    assert(as1 == as2);

    PrivremeniZaposlenik pz1 = as2;
    std::cout << "----------------------------------------\n";
    std::cout << pz1 << std::endl;
    std::cout << "----------------------------------------\n";
    assert(pz1 != as2);

    AngaziraniStudent * pas3 = new  AngaziraniStudent("Nino", "Gusic",  16, "12:02:2015", "12:03:2015",  2);
    Student * ps = pas3;
    std::cout << ps->prezime() << std::endl;
    std::cout << "----------------------------------------\n";
    std::cout << *pas3 << std::endl;
    std::cout << "----------------------------------------\n";

    assert(as2 != *pas3);

    std::cout << "------------------\n";
    delete pas3;
    return EXIT_SUCCESS;
}
