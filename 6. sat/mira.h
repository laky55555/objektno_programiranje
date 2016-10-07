#include <iostream>
#include <array>
#include <initializer_list>
#include <algorithm>
#include <fstream>
#include <utility>
// Matrica sa statički zadanim dimenzijama. Nije moguća realokacija.
// rows = broj redaka, cols = broj stupaca
template <int rows, int cols>
class Matrix{
    public:
        Matrix(){std::cout << "Ctor1" << std::endl;}
        Matrix(double d);
        Matrix(std::initializer_list<std::initializer_list<double>> li);
        // operatori indeksiranja: i=redak, j=stupac
        double & operator()(unsigned int i, unsigned int j){return mData[i*cols+j];};
        double const & operator()(unsigned int i, unsigned int j) const {return mData[i*cols+j];}

        Matrix<rows, cols>& operator+=(const Matrix<rows, cols> M1);
        Matrix<rows, cols>& operator-=(const Matrix<rows, cols> M1);
        // postavi sve elemente na nulu
        void zero();
        // postavi na jediničnu matricu
        void eye();
        explicit operator bool() const;

        //kopiranje
        Matrix(const Matrix<rows, cols> &M);
        Matrix<rows, cols>& operator=(const Matrix<rows, cols> &M);
        //premjestanje
        Matrix(Matrix<rows, cols> &&M)noexcept:mData(std::move(M.mData)){std::cout << "MCtor" << std::endl;}
        Matrix<rows, cols>& operator=(Matrix<rows, cols> &&M)noexcept;

    private:
        // Pamtimo elemente zapisane po recima
        std::array<double, rows*cols> mData;
};

template <int rows, int cols>
Matrix<rows, cols>::Matrix(double d)
{
    std::cout << "Ctor2" << std::endl;
    std::fill(mData.begin(), mData.end(), d);
}

template <int rows, int cols>
Matrix<rows, cols>::Matrix(std::initializer_list<std::initializer_list<double>> li)
{
    std::cout << "Ctor3" << std::endl;
    int i=0;
    using Iterator1 = std::initializer_list<std::initializer_list<double>>::iterator;
    using Iterator2 = std::initializer_list<double>::iterator;
    for(Iterator1 it1=li.begin(); it1!=li.end(); ++it1)
    {
        for(Iterator2 it2=(*it1).begin(); it2!=(*it1).end(); ++it2)
            mData[i++]=*it2;
        if(i%cols!=0)while(i%cols!=0) mData[i++]=0;//ako su neke podliste kraće nego bi trebale biti ostatak reda popunimo nulama
    }
}

template <int rows, int cols>
void Matrix<rows, cols>::zero()
{
    std::fill(mData.begin(), mData.end(), 0.0);
}

template <int rows, int cols>
void Matrix<rows, cols>::eye()
{
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
        {
            if(i==j) (*this)(i,j)=1;
            else (*this)(i,j)=0;
        }
}
template <int rows, int cols>
std::ostream& operator<<(std::ostream& out, const Matrix<rows,cols> &M)
{
    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<cols; ++j)
            out << M(i,j) << " ";
        out << std::endl;
    }
    return out;
}

template <int rows, int cols>
Matrix<rows, cols> operator+( const Matrix<rows, cols> M1, const Matrix<rows, cols> M2)
{
    Matrix<rows, cols> M3;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            M3(i,j)=M1(i,j)+M2(i,j);
    return M3;
}

template <int rows, int cols>
Matrix<rows, cols> operator-( const Matrix<rows, cols> M1, const Matrix<rows, cols> M2)
{
    Matrix<rows, cols> M3;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            M3(i,j)=M1(i,j)-M2(i,j);
    return M3;
}
template <int rows, int cols>
Matrix<rows, cols> operator*(double d, const Matrix<rows, cols> M)
{
    Matrix<rows, cols> M3;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            M3(i,j)=d*M(i,j);
    return M3;
}
template <int rows, int cols>
Matrix<rows, cols> operator*(const Matrix<rows, cols> M, double d)
{
    Matrix<rows, cols> M3;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            M3(i,j)=d*M(i,j);
    return M3;
}

template<int rows, int cols, int med>
Matrix<rows, cols> operator*(const Matrix<rows, med> M1, const Matrix<med, cols> M2)
{
    Matrix<rows, cols> M3;
    M3.zero();
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            for(int k=0; k<med; ++k)
                M3(i,j)+=M1(i,k)*M2(k,j);
    return M3;
}
template <int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator+=(const Matrix<rows, cols> M1)
{
    (*this)=(*this)+M1;
    return *this;
}


template <int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator-=(const Matrix<rows, cols> M1)
{
    (*this)=(*this)-M1;
    return *this;
}

template <int rows, int cols>
Matrix<rows, cols>::operator bool() const
{
    //ako je matrica NULA vraca 1, inace nula
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
            if((*this)(i,j)!=0) return false;
    return true;
}

template <int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(Matrix<rows, cols> &&M) noexcept
{
    std::cout << "M_OP" << std::endl;
    if(this!=&M)mData=std::move(M.mData);
    return *this;
}

template <int rows, int cols>
Matrix<rows, cols>::Matrix(const Matrix<rows, cols> &M)
{
    std::cout << "CCtor" << std::endl;
    std::copy(M.mData.begin(), M.mData.end(), mData.begin());
}
template <int rows, int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(const Matrix<rows, cols> &M)
{
    std::cout << "C_OP" << std::endl;
    if(this!=&M)std::copy(M.mData.begin(), M.mData.end(), mData.begin());
    return *this;
}

