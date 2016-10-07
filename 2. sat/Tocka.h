#ifndef  _TOC_H_IS_INCLUDED_
#define  _TOC_H_IS_INCLUDED_

#include <set>
#include <vector>

class tocka{
private:
    int x, y;
public:
    tocka (){}
	tocka (int a, int b){x=a; y=b;}
	~tocka (){}
	void upis_tocke ();
	void ispis_tocke ();
	double udaljenost ( tocka P );
	//friend bool operator== (const tocka &a, const tocka &b);
	friend bool operator< (const tocka &a, const tocka &b);
};




#endif
