#ifndef __AUX_H__
#define __AUX_H__

#include <iostream>

using std::cout;
using std::endl;

void TEST(bool express);

// Pomoćne klase za testiranje implementacije SmartPtr
// klase.

struct A {
    std::string name="_";

    A() {}
    A(std::string const & _ss) : name(_ss) {}
    A(std::string && _ss) : name(std::move(_ss)) {name+="_"; }
    virtual char f() const { return 'A'; }
    virtual ~A() {}
};

//std::ostream& operator<<(std::ostream & out, A const & a){ out << "A(" << a.name <<")"; return out;}

struct B : A{
    double  z{0.0};

    using A::A;
    B() : A() {} // Kako imamo druge konstruktore taj ne sintetizira.
    B(std::string const & _ss,  double _z) : A(_ss), z(_z) {}
    B(std::string && _ss,  double _z) : A(std::move(_ss)), z(_z) {}

    virtual char f() const { return 'B'; }
};

//std::ostream& operator<<(std::ostream & out, B const & a){ out << "B(" << a.name << "," << a.z <<")"; return out;}


void TEST(bool express){
  if(express) cout << "ok.\n";
  else        cout << "error.\n";
}

#endif
