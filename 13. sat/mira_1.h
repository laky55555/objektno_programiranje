#include <iostream>
#include <array>

class Scalar;
template <typename T>
struct Traits{
   typedef T const& ExprRef;
};
template <>
struct Traits<Scalar>{
   typedef Scalar  ExprRef;
};


template <typename OP1, typename OP2>
class Add{
    private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
    public:
	Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]+op2[i]; }
	friend std::ostream& operator<< (std::ostream& out, const Add& a){out << "Add<" << a.op1 <<"," << a.op2 << ">"; return out;}
};

template <typename OP1, typename OP2>
class Sub{
    private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
    public:
    Sub(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]-op2[i]; }
	friend std::ostream& operator<< (std::ostream& out, const Sub& a){out << "Sub<" << a.op1 <<"," << a.op2 << ">"; return out;}
};

template <typename OP1, typename OP2>
class Mult{
    private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
    public:
	Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
	double operator[](int i) const { return op1[i]*op2[i]; }
	friend std::ostream& operator<< (std::ostream& out, const Mult& a){out << "Mult<" << a.op1 << "," <<a.op2 << ">";return out;}
};

class Scalar{
    private:
	double  const & val;
    public:
	Scalar(double const& v) : val(v) {}
	double operator[](size_t) const { return val; }
	friend std::ostream& operator<< (std::ostream& out, const Scalar& a){out << a.val; return out;}
};

template <size_t N, typename Rep = std::array<double,N> >
class Vector{
    private:
        Rep expr_rep;  // Implementacijski objekt
    public:
	Vector(Rep const& r) : expr_rep(r) {}
	explicit Vector(double val = 0.0) {expr_rep.fill(val);}
        template <typename Rep2>
        Vector& operator=(Vector<N,Rep2> const& rhs){
            for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
            return *this;
        }
        // Pomoćne funkcije
        size_t size() const { return N; }
	double operator[](size_t i) const {  return expr_rep[i]; }
	double& operator[](size_t i) { return expr_rep[i]; }
	Rep const& rep() const { return expr_rep; }
	Rep& rep() { return expr_rep; }
	friend std::ostream& operator<<(std::ostream& out, const Vector& a){out << a.expr_rep; return out;}

};
template <size_t N>
std::ostream& operator<<(std::ostream& out, const std::array<double, N>& a){
    out << "Array<"<< N << ">";
    return out;
}
template <size_t N,   typename R1, typename R2>
Vector<N, Add<R1,R2> >
operator+(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
}

template <size_t N,   typename R1, typename R2>
Vector<N, Sub<R1,R2> >
operator-(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Sub<R1,R2> >( Sub<R1,R2>( a.rep(),b.rep() ) );
}


template <size_t N,   typename R1>
Vector<N, Mult<Scalar,R1> >
operator*(double const& a, Vector<N,R1> const& b){
    return Vector<N, Mult<Scalar, R1> >( Mult<Scalar, R1>( Scalar(a),b.rep() ) );
}

template <size_t N, typename R1>
Vector <N, Mult<R1,Scalar> >
operator*(Vector <N, R1> const& a, double const& b){
    return Vector<N, Mult<R1, Scalar> >(Mult <R1, Scalar> (a.rep(), Scalar(b)));
}

template <size_t N, typename R1>
Vector <N, Add<R1,Scalar> >
operator+(Vector <N, R1> const& a, double const& b){
    return Vector<N, Add<R1, Scalar> >(Add<R1, Scalar> (a.rep(), Scalar(b)));
}


template <size_t N, typename R1>
Vector <N, Sub<R1,Scalar> >
operator-(Vector <N, R1> const& a, double const& b){
    return Vector<N, Sub<R1, Scalar> >(Sub<R1, Scalar> (a.rep(), Scalar(b)));
}

template <size_t N,   typename R1>
Vector<N, Add<Scalar,R1> >
operator+(double const& a, Vector<N,R1> const& b){
    return Vector<N, Add<Scalar, R1> >( Add<Scalar, R1>( Scalar(a),b.rep() ) );
}


template <size_t N,   typename R1>
Vector<N, Sub<Scalar,R1> >
operator-(double const& a, Vector<N,R1> const& b){
    return Vector<N, Sub<Scalar, R1> >( Sub<Scalar, R1>( Scalar(a),b.rep() ) );
}
template <size_t N,   typename R1, typename R2>
Vector<N, Mult<R1,R2> >
operator*(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Mult<R1,R2> >( Mult<R1,R2>( a.rep(),b.rep() ) );
}
