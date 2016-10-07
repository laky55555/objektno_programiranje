#include <vector>
#include <string>


#ifndef __GAME_OF_LIFE_H_INCLUDED__
#define __GAME_OF_LIFE_H_INCLUDED__


class GameOL{
  public:
    GameOL();
    ~GameOL();
    void init(std::string const & file_name);
    void print() const;
    void print(std::string const &  file_name) const;
    void update();
  private:
    // broj živih susjeda danog elementa (i,j)
    int  broj_susjeda(int i, int j) const;
    std::vector<int> mapa;
    int r,s;

};
#endif
