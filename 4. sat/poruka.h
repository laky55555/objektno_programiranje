#ifndef PORUKA_H_INCLUDED
#define PORUKA_H_INCLUDED

#include <string>
#include <set>

class Poruka;

class Kategorija{
public:
    // pri konstrukciji je obavezan opis kategorije
    explicit Kategorija(std::string const & opis);
    // kontrola kopiranja
    Kategorija(Kategorija const& kate);
    Kategorija(Kategorija && kate) = delete;
    Kategorija& operator=(Kategorija const & kate) = delete;
    Kategorija& operator=(Kategorija && kate) = delete;
    ~Kategorija();

    // dodaj poruku u kategoriju
    void dodaj_poruku(Poruka *por);
    // ukloni poruku iz kategorije
    void ukloni_poruku(Poruka *por);
    // vrati opis kategorije
    std::string opis() const { return mopis; }
    int broj_poruka() const { return mporuke.size(); }
private:
    // pokazivaèi na poruke u kategoriji
    std::set<Poruka*> mporuke;
    // opis kategorije
    std::string mopis;
};

class Poruka{
    friend class Kategorija;
  public:
    // pri konstrukciji poruke obavezano je dati sadržaj poruke
      explicit Poruka(std::string const & sadrzaj = "");
      // Kontrola kopiranja
      Poruka(Poruka const & por);
      Poruka(Poruka && por);
      Poruka& operator=(Poruka const& por);
      Poruka& operator=(Poruka&& por);
      ~Poruka();
      // dodaj poruku u kategoriju
      void dodaj(Kategorija& kate);
      // ukloni poruku iz kategorije
      void ukloni(Kategorija& kate);
      // vrati poruku
      std::string sadrzaj() const { return msadrzaj; }
      // vrati sve kategorije u kojima je poruka (odvojene bjelinom, kao jedan string)
      std::string kategorije() const;
  private:
    std::string msadrzaj;
    std::set<Kategorija*> mkategorije;
};

#endif // PORUKA_H_INCLUDED
