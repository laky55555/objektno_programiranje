#include "Tocka.h"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>





double tocka::udaljenost ( tocka P )
{
	return std::sqrt(double(P.x-x)*(P.x-x) + (P.y-y)*(P.y-y));
}


void tocka::upis_tocke()
{
    std::cout << "Upisite koordinate tocke" << std::endl;
    std::cin >> x >> y;
}


void tocka::ispis_tocke()
{
    std::cout << "Tocka ima koordinate: " << x << " i " << y << std::endl;
}

/*bool operator== (const tocka &a, const tocka &b)
{
	if (a.x == b.x && a.y == b.y)
        return true;
    else
        return false;
}*/

bool operator< (const tocka &a, const tocka &b)
{
	if (a.x < b.x || (a.x == b.x && a.y < b.y) )
        return true;
    else
        return false;
}


