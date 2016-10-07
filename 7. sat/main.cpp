#include "iterator.h"



int main(void)
{

    Grid grid(0.0,1.0);
    grid.print();
    std::cout<< std::endl;

    grid.uniform_refine();
    std::cout << "Refine";

    grid.print(); std::cout<< "nakon refine"<< std::endl;

    grid.uniform_refine();
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;

    grid.refine_selected(2);
    std::cout << "refine segment 2\n";
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;

    grid.coarse_selected(1);
    std::cout << "eliminiraj segment 1\n";
    grid.print(); std::cout<< std::endl;
    std::cout << "no of segments = " << grid.nOfSegments() << std::endl;
    return 0;
}
