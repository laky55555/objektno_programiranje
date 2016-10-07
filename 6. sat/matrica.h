#include <iostream>
#include <array>
#include <initializer_list>


// Matrica sa statièki zadanim dimenzijama. Nije moguæa realokacija.
// rows = broj redaka, cols = broj stupaca
template <int rows, int cols>
class Matrix{
    public:
        Matrix<rows, cols>(){}
        Matrix<rows, cols>(double a){for(int i=0; i<rows*cols; i++) mData[i] = a; }
        Matrix<rows, cols>(std::initializer_list<std::initializer_list<double>> lista);

        Matrix(const Matrix<rows, cols> &M) = default;
        Matrix<rows, cols>& operator=(const Matrix<rows, cols> &M) = default;

        Matrix<rows, cols>(Matrix<rows, cols> &&x) noexcept{mData = std::move(x.mData);}
        Matrix<rows, cols>& operator=(Matrix<rows, cols> &&x) noexcept;

        ~Matrix<rows, cols>() = default;


        // operatori indeksiranja: i=redak, j=stupac
        double & operator()(unsigned int i, unsigned int j);
        double const & operator()(unsigned int i, unsigned int j) const;

        Matrix<rows, cols>& operator+= (const Matrix<rows, cols> x);
        Matrix<rows, cols>& operator-= (const Matrix<rows, cols> x);

        explicit operator bool() const;

        // postavi sve elemente na nulu
        void zero();
        // postavi na jediniènu matricu
        void eye();

        //void print(std::ostream& out) const;
    private:
        // Pamtimo elemente zapisane po recima
        std::array<double, rows*cols> mData;
};

template <int rows,  int cols>
Matrix<rows, cols>::Matrix(std::initializer_list<std::initializer_list<double>> lista)
{
    std::initializer_list<std::initializer_list<double>>::iterator vanjski;
    std::initializer_list<double>::iterator unutarnji;
    int i=0;
    for(vanjski=lista.begin(); vanjski!=lista.end(); vanjski++)
        for(unutarnji=(*vanjski).begin(); unutarnji!=(*vanjski).end(); unutarnji++)
        {
            mData[i] = (*unutarnji);
            i++;
        }
}

template <int rows,  int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator=(Matrix<rows, cols> &&x) noexcept
{
    if(this != &x)
        mData = std::move(x.mData);
    return *this;
}

template <int rows,  int cols>
void Matrix<rows, cols>::zero()
{
    for(int i=0; i<rows*cols; i++)
        mData[i] = 0;
}

template <int rows,  int cols>
void Matrix<rows, cols>::eye()
{
    int pozicija=0;
    for(int i=0; i<rows*cols; i++)
    {
        if(pozicija%(cols+1) == 0)
            mData[i] = 1;
        else
            mData[i] = 0;
        pozicija++;
    }
}

template <int rows,  int cols>
double& Matrix<rows, cols>::operator()(unsigned int i, unsigned int j)
{
    return mData[i*cols+j];
}

template <int rows,  int cols>
double const& Matrix<rows, cols>::operator()(unsigned int i, unsigned int j) const
{
    double const& a = mData[i*cols+j];
    return a;
}

template <int rows,  int cols>
Matrix<rows, cols> operator+ (const Matrix<rows, cols> x, const Matrix<rows, cols> y)
{
    Matrix<rows, cols> a;
    for (int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
        a(i,j) = x(i,j) + y(i,j);
    return a;
}

template <int rows,  int cols>
Matrix<rows, cols> operator- (const Matrix<rows, cols> x, const Matrix<rows, cols> y)
{
    Matrix<rows, cols> a;
    for (int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
        a(i,j) = x(i,j) - y(i,j);
    return a;
}

template <int rows,  int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator+= (const Matrix<rows, cols> x)
{
    for (int i =0; i<cols*rows; i++)
        this->mData[i] += x.mData[i];
    return *this;
}

template <int rows,  int cols>
Matrix<rows, cols>& Matrix<rows, cols>::operator-= (const Matrix<rows, cols> x)
{
    for (int i =0; i<cols*rows; i++)
        this->mData[i] -= x.mData[i];
    return *this;
}

template <int rows,  int cols>
Matrix<rows, cols> operator* (const Matrix<rows, cols> x, const double y)
{
    Matrix<rows, cols> a;
    for (int i =0; i<rows; i++)
        for(int j=0; j<cols; j++)
            a(i,j) = x(i,j) * y;
    return a;
}

template <int rows,  int cols>
Matrix<rows, cols> operator* (const double x, const Matrix<rows, cols> y)
{
    Matrix<rows, cols> a;
    for (int i =0; i<rows; i++)
        for(int j=0; j<cols; j++)
            a(i,j) = y(i,j) * x;
    return a;
}

template <int rows,  int cols, int stupci>
Matrix<rows, stupci> operator* (const Matrix<rows, cols> a, const Matrix<cols, stupci> b)
{
    Matrix<rows, stupci> x;
    x.zero();
    for (int i=0; i<rows; i++)
        for(int j=0; j<stupci; j++)
            for(int k=0; k<cols; k++)
                x(i,j) += a(i,k) * b(k,j);
    return x;
}

/*template <int rows,  int cols>
void  Matrix<rows, cols>::print(std::ostream& out) const
{
    for (int i=0; i<rows*cols; i++)
    {
        out << mData[i] << " ";
        if ( (i+1)%cols == 0)
            out << std::endl;
    }
}*/

template <int rows,  int cols>
Matrix<rows, cols>::operator bool() const
{
    for(int i=0; i<rows*cols; i++)
        if(mData[i] != 0)
            return false;
    return true;
}

template <int rows,  int cols>
std::ostream& operator<<(std::ostream& ispis, const Matrix<rows, cols> a)
{
    for (int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            ispis << a(i,j) << " ";
        ispis << std::endl;
    }
    return ispis;
}



