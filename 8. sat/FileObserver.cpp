#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include "ctype.h"


#include "FileObserver.h"

/*Prices::Prices(std::string ime) : IsFileModified(ime){
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t vrijeme=std::chrono::system_clock::to_time_t ( today );
    lastReadTime = vrijeme;
    readFile();
}*/

void Subject::attach(Observer* o){
    std::list<Observer*>::iterator it;
	it = std::find(observers.begin(), observers.end(), o);
	if(it != observers.end())
		throw "Subject:: Observer already attached.";
	observers.push_back(o);
}

void Subject::dettach(Observer* o){
    std::list<Observer*>::iterator it;
	it = std::find(observers.begin(), observers.end(), o);
	if(it == observers.end())
			throw "Subject:: Observer is not attached.";
	observers.erase(it);
}

void Subject::notify(){
    std::list<Observer*>::iterator it;
    it = observers.begin();
    for( ; it != observers.end(); ++it)
    	(*it)->update(this);
}

void DisplayInfo::ispisi_listu() const{
    std::map<std::string, double>::iterator it;
    std::map<std::string, double> lista;
    lista = pok_cijena->getState();
    //std::cout << "Velicina mape: " << pok_cijena->getState().size() << ", a velicina lista: " << lista.size()<<std::endl;
	for (it=lista.begin(); it!=lista.end(); ++it)
        std::cout << it->first << ": " << it->second << std::endl;
    std::cout << std::endl;
}

time_t IsFileModified::getLastModificationTime(){
	// C-kod za Windows platformu
	struct _stat fileInfo;
	if(_stat (fileName.c_str(), &fileInfo) != 0){
            throw "stat error!";
    }
	return fileInfo.st_mtime;
}


void Prices::readFile(){

	std::ifstream is (fileName, std::ifstream::binary);
	if(!is)
    {
        std::cout << "Doslo je do pogreske kod otvaranja datoteke\n";
        exit(1);
    }
    char c;
    double broj;
    std::string artikl;
    while (is.get(c))
    {
        //std::cout <<"Ucitavam slovo:" <<c << "a " << artikl <<std::endl;
        if(isalnum(c) || c == ' ')
            artikl.push_back(c);
        if (c == ':')
        {
            is>>broj;
            price_list.insert( std::pair<std::string,double>(artikl,broj));
            //std::cout << artikl << broj <<std::endl;
            artikl.clear();
        }
    }
    is.close();

    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t vrijeme=std::chrono::system_clock::to_time_t ( today );
    lastReadTime = vrijeme;
}

void Prices::setState(){
    if (is_modified_since(lastReadTime))
    {
        price_list.clear();
        readFile();
        notify();
    }
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

