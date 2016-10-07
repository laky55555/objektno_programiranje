#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <map>
#include <string>
#include <list>
#include "sys/stat.h"



class Subject;

class Observer{
public:
	virtual void update(Subject*) = 0;
	virtual ~Observer() {}
};

class Subject{
public:
    virtual void attach(Observer *o);
    virtual void dettach(Observer *o);
    virtual void notify();
    virtual ~Subject() {}
private:
    std::list<Observer*> observers;
};

class IsFileModified{
public:
    IsFileModified(std::string ime) : fileName(ime){};
    bool is_modified_since(time_t lastReadTime) {return (lastReadTime < getLastModificationTime() ? true : false); }
    virtual ~IsFileModified(){}
protected:
    std::string fileName;
private:
    time_t getLastModificationTime();

};

class Prices : public Subject, private IsFileModified {
public:
    Prices(std::string ime) : IsFileModified(ime) {readFile();}
    virtual void setState();
    virtual const std::map<std::string, double>& getState()const {return price_list;}
    virtual ~Prices() {}
private:
    //std::string ime_datoteke;
    std::map<std::string, double> price_list;
    time_t lastReadTime;
    void readFile();
};

class DisplayInfo : public Observer{
public:
    DisplayInfo(Prices *cijena) : pok_cijena(cijena) {pok_cijena->attach(this);}
    virtual void update(Subject * subjekt) {if(subjekt == pok_cijena) ispisi_listu(); }
    virtual void ispisi_listu() const;
    virtual ~DisplayInfo(){}
private:
    //std::map<std::string, double> price_list;
    Prices *pok_cijena;
};



