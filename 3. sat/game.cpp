#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
GameOL::GameOL() {}
GameOL::~GameOL() {}


int GameOL::broj_susjeda(int i, int j) const
{
    int g1=0,g2=0,g3=0,d1=0,d2=0,d3=0,l=0,d=0;
    if(i==0 && j==0)
    {
        d=mapa[i*s+j+1];
        d2=mapa[(i+1)*s+j];
        d3=mapa[(i+1)*s+j+1];
    }
    else if(i==0 && j>0 && j<s-1)
    {
        l=mapa[i*s+j-1];
        d=mapa[i*s+j+1];
        d1=mapa[(i+1)*s+j-1];
        d2=mapa[(i+1)*s+j];
        d3=mapa[(i+1)*s+j+1];
    }
    else if(i==0 && j==s-1)
    {
        l=mapa[i*s+j-1];
        d1=mapa[(i+1)*s+j-1];
        d2=mapa[(i+1)*s+j];
    }
    else if(i>0 && i<r-1 && j==0)
    {
        g2=mapa[(i-1)*s+j];
        g3=mapa[(i-1)*s+j+1];
        d=mapa[i*s+j+1];
        d2=mapa[(i+1)*s+j];
        d3=mapa[(i+1)*s+j+1];
    }
    else if(i>0 && i<r-1 && j==s-1)
    {
        g1=mapa[(i-1)*s+j-1];
        g2=mapa[(i-1)*s+j];
        l=mapa[i*s+j-1];
        d1=mapa[(i+1)*s+j-1];
        d2=mapa[(i+1)*s+j];
    }
    else if(i==r-1 && j==0)
    {
        g2=mapa[(i-1)*s+j];
        g3=mapa[(i-1)*s+j+1];
        d=mapa[i*s+j+1];
    }
    else if(i==r-1 && j>0 && j<s-1)
    {
        g1=mapa[(i-1)*s+j-1];
        g2=mapa[(i-1)*s+j];
        g3=mapa[(i-1)*s+j+1];
        l=mapa[i*s+j-1];
        d=mapa[i*s+j+1];
    }
    else if(i==r-1 && j==s-1)
    {
        g1=mapa[(i-1)*s+j-1];
        g2=mapa[(i-1)*s+j];
        l=mapa[i*s+j-1];
    }
    else
    {
        g1=mapa[(i-1)*s+j-1];
        g2=mapa[(i-1)*s+j];
        g3=mapa[(i-1)*s+j+1];
        l=mapa[i*s+j-1];
        d=mapa[i*s+j+1];
        d1=mapa[(i+1)*s+j-1];
        d2=mapa[(i+1)*s+j];
        d3=mapa[(i+1)*s+j+1];
    }
    return g1+g2+g3+l+d+d1+d2+d3;
}
void GameOL::update()
{
    std::vector<int> novi(r*s);
    novi=mapa;
    for(int i=0;i<r; i++)
        for(int j=0; j<s; j++)
    {
        if(broj_susjeda(i,j)<=1)novi[i*s+j]=0;
        else if(broj_susjeda(i,j)>=4)novi[i*s+j]=0;
        else if((broj_susjeda(i,j)==2 || broj_susjeda(i,j)==3))novi[i*s+j]=1;
        else if(mapa[i*s+j]==0 || broj_susjeda(i,j)==3) novi[i*s+j]=1;
        else continue;
    }
    mapa=novi;
}

void GameOL::print() const
{
    for(int i=0;i<r*s;i++)
    {
        if(i%s==0)std::cout << std::endl << mapa[i];
        else std::cout << mapa[i];
    }
}

void GameOL::init(std::string const & file_name)
{
    std::ifstream f;
    f.open(file_name.c_str());
    std::string str;
    f >> r >> s;
    int i=0;
    mapa.resize(200);
    std::getline(f, str);   //da dovrsimo prvu liniju
    for(int i=0;i<r*s;i++)mapa[i]=0;
    std::cout << r << " " << s << std::endl;
    while(std::getline(f,str))
    {
        for(int j=0;(j<str.size() || j<s); j++)
        {
            if(str[j]=='*') mapa[i+j]=1;
        }
        i+=s;
    }
}
