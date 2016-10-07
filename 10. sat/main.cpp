#include "mi.h"



Datum::Datum(const std::string a)
{
    std::cout << "Konstruktor datuma\n";
    m_dan = (a[0]-'0')*10+(a[1]-'0');
    m_mjesec = (a[3]-'0')*10+(a[4]-'0');
    m_godina = (a[6]-'0')*1000+(a[7]-'0')*100+(a[8]-'0')*10+(a[9]-'0');
}

std::string Datum::u_string() const
{
    std::string zavrsni, dan, mjesec, godina;
    std::ostringstream a, b, c;
    a << m_dan;
    dan = a.str();
    b << m_mjesec;
    mjesec = b.str();
    c << m_godina;
    godina = c.str();
    if(m_dan<10)
        zavrsni = "0" + dan + ":";
    else
        zavrsni = dan + ":";
    if(m_mjesec<10)
        zavrsni += "0" + mjesec + ":";
    else
        zavrsni += mjesec + ":";
    if(m_godina<10)
        zavrsni += "000" + godina;
    else if(m_godina<100)
        zavrsni += "00" + godina;
    else if(m_godina<1000)
        zavrsni += "0" + godina;
    else
        zavrsni += godina;
    return zavrsni;

}


std::ostream& operator<<(std::ostream& out, const Datum& d)
{
    std::string dan = d.u_string();
    out << dan;
    return out;
}

std::ostream& operator<<(std::ostream& out, Osoba const & o)
{
    o.ispis(out);
    return out;
}

bool operator== (const Datum& a, const Datum& b)
{
    if(a.godina() == b.godina() && a.mjesec() == b.mjesec() && a.dan() == b.dan() )
        return true;
    else
        return false;
}

bool operator== (Osoba const & left, Osoba const & right)
{
    if( typeid(left) == typeid(right) && left.jednak(right) )
        return true;
    else
        return false;
}

bool operator!= (const Datum& a, const Datum& b)
{
    if(a == b)
        return false;
    else
        return true;
}

bool operator!=(Osoba const & left, Osoba const & right)
{
    if(left == right)
        return false;
    else
        return true;
}

bool Osoba::jednak(Osoba const &o) const
{
    if (m_ime == o.ime() && m_prezime == o.prezime())
        return true;
    else
        return false;
}

bool Zaposlenik::jednak(Osoba const &o) const
{
    const Zaposlenik & rd = dynamic_cast<const Zaposlenik &>(o);
    // Neka prvo bazna klasa obavi svoj posao
    if(Osoba::jednak(o))
    {
        if(m_radnoMjesto == rd.radnoMjesto() && m_pocetakZaposlenja == rd.pocetakZaposlenja() )
            return true;
        else
            return false;
    }
    else
        return false; // Bazni dijelovi nisu jednaki
}

bool PrivremeniZaposlenik::jednak(Osoba const &o) const
{
    const PrivremeniZaposlenik & rd = dynamic_cast<const PrivremeniZaposlenik &>(o);
    // Neka prvo bazna klasa obavi svoj posao
    if(Zaposlenik::jednak(o))
    {
        if(m_krajZaposlenja == rd.krajZaposlenja() )
            return true;
        else
            return false;
    }
    else
        return false; // Bazni dijelovi nisu jednaki
}

bool Student::jednak(Osoba const &o) const
{
    const Student & rd = dynamic_cast<const Student &>(o);
    // Neka prvo bazna klasa obavi svoj posao
    if(Osoba::jednak(o))
    {
        if(m_godina == rd.godina() )
            return true;
        else
            return false;
    }
    else
        return false; // Bazni dijelovi nisu jednaki
}

bool AngaziraniStudent::jednak(Osoba const &o) const
{
    if(Student::jednak(o) && PrivremeniZaposlenik::jednak(o))
        return true;
    else
        return false;
}


int main(void)
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
