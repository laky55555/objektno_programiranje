#ifndef __VECT_REALLOC_H_IS_INCLUDDED__
#define __VECT_REALLOC_H_IS_INCLUDDED__

#include <iostream>
#include <string>

// Klasa Vect implemetira vektor dinamički alociranih double-ova kojima je pridružen jedan string
// (ime varijable). Klasa vrši realokaciju kada više nema dovoljno mjesta za novi element.
// Implementira metodu push_back. Implementirana je potpuna kontrola kopiranja te neke uobičajene
// metode.
class Vect
{
    public:
        // konstruktor i delegirajuće verzije
        Vect(size_t n, double v, std::string const & ime); // Ctor
        Vect(size_t n, double v) : Vect(n, v, "") {}       // Ctor
        explicit Vect(size_t n) : Vect(n, 0.0, "") {}      // Ctor
        explicit Vect(std::string const & ime) : Vect(0, 0.0, ime) {} // Ctor

        // Kontrola kopiranja
        Vect(const Vect& v);                            // CCtor
        Vect(Vect && v) noexcept;                       // MCtor

        Vect& operator=(const Vect& v);                 // OP
        Vect& operator=(Vect && v) noexcept;            // MOP

        ~Vect(){std::cout << "Dtor\n";  free(); }

        // dohvat elemenata
        double const& operator[](size_t i) const { return mdata[i]; }
        double&       operator[](size_t i)       { return mdata[i]; }

        // push_back kao u std::vector. Eventualno izaziva realokaciju čitavog vektora
        void push_back(double);

        // info rutine
        size_t  size()     const {return mfirst_free - mdata; }
        size_t  capacity() const {return mend - mdata; }

        // utility-rutine
        double norm2() const;
        Vect& scale(double alpha);
        void print(std::ostream& out) const;

        // Ime vektora je javna varijabla
        std::string  ime;   // ime varijable
    private:
        double *mdata;       // pokazivač na prvi element
        double *mfirst_free; // pokazivač na prvo slobodno mjesto
        double *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)

        // Vraća true ako imamo prostora za još jedan element, inaće vraća false.
        bool has_space() const {  return ( size() == capacity() ) ?  false : true; }

        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();
        // realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
        // vektor prazan dodaj jedan element.
        void reallocate();

        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
        // statičkim. Ne zaboraviti definirati ga u izvornoj datoteci.
        static std::allocator<double> alloc;

};
#endif
