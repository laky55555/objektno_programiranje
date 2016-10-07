#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include "math.h"

using namespace std;


double podudaranje(set<string> & skup1, set<string> & skup2)
{
    set<string> presjek;
    set_intersection (skup1.begin(), skup1.end(), skup2.begin(), skup2.end(), inserter(presjek, presjek.end()));
    return  presjek.size() / (sqrt(skup1.size()) * sqrt(skup2.size()));

}

int main(void)
{
    set<string> skup1, skup2;
    skup1.insert("abc");
    skup1.insert("fds");
    skup1.insert("aas");
    skup1.insert("123");

    skup2.insert("aas");
    skup2.insert("123");
    skup2.insert("abc");

    cout << podudaranje(skup1, skup2) <<endl;

    return 0;
}

