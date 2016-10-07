#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <list>
#include "sys/stat.h"


int main(void)
{
    std::string a="cijene.txt";
    std::ifstream is (a, std::ifstream::binary);

    if(!is)
        	std::cout<< "Opala ljubav je propala\n";

    char c;
    double broj;
    while (is.get(c))          // loop getting single characters
    {
        std::cout << c;
        if (c == ':')
        {is>>broj;
        std::cout << broj;}
    }
    is.close();

    struct _stat fileInfo;
	if(_stat ("cijene.txt",&fileInfo) != 0){
		throw "stat error!";
	}
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    time_t vrijeme=std::chrono::system_clock::to_time_t ( today );
    std::cout << fileInfo.st_ctime << std::endl;
    std::cout << fileInfo.st_mtime << std::endl;
    std::cout << fileInfo.st_atime << std::endl;
    std::cout << ctime(&vrijeme) << std::endl;

    return 0;
}
