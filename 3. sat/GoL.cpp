#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>



class GameOL{
  public:
    GameOL();
    ~GameOL();
    void init(std::string const & file_name);
    void print() const;
    void print(std::string const &  file_name) const;
    void update();
  private:
    // broj  ivih susjeda danog elementa (i,j)
    int  br_susjeda(int i, int j) const;
    char **polje;
    int redci, stupci;
};

GameOL::GameOL()
{
    redci = stupci = 0;
}
GameOL::~GameOL()
{
    for(int i=0; i<redci; i++)
        std::free(polje[i]);
    std::free(polje);
}
void GameOL::init(std::string const & file_name)
{
    std::ifstream myfile;
    myfile.open(file_name.c_str());
    myfile>>redci;
    myfile>>stupci;

    polje = (char**)malloc(redci * sizeof(char*));
    for(int i=0; i<redci; i++)
        polje[i] = (char*)malloc(stupci*sizeof(char));

    char c;
    for(int i=0; i<redci; i++)
        for(int j=0; j<stupci; j++)
            myfile.get(polje[i][j]);

    myfile.close();
}



int main(int argc, char * argv[])
{
  // ucitaj ulazno stanje iz datoteke. Datoteka je pocetno_stanje.txt
  // ili je zadana argumentom komandne linije
  std::string input_file("pocetno_stanje.txt");
  if(argc > 1)
    input_file = argv[1];

  GameOL gol;  // defaultni konstruktor

  // Inicijaliziraj Game Of Live objekt s pocetnim stanjem
  // koje je zadano u datoteci input_file
  gol.init(input_file);
  // iscrtaj pocetno stanje
  gol.print();

  while( user_continue() )
  {
    gol.update();  // prijelaz automata u novo stanje
    gol.print();
    std::cout << "Next step ? ";
  }
  // ispisi zavrsno stanje u datoteku
  gol.print("zavrsno_stanje.txt");

  return 0;
}
