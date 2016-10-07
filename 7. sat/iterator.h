#include <iostream>
#include <memory>
#include <utility>


class Segment{
    public:
        // Konstruktor. Postavlja lijevi i desni kraj intervala i pokaziva� na roditelja.
        Segment(double left, double right, Segment * parent) : mpt_l(left), mpt_r(right), mparent(parent) {}

        // Da li je segment list (nema djece) ?
        bool isLeaf() const{ return mseg_l.get() == nullptr; }

        // Profini segment. Ako ve� ima djecu ne radi ni�ta.
        void refine();

        // Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
        // list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak.
        void coarse();

        // Lijevi podsegment ili nullptr.
        Segment * getLeft()  { return mseg_l.get(); }

        // Desni podsegment ili nullptr.
        Segment * getRight() { return mseg_r.get(); }

        // Ispi�i segment.
        void print(){std::cout << "(" << mpt_l <<","<<mpt_r<<") ";}

        // Vrati pokaziva� na roditelja.
        Segment * parent() { return mparent; }
    private:
      // lijevi kraj segmenta
      double mpt_l;
      // desni kraj segmenta
      double mpt_r;
      // djeca segementa
      std::unique_ptr<Segment> mseg_l;  // lijevi podsegment
      std::unique_ptr<Segment> mseg_r;  // desni podsegment
      // segment roditeljit->get()->
      Segment * mparent;
      friend class GridLeafIterator;
};


class GridLeafIterator{
    public:
         GridLeafIterator(Segment* root);
         // operator inkrementiranja (dovoljna je prefiks verzija)
         GridLeafIterator& operator++();
         // operatori dohvata - dereferenciranje i operator strelica
         Segment& operator*(){return *trenutna;}
         //const Segment* operator*()const {return trenutna;}
         Segment* operator->(){return trenutna;}
         //const Segment* operator->() const {return trenutna;}
         bool posljednji(){return trenutna == zadnje ? true : false;}
         void zadnji_u_nizu() {trenutna = nullptr;}
    private:
         Segment *  mRoot, *trenutna, *zadnje;
         // implementacijski detalji
         // ...
         friend bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs) { return lhs.trenutna==rhs.trenutna && lhs.mRoot==rhs.mRoot ? true : false ;}
         friend bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs) { return lhs.trenutna!=rhs.trenutna || lhs.mRoot!=rhs.mRoot ? true : false ;}
};


class Grid {
    public:
       using iterator = GridLeafIterator;

       Grid(double a, double b): root(a,b, nullptr) {}

       iterator begin();
       iterator end();

       // Profini svaki segment list u trenutnoj mre�i.
       void uniform_refine();
       // Ispi�i sve segmente listove mre�e.
       void print();
       // Broj segmenata listova u mre�i.
       int  nOfSegments();
       // Profini segment list koji je noSeg po redu.
       // Ako je noSeg >=  nOfSegments() izbaci izuzetak
       void refine_selected(int noSeg);
       // Eliminiraj  segment list koji je noSeg po redu ukoliko
       // su oba djeteta njegovog roditelja listovi.
       void coarse_selected(int noSeg);
    private:
       Segment root;
};









