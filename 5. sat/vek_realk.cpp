#include "vek_realk.h"
#include <string>
#include <cmath>

std::allocator<double> Vect::alloc;

// Konstruktor
// Tek ako je zadano n>0 alociramo memoriju
Vect::Vect(size_t n, double v, std::string const & vec_name) : ime(vec_name), mdata(nullptr),
                                                                mfirst_free(nullptr), mend(nullptr)
{
            std::cerr << "Ctor"<<std::endl;
            if(n > 0) {
                 mdata = alloc.allocate(n);
                 for(size_t i=0; i<n; ++i) alloc.construct(mdata+i, v);
                 mfirst_free = mend = mdata+n;
            }
}

void  Vect::print(std::ostream& out) const
{
    out<< ime << ": (" << size() << "," << capacity()<<") ";
    for(size_t i=0; i < size(); ++i) {
        out << mdata[i];
        if(i+1 < size()) out << ",";
    }
}

void Vect::push_back(double x){
    if( !has_space() )
        reallocate();
    alloc.construct(mfirst_free++, x);
}

void Vect::reallocate()
{
    double *nova_mdata;
    size_t nova_velicina = 2*capacity();
    if (nova_velicina == 0)
        nova_velicina = 1;
    nova_mdata = alloc.allocate(nova_velicina);
    for(size_t i=0; i<capacity(); ++i) alloc.construct(nova_mdata+i, *mdata+i);     //???????????
    alloc.deallocate(mdata, capacity());
    mdata = nova_mdata;
    mfirst_free = mdata + (nova_velicina/2);
    mend = mdata + nova_velicina;
}

void Vect::free()
{
    for(unsigned int i=0; i<size(); ++i)
        alloc.destroy(mdata+i);
    alloc.deallocate(mdata, capacity());
    mdata = mfirst_free = mend = nullptr;
}

Vect::Vect(const Vect& v)
{
    ime = v.ime;
    mdata = nullptr; mfirst_free = nullptr; mend=nullptr;
    std::cerr << "C-Ctor"<<std::endl;
    if(v.capacity() != 0)
    {
        mdata = alloc.allocate(v.capacity());
        for(size_t i=0; i<v.size(); ++i)
            alloc.construct(mdata+i, v[i]);
        mfirst_free = mdata + v.size();
        mend = mdata + v.capacity();
    }

}

Vect::Vect(Vect && v) noexcept
{
    std::cerr << "M-Ctor"<<std::endl;
    ime = std::move(v.ime);
    v.ime.clear();
    mdata = &v[0];
    mfirst_free = mdata + v.size();
    mend = mdata + v.capacity();
    v.mdata = v.mfirst_free = v.mend = nullptr;
}

Vect& Vect::operator=(const Vect& v)
{
    std::cerr << "OP"<<std::endl;
    if (this != &v)
    {
        ime = v.ime;
        if(this->capacity() < v.capacity())         //ako nemamo dovoljno mjesta u vektoru alociramo novo mjesto
        {
            free();
            mdata = alloc.allocate(v.capacity());
            for(size_t i=0; i<v.size(); ++i)
                alloc.construct(mdata+i, v[i]);
            mend = mdata + v.capacity();
        }
        else                                        //ako imamo dovoljno mjesta, ne moramo alocirati novi vektor vec samo izmjeniti postojeci
            for(size_t i=0; i<v.size(); ++i)
                *(mdata+i) = v[i];
        mfirst_free = mdata + v.size();
    }
    return *this;
}


Vect& Vect::operator=(Vect && v) noexcept
{
    std::cerr << "M-OP"<<std::endl;
    if (this != &v)
    {
        free();
        ime = std::move(v.ime);
        v.ime.clear();
        mdata = &v[0];
        mfirst_free = mdata + v.size();
        mend = mdata + v.capacity();
        v.mdata = v.mfirst_free = v.mend = nullptr;
    }
    return *this;
}

double Vect::norm2() const
{
    double norma = 0.0;
    for(size_t i=0; i<size(); ++i)
        norma += *(mdata+i) * *(mdata+i);
    norma = sqrt(norma);
    return norma;
}

Vect& Vect::scale(double alpha)
{
    for(size_t i=0; i<size(); ++i)
        *(mdata+i) = *(mdata+i)*alpha;
    return *this;
}






