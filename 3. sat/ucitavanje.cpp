#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


int main(void)
{
    int redci, stupci;
    char **polje;
    std::ifstream myfile;
    myfile.open("pocetno_stanje.txt");
    myfile>>redci;
    myfile>>stupci;

    std::cout << redci << " " << stupci << std::endl;

    polje = (char**)malloc(redci * sizeof(char*));
    for(int i=0; i<redci; i++)
        polje[i] = (char*)malloc(stupci*sizeof(char));

    char c;
    myfile.get(c);
    while(c != '\n')
        myfile.get(c);
    int j=0;
    for(int i=0; i<redci; i++)
    {
        while(c != '\n')
        myfile.get(c);
    }
    /*for(int i=0; i<redci; i++)
        for(int j=0; j<stupci; j++)
        {
            myfile.get(polje[i][j]);
            std::cout << polje[i][j];
        }*/
    for(int i=0; i<redci; i++)
    {
        for(int j=0; j<stupci; j++)
            std::cout << polje[i][j];
        std::cout << std::endl;
    }


    myfile.close();



    return 0;
}
