#include "stablo.h"
#include <stdexcept>

void Segment::refine()
{
    if(isLeaf())  //ako je list onda ga profinjujemo
    {
        Segment *leftchild = new Segment(mpt_l,(mpt_l+mpt_r)/2,this);
        Segment *rightchild = new Segment((mpt_l+mpt_r)/2, mpt_r, this);
        mseg_l.reset(leftchild);
        mseg_r.reset(rightchild);
        //oovo da djecu stavi kao listove
        /*(*leftchild).mseg_l.reset(nullptr);
        (*rightchild).mseg_l.reset(nullptr);
        (*leftchild).mseg_r.reset(nullptr);
        (*rightchild).mseg_r.reset(nullptr);*/
    }
}
    // Okrupni segment, tj. eliminiraj djecu segmenta. Time segment postaje
        // list. Segment mora imati djecu koja su listovi, u suprotnom izbaciti izuzetak.
void Segment::coarse()
{
    Segment* l=getLeft();
    Segment* r=getRight();
    try
    {
        if(!(l->isLeaf() || r->isLeaf()))
            throw std::runtime_error("ne mozemo okrupniti segment!");
        mseg_l.release();
        mseg_r.release();
    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}

GridLeafIterator& GridLeafIterator::operator++()
{
    //treba naci iduci list
    Segment *roditelj=current->parent();
    if(roditelj==nullptr)
    {
        current=nullptr;
        return *this;
    }
    while(roditelj->getRight()==current)
    {
        current=roditelj;
        roditelj=roditelj->parent();
        if(roditelj==nullptr)break;
    }
    if(roditelj==nullptr)
    {
        current=nullptr;
        return *this;
    }
    current = roditelj->getRight();
    while(current->getLeft()!=nullptr)
        current=current->getLeft();
    return *this;
}

GridLeafIterator& GridLeafIterator::operator--()
{
    Segment *roditelj=current->parent();
    while(current==roditelj->getLeft())
    {
        current=roditelj;
        roditelj=roditelj->parent();
    }
    current=roditelj->getLeft();
    while(current->getRight()!=nullptr)
        current=current->getRight();
    return *this;
}

bool operator==(GridLeafIterator const & lhs, GridLeafIterator const & rhs)
{
    if(lhs.current==rhs.current && lhs.mRoot==rhs.mRoot) return true;
    return false;
}


bool operator!=(GridLeafIterator const & lhs, GridLeafIterator const & rhs)
{
    if(lhs.current!=rhs.current || lhs.mRoot!=rhs.mRoot) return true;
    return false;
}


GridLeafIterator Grid::begin()
{
    Segment* tmp=&root;
    while(tmp->getLeft()!=nullptr)
        tmp=tmp->getLeft();
    GridLeafIterator i(&root, tmp);
    return i;
}

GridLeafIterator Grid::end()
{
    GridLeafIterator i(&root, nullptr);
    return i;
}

void Grid::uniform_refine()
{
    for(GridLeafIterator it=begin(); it!=end(); ++it)
        it->refine();
}
void Grid::print()
{
    for(GridLeafIterator it=begin(); it!=end(); ++it)
        it->print();
}

int  Grid::nOfSegments()
{
    int j=0;
    for(GridLeafIterator it=begin(); it!=end(); ++it)
        ++j;
    return j;
}
void Grid::refine_selected(int noSeg)
{
    try
    {
        int k=0;
        if(noSeg>=nOfSegments())
            throw std::runtime_error("broj listova je manji od zadanog broja");
        for(GridLeafIterator it=begin(); it!=end(); ++it)
        {
            if(k==noSeg)
            {
                it->refine();
                break;
            }
            else ++k;
        }

    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}

void Grid::coarse_selected(int noSeg)
{
    std::cout << "tu smo" << std::endl;
    try
    {
        int k=0;
        if(noSeg>=nOfSegments())
            throw std::runtime_error("broj listova je manji od zadanog broja");
        for(GridLeafIterator it=begin(); it!=end(); ++it)
        {
            if(k==noSeg)
            {
                Segment* roditelj=it->parent();
                roditelj->coarse();
                break;
            }
            else ++k;
        }

    }
    catch(std::runtime_error const &e){
        std::cout << "Error:" << e.what() << std::endl;
    }
}




















