#include <iostream>
#include <ctime>
#include <chrono>

#include "operations.h"

using std::cout;
using std::endl;

void test(bool t);
void test(bool t)
{
    if(t) cout << "o.k.\n";
    else  cout << "error.\n";
}

int main()
{
    const size_t max = 3;

    Vector<max>  x, y(2.0), z;
    x[0]=1.0; x[1]= 1.5; x[2]=1;

    z = x + y;
    test(z[2] == x[2]+y[2]);
    z = 2.0*x + y;
    test(z[1] == 2*x[1]+y[1]);
    z = x*2.0 + y;
    test(z[0] == 2*x[0]+y[0]);
    z = 4.0*(x*2.0 + y);
    test(z[1] == 8*x[1]+4*y[1]);
    z = 1.0 + (1.2*x + y*2.0)*4.0 - x + 2.0;
    test(z[2] == 3+4*(1.2*x[2]+2*y[2]) -x[2]);
    z[1] = 2.0;
    z = z*z;
    test(z[1]==4.0);

    cout << " x+ y      = " << x+y << endl;
    cout << " 2*x+ y    = " << 2.0*x+y << endl;
    cout << " x*2+y     = " << x*2.0 + y << endl;
    cout << " 4*(x*2+y) = " << 4.0*(x*2.0 + y) << endl;
    cout << " 1 + (1.2 * x + y * 2.0)*4.0 - x + 2 = "
         << 1.0 + (1.2*x + y*2.0)*4.0 - x + 2.0 << endl;



    const size_t dim = 10000;
    double cc = 3.0;
    Vector<dim> A1(1.0);
    Vector<dim> A2(2.0);
    Vector<dim> A3(0.0);

    auto start = std::chrono::system_clock::now();
    for(int c=0; c<1000; ++c){
        double coef = 1.0;
        for(unsigned int i=0; i < dim; ++i)
            A3[i] = 2.0*A1[i] + coef*(A2[i]-A1[i]);
        coef += 0.01;
    }
    auto end = std::chrono::system_clock::now();
    auto duration =std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now() - start);

    cout<< "C time for " << dim << " additions = "<<  duration.count() <<" ms.\n";
    cout << A3[5678] << endl; // Da sprijeèi potpunu eliminaciju koda s opcijom -O2

    start = std::chrono::system_clock::now();
    for(int c=0; c<1000; ++c){
        double coef = 1.0;
        A3 = 2.0*A1 + coef*(A2-A1);
        coef += 0.01;
    }
    end = std::chrono::system_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now() - start);

    cout<< "C++ time for " << dim << " additions = "
         <<  duration.count() <<" ms.\n";
    cout << A3[5678] << endl;// Da sprijeèi potpunu eliminaciju koda s opcijom -O2



    return 0;
}
