#include <iostream>
#include <string>

class Datum
{
public:
    Datum(std::string str);
    int dan()const;
    int mjesec()const;
    int godina()const;
    std::string to_string()const;
    //friend bool operator==(Datum const &left, Datum const & right);
    //friend bool operator!=(Datum const &left, Datum const & right);

    ~Datum(){/*std::cout <<"destruktor DATUM" << std::endl;*/}
private:
    int m_dan;
    int m_mjesec;
    int m_godina;
    int prvi_broj(std::string str) const;
};

class Osoba
{
public:
    Osoba(std::string ime, std::string prezime);
    std::string ime()const;
    std::string prezime() const;
    virtual ~Osoba(){std::cout << "destruktor OSOBA" << std::endl;}
    virtual void print(std::ostream& out) const;
    friend bool operator==(Osoba const & left, Osoba const & right);
    //friend bool operator!=(Osoba const & left, Osoba const & right);
private:
    std::string m_ime;
    std::string m_prezime;
protected:
    virtual bool jednak(const Osoba& o)const;
};

class Zaposlenik : public virtual Osoba
{
public:
    Zaposlenik(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja);
    int radnoMjesto()const;
    Datum pocetakZaposlenja() const;
    virtual ~Zaposlenik(){std::cout << "destruktor ZAPOSLENIK" << std::endl;}
    virtual void print(std::ostream& out) const;
private:
    int m_radnoMjesto;
    Datum m_pocetakZaposlenja;
protected:
    virtual bool jednak(const Osoba& o)const;
};

class Student : public virtual Osoba
{
public:
    Student(std::string ime, std::string prezime, int godina);
    int godina()const;
    virtual ~Student(){std::cout << "destruktor STUDENT" << std::endl;}
    virtual void print(std::ostream& out) const;
private:
    int m_godina;
protected:
    virtual bool jednak(const Osoba& o)const;
};


class PrivremeniZaposlenik : public Zaposlenik
{
public:
    PrivremeniZaposlenik(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja, std::string krajZaposlenja);
    Datum krajZaposlenja()const;
    virtual ~PrivremeniZaposlenik(){std::cout << "destruktor PRIVREMENI ZAPOSLENIK" << std::endl;}
    virtual void print(std::ostream& out) const;
private:
    Datum m_krajZaposlenja;
protected:
    virtual bool jednak(const Osoba& o)const;
};

class AngaziraniStudent : public PrivremeniZaposlenik, public Student
{
public:
    AngaziraniStudent(std::string ime, std::string prezime, int radnoMjesto, std::string pocetakZaposlenja, std::string krajZaposlenja, int godine);
    virtual ~AngaziraniStudent(){std::cout << "destruktor ANGAZIRANI STUDENT" << std::endl;}
    virtual void print(std::ostream& out) const;
protected:
    virtual bool jednak(const Osoba& o)const;
};
