#include "iterator.h"
#include <stdexcept>


void Segment::refine()
{
    if(isLeaf())
    {
        /*Segment a(mpt_l, (mpt_l+mpt_r)/2, this), b((mpt_l+mpt_r)/2, mpt_r, this);
        mseg_l.reset(&a);
        mseg_r.reset(&b);*/
        Segment *a = new Segment(mpt_l,(mpt_l+mpt_r)/2,this), *b = new Segment((mpt_l+mpt_r)/2, mpt_r, this);
        mseg_l.reset(a);
        mseg_r.reset(b);
    }
}

void Segment::coarse()
{
    try{
       // if(isLeaf())
       //     throw std::runtime_error("Coarse:  Segment je list, ne mogu vise dijeliti.");
      //  else

            if( !( getLeft()->isLeaf() && getRight()->isLeaf()) )
                throw std::runtime_error("Coarse:  Lijevo ili desno dijete nije list.");
            mseg_l.reset(nullptr);
            mseg_r.reset(nullptr);
       // }
    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}

GridLeafIterator Grid::begin()
{
    GridLeafIterator iter(&root);
    return iter;
}

GridLeafIterator Grid::end()
{
    GridLeafIterator iter(&root);
    iter.zadnji_u_nizu(); //postavi pointer trenutnog mjesta na nullpointer
    return iter;
}

void Grid::uniform_refine()
{
    auto it = begin();
    auto end_it = end();
    /*if(it->isLeaf())
            it->refine();*/
    for( ; it != end_it; ++it)
            it->refine();
}

void Grid::print()
{
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it)
        it->print();
}

int Grid::nOfSegments()
{  // Ne može biti konstantna jer nemamo konstantan iterator
    int n = 0;
    auto it = begin();
    auto end_it = end();
    for( ; it != end_it; ++it) n++;
    return n;
}

void Grid::refine_selected(int noSeg)
{
    try{
        auto it = begin();
        for(int i=0; i<noSeg; ++i)
        {
            if(it.posljednji()) //dosli smo do poslijednjeg segmenta
                throw std::runtime_error("refine_selected:   Nema toliko listova.");
            ++it;
        }
        it->refine();
    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}

void Grid::coarse_selected(int noSeg)
{
    try{
        auto it = begin();
        for(int i=0; i<noSeg; ++i)
        {
            if(it.posljednji()) //dosli smo do poslijednjeg segmenta
                throw std::runtime_error("coarse_selected:   Nema toliko listova.");
            ++it;
        }
        /*if(it->parent()->getLeft()->isLeaf() == true && it->parent()->getRight()->isLeaf())
           sta treba????? obrisati oba lista, ili samo jedan?? ako oba onda je to to
           */
        it->parent()->coarse();
    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}

GridLeafIterator::GridLeafIterator(Segment *root)
{
    mRoot = root;
    zadnje = trenutna = mRoot;
    while (!trenutna->isLeaf())
        trenutna = trenutna->getLeft();   //std::cout << "fdasslfask    "; trenutna->print();}

    while (!zadnje->isLeaf())
        zadnje = zadnje->getRight();

}

GridLeafIterator& GridLeafIterator::operator++()
{
    try{
        if(trenutna == nullptr)
            throw std::runtime_error("Ne moze vise ++, nema vise listova.");
        if(trenutna == mRoot || trenutna == zadnje)
            trenutna = nullptr;
        else
        {
            while(trenutna == trenutna->parent()->getRight())  //dizemo se kroz stablo sve dok smo desni segment
                trenutna = trenutna->parent();

            trenutna = trenutna->parent()->getRight();        //dolazimo na prvi desni segment koji jos nismo bili

            while(!trenutna->isLeaf())              //postavljamo trenutnu poziciju na najmanji podsegment od roditelja
                trenutna = trenutna->getLeft();
        }
    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }

    return *this;
}

/*
Segment& GridLeafIterator::operator*()
{
        if(0)
            throw std::runtime_error("Dereferenciranje end pokazivaca.");
        return *trenutna;
}
Segment* GridLeafIterator::operator->()
{
        if(0)
            throw std::runtime_error("Dereferenciranje end pokazivaca.");
        return trenutna;
}
*/
