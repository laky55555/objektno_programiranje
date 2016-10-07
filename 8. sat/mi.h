#include <iostream>
#include <string>


class Datum{
public:
    Datum(std::string a);
    int dan() {return m_dan;}
    int mjesec() {return m_mjesec;}
    int godina() {return m_godina;}
    std::string u_string();
private:
    int m_dan, m_mjesec, m_godina;
};




class Osoba{
public:
    Osoba(std::string x, std::string y) : m_ime(x), m_prezime(y) {}
    std::string ime() {return m_ime;}
    std::string prezime() {return m_prezime;}
private:
    std::string m_ime, m_prezime;

};


class Zaposlenik : public virtual Osoba{
public:
    Zaposlenik(std::string x, std::string y, int a, int b) : Osoba(x, y), m_radnoMjesto(a), m_pocetakZaposlenja(b) {}
    int radnoMjesto() {return m_radnoMjesto;}
    int pocetakZaposlenja() {return m_pocetakZaposlenja;}
private:
    int m_radnoMjesto, m_pocetakZaposlenja;
};


class PrivremeniZaposlenik : public Zaposlenik{
public:
    PrivremeniZaposlenik(std::string x, std::string y, int a, int b, Datum c) : Osoba(x, y), Zaposlenik(x, y, a, b), m_krajZaposlenja(c) {}
    Datum krajZaposlenja() {return m_krajZaposlenja;}
private:
    Datum m_krajZaposlenja;
};

class Student : public virtual Osoba{
public:
    Student(std::string x, std::string y, int a) : Osoba(x, y), m_godina(a) {}
    int godina() {return m_godina;}
private:
    int m_godina;
};

class AngaziraniStudent: public PrivremeniZaposlenik, public Student
{
public:
    AngaziraniStudent(std::string x, std::string y, int a, int b, Datum c, int d) : Osoba(x, y), Zaposlenik(x, y, a, b), Student(x, y, d) {}
};












