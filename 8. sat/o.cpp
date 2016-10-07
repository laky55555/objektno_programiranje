#include "o.h"
#include <algorithm>
#include <thread>

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

time_t IsFileModified::getLastModificationTime()
{
	// C-kod za Unix platformu
	struct stat fileInfo;
	if(stat (m_fileName.c_str(),&fileInfo) != 0)
	{
		throw "stat error!";
	}
	return fileInfo.st_mtime;
}

void Subject::attach(Observer *o)
{
    iterator it = std::find(m_observers.begin(), m_observers.end(), o);
	if(it != m_observers.end())
		throw std::runtime_error("observer already attached");
	m_observers.push_back(o);
}

void Subject::dettach(Observer* o)
{
    iterator it = std::find(m_observers.begin(), m_observers.end(), o);
    if(it==m_observers.end())
        throw std::runtime_error("observer is not attached");
    m_observers.erase(it);
}

void Subject::notify()
{
    for(iterator it=m_observers.begin(); it!=m_observers.end(); ++it)
        (*it)->update(this);
}


 bool IsFileModified::is_modified_since(time_t lastReadTime)
 {
    if(lastReadTime<getLastModificationTime())return true;
    return false;
 }


void Prices::setState()
{
    if(is_modified_since(m_lastReadTime))
    {
        m_lastReadTime=getLastModificationTime();
        m_price_list.clear();
        readFile();
        notify();

    }
}

void Prices::readFile()
{
    std::ifstream in(m_fileName);
    std::string line, ime, cijena;
    int i;
    double d=0;
    while(std::getline(in, line))
    {
        i=line.find(":");
        ime=line.substr(0,i-1);
        cijena=line.substr(i+1, line.size());
        std::stringstream ss;
        ss << cijena;
        //std::cout << ime << " " << cijena << std::endl;
        ss >> d;
        m_price_list[ime]=d;
        ime.clear();
        cijena.clear();
    }
}

void DisplayInfo::update(Subject *s)
{
    if(s==m_price)
    {
        display();
    }
}


void DisplayInfo::display() const
{
    std::map<std::string, double>::iterator it;
    std::map<std::string, double> mapi=m_price->getState();
    for(it=mapi.begin(); it!=mapi.end();++it)
        std::cout << it->first << " : " << it->second<< std::endl;
}



int main(void)
{

// konkretni subjekt
    Prices test("cijene.txt");
    // konkretni observer
    DisplayInfo display(&test);

    while (true) {
        test.setState();
        // spavaj jednu sekundu
        std::this_thread::sleep_for(std::chrono::milliseconds(1300));
    }



return 0;
}

