#include <iostream>
#include <list>
#include <chrono>
#include <map>
#include <string>
class Observer;

class Subject
{
public:
  virtual void attach(Observer *o);
  virtual void dettach(Observer *o);
  virtual void notify();
  virtual ~Subject(){}
protected:
    std::list<Observer*> m_observers;
protected:
    typedef std::list<Observer*>::iterator iterator;
};

class IsFileModified
{
public:
    IsFileModified(std::string name):m_fileName(name){}
    bool is_modified_since(time_t lastReadTime);
    virtual ~IsFileModified(){}
protected:
    std::string m_fileName;
    time_t getLastModificationTime();
};

class Prices: public Subject, private IsFileModified
{
public:
    Prices(std::string fileName):IsFileModified(fileName){m_lastReadTime=getLastModificationTime();readFile();}
    virtual void setState();
    virtual const std::map<std::string, double>& getState()const {return m_price_list;}
    virtual ~Prices(){}
protected:
    std::map<std::string, double> m_price_list;
    time_t m_lastReadTime;
    virtual void readFile();
};

class Observer
{
public:
    virtual void update(Subject* s) = 0;
	virtual ~Observer() {}
};

class DisplayInfo:public Observer
{
public:
    DisplayInfo(Prices *p):m_price(p){m_price->attach(this);}
    virtual void update(Subject *s);
    virtual void display()const;
    virtual ~DisplayInfo(){}
private:
    Prices* m_price;
};
