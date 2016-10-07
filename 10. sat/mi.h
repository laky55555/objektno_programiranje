#include <iostream>
#include <string>
#include <typeinfo>
#include <stdlib.h>
#include <assert.h>
#include <sstream>

class Datum{
public:
    Datum(std::string a);
    int dan() const {return m_dan;}
    int mjesec() const{return m_mjesec;}
    int godina() const {return m_godina;}
    std::string u_string() const;
    ~Datum() {std::cout << "Destruktor datuma\n";}
private:
    int m_dan, m_mjesec, m_godina;
};

class Osoba{
public:
    Osoba(std::string x, std::string y) : m_ime(x), m_prezime(y) {std::cout << "Konstruktor osobe\n";}
    std::string ime() const {return m_ime;}
    std::string prezime() const {return m_prezime;}
    virtual void ispis(std::ostream& out) const {out << ime() << std::endl << prezime() << std::endl;}
    virtual ~Osoba() {std::cout << "Destruktor osobe\n";}
protected:
    virtual bool jednak(Osoba const & o) const;
    friend bool operator== (Osoba const & left, Osoba const & right);
private:
    std::string m_ime, m_prezime;
};

bool operator== (const Datum& a, const Datum& b);
bool operator!= (const Datum& a, const Datum& b);


bool operator==(Osoba const & left, Osoba const & right);
bool operator!=(Osoba const & left, Osoba const & right);

std::ostream& operator<<(std::ostream& out, const Datum& d);
std::ostream& operator<<(std::ostream& out, Osoba const & o);


class Zaposlenik : public virtual Osoba{
public:
    Zaposlenik(std::string x, std::string y, int a, std::string b) : Osoba(x, y), m_radnoMjesto(a), m_pocetakZaposlenja(b) {std::cout << "Konstruktor zaposlenika\n";}
    int radnoMjesto() const {return m_radnoMjesto;}
    Datum pocetakZaposlenja() const {return m_pocetakZaposlenja;}
    virtual void ispis(std::ostream& out) const {Osoba::ispis(out); out << radnoMjesto() << std::endl << pocetakZaposlenja() << std::endl;}
    virtual ~Zaposlenik() {std::cout << "Destruktor zaposlenika\n";}
protected:
    virtual bool jednak(Osoba const & o) const;
private:
    int m_radnoMjesto;
    Datum m_pocetakZaposlenja;
};


class PrivremeniZaposlenik : public Zaposlenik{
public:
    PrivremeniZaposlenik(std::string x, std::string y, int a, std::string b, std::string c) : Osoba(x, y), Zaposlenik(x, y, a, b), m_krajZaposlenja(c) {std::cout << "Konstruktor privremenog zaposlenika\n";}
    Datum krajZaposlenja() const {return m_krajZaposlenja;}
    virtual void ispis(std::ostream& out) const {Zaposlenik::ispis(out); out << krajZaposlenja() << std::endl;}
    virtual ~PrivremeniZaposlenik() {std::cout << "Destruktor privremenog zaposlenika\n";}
protected:
    virtual bool jednak(Osoba const & o) const;
private:
    Datum m_krajZaposlenja;
};

class Student : public virtual Osoba{
public:
    Student(std::string x, std::string y, int a) : Osoba(x, y), m_godina(a) {std::cout << "Konstruktor studenta\n";}
    int godina() const {return m_godina;}
    virtual void ispis(std::ostream& out) const {Osoba::ispis(out); out << godina() << std::endl;}
    virtual ~Student() {std::cout << "Destruktor studenta\n";}
protected:
    virtual bool jednak(Osoba const & o) const;
private:
    int m_godina;
};

class AngaziraniStudent: public PrivremeniZaposlenik, public Student{
public:
    AngaziraniStudent(std::string x, std::string y, int a, std::string b, std::string c, int d) : Osoba(x, y), PrivremeniZaposlenik(x, y, a, b, c), Student(x, y, d) {std::cout << "Konstruktor angaziranog studenta\n";}
    virtual void ispis(std::ostream& out) const {PrivremeniZaposlenik::ispis(out); out << godina() << std::endl;}
    virtual ~AngaziraniStudent() {std::cout << "Destruktor angaziranog studenta\n";}
protected:
    virtual bool jednak(Osoba const & o) const;

};



