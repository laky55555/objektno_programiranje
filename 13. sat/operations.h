#include <iostream>
#include <array>


template <size_t N, typename Rep = std::array<double,N> >
class Vector{
private:
        Rep expr_rep;  // Implementacijski objekt
public:
	// Konstruktor inicijalizira implementacijski objekt
	Vector(Rep const& r) : expr_rep(r) {}
	// Vektor mo emo inicijalizirati konstantom.
	explicit Vector(double val = 0.0) {expr_rep.fill(val);}
        // pridru ivanje polja razlièitog tipa
        template <typename Rep2>
        Vector& operator=(Vector<N,Rep2> const& rhs){
            for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
            return *this;
        }
        // Pomoæne funkcije
        size_t size() const { return N; }
	double operator[](size_t i) const {  return expr_rep[i]; }
	double& operator[](size_t i) { return expr_rep[i]; }
	Rep const& rep() const { return expr_rep; }
	Rep& rep() { return expr_rep; }
	friend std::ostream& operator<<(std::ostream& out, const Vector& v) {  out <<v.expr_rep; return out;}
};

template <size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<double, N>& v)
{  out <<"Array<" << N << ">"; return out;}

// Operator indeksiranja vraæa vrijednost skalara.
class Scalar{
private:
	double  const & val;
public:
	Scalar(double const& v) : val(v) {}
	double operator[](size_t) const { return val; }
	friend std::ostream& operator<<(std::ostream& out, const Scalar& v) { out << v.val; return out;}
};



// Klasa obilje ja koja nam omoguæava vektor tretiramo kroz
// reference, a skalare po vrijednosti.
template <typename T>
struct Traits{
   typedef T const& ExprRef;
};
// Specijalizacija za skalare
// Na skalare ne uzimamo referencu jer im vijek trajanja mo e biti kraæi od
// vijeka trajanja vektora
template <>
struct Traits<Scalar>{
   typedef Scalar  ExprRef;
};

// Klasa koja reprezentira zbrajanje.
template <typename OP1, typename OP2>
class Add{
private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]+op2[i]; }
    friend std::ostream& operator<<(std::ostream& out, const Add& a) { out <<"Add<" << a.op1 << "," << a.op2 << ">"; return out;}
};


// Klasa koja reprezentira oduzimanje.
template <typename OP1, typename OP2>
class Sub{
private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
public:
	Sub(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const {return op1[i]-op2[i]; }
	friend std::ostream& operator<<(std::ostream& out, const Sub& s) { out <<"Sub<" << s.op1 << "," << s.op2 << ">"; return out;}
};

// Klasa koja reprezentira mnozenje.
template <typename OP1, typename OP2>
class Mult{
    private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
    public:
	Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]*op2[i]; }
	friend std::ostream& operator<<(std::ostream& out, const Mult& m) { out <<"Mult<" << m.op1 << "," << m.op2 << ">"; return out;}
};


// Mno enje skalar * vektor
template <size_t N, typename R2>
Vector<N, Mult<Scalar,R2> >
operator*(double const& a, Vector<N,R2> const& b)
{
    return Vector<N,Mult<Scalar,R2> >( Mult<Scalar,R2>( Scalar(a), b.rep() ) );
}

template <size_t N, typename R2>
Vector<N, Mult<R2,Scalar> >
operator*(Vector<N,R2> const& b, double const& a)
{
    return Vector<N,Mult<R2,Scalar> >( Mult<R2,Scalar>( b.rep(), Scalar(a) ) );
}


// zbrajanje skalar + vektor
template <size_t N, typename R2>
Vector<N, Add<Scalar,R2> >
operator+(double const& a, Vector<N,R2> const& b)
{
    return Vector<N, Add<Scalar,R2> >( Add<Scalar,R2>( Scalar(a),b.rep() ) );
}

template <size_t N, typename R2>
Vector<N, Add<R2,Scalar> >
operator+(Vector<N,R2> const& b, double const& a)
{
    return Vector<N, Add<R2,Scalar> >( Add<R2,Scalar>( b.rep(), Scalar(a) ) );
}


// oduzimanje skalar - vektor
template <size_t N, typename R2>
Vector<N, Sub<Scalar,R2> >
operator-(double const& a, Vector<N,R2> const& b)
{
    return Vector<N, Sub<Scalar,R2> >( Sub<Scalar,R2>( Scalar(a),b.rep() ) );
}

template <size_t N, typename R2>
Vector<N, Sub<R2, Scalar> >
operator-(Vector<N,R2> const& b, double const& a)
{
    return Vector<N, Sub<R2,Scalar> >( Sub<R2, Scalar>( b.rep(), Scalar(a) ) );
}

// Zbrajanje vektora
template <size_t N,   typename R1, typename R2>
Vector<N, Add<R1,R2> >
operator+(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
}

template <size_t N,   typename R1, typename R2>
Vector<N, Sub<R1,R2> >
operator-(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Sub<R1,R2> >( Sub<R1,R2>( a.rep(),b.rep() ) );
}

template <size_t N,   typename R1, typename R2>
Vector<N, Mult<R1,R2> >
operator*(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Mult<R1,R2> >( Mult<R1,R2>( a.rep(),b.rep() ) );
}
