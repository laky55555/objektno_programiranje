#include <iostream>
#include <memory>
#include <utility>
class Segment{
    public:
        // Konstruktor. Postavlja lijevi i desni kraj intervala i pokazivač na roditelja.
        Segment(double left, double right, Segment * parent) : mpt_l(left), mpt_r(right), mparent(parent) {}
        // Da li je segment list (nema djece) ?
        bool isLeaf() const{ return mseg_l.get() == nullptr; }
        // Profini segment. Ako već ima djecu ne radi ništa.
        void refine();
        // Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
        // list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak.
        void coarse();
        // Lijevi podsegment ili nullptr.
        Segment * getLeft()  { return mseg_l.get(); }
        // Desni podsegment ili nullptr.
        Segment * getRight() { return mseg_r.get(); }
        // Ispiši segment.
        void print(){std::cout << "(" << mpt_l <<","<<mpt_r<<") ";}
        // Vrati pokazivač na roditelja.
        Segment * parent() { return mparent; }

        //kontrola kopiranja premjestanjem
        /*Segment(const Segment &S)=default;
        Segment& operator=(const Segment &S)=default;
        Segment(Segment &&S)noexcept
        {
            mseg_l.release();
            mseg_r.release();
            mpt_l=S.mpt_l;
            mpt_r=S.mpt_r;
            mseg_l.reset(S.mseg_l.release());
            mseg_r.reset(S.mseg_r.release());
            mparent=S.mparent;
        }
        Segment& operator=(Segment &&S) noexcept
        {
            if(this!=&S)
            {
                mseg_l.release();
                mseg_r.release();
                mpt_l=S.mpt_l;
                mpt_r=S.mpt_r;
                mseg_l.reset(S.mseg_l.release());
                mseg_r.reset(S.mseg_r.release());
                mparent=S.mparent;
            }
            return *this;
        }*/


    private:
      // lijevi kraj segmenta
      double mpt_l;
      // desni kraj segmenta
      double mpt_r;
      // djeca segementa
      std::unique_ptr<Segment> mseg_l;  // lijevi podsegment
      std::unique_ptr<Segment> mseg_r;  // desni podsegment
      // segment roditelj
      Segment * mparent;
      friend class GridLeafIterator;
};
class GridLeafIterator;

class Grid {
    public:

       Grid(double a, double b): root(a,b, nullptr) {}

       GridLeafIterator begin();
       GridLeafIterator end();

       // Profini svaki segment list u trenutnoj mreži.
       void uniform_refine();
       // Ispiši sve segmente listove mreže.
       void print();
       // Broj segmenata listova u mreži.
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

class GridLeafIterator{
    public:
         GridLeafIterator(Segment* root):mRoot(root){}
         GridLeafIterator(Segment* root, Segment *curr):mRoot(root), current(curr){}
         // operator inkrementiranja (dovoljna je prefiks verzija)
         GridLeafIterator& operator++();
         GridLeafIterator& operator--();
         // operatori dohvata - dereferenciranje i operator strelica
         Segment& operator* (){return (*current);}
         Segment* operator->(){return current;}

    private:
         Segment *  mRoot;
         // implementacijski detalji
         // ...
         Segment *current;  //na koji segment trenutno pokazujemo
         friend
         bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
         friend
         bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs);
};
