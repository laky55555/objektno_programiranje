#include <iostream>
#include <string>
#include <set>

using namespace std;



void separator(string const & text, set<string> & skup)
{
    int i;
    for(i=0; i<text.length(); i++)
    {
        string rijec;
        while(isalnum(text[i]))
        {
            rijec += text[i];
            i++;
        }
        if (rijec.length())
            skup.insert(rijec);
        rijec.clear();
    }
}







int main (void)
{
    string a="klj l    kjlkj. fjlkad--fdaf kkjl?kjk!jjjjjj 89";
    set<string> skup;

    separator(a, skup);
    int i=0;
    set<string>::iterator si;
    for(si = skup.begin(); si != skup.end(); si++)
    {
        i++;
        cout << *si <<endl;
    }
    cout << i<<endl;
    return 0;
}
