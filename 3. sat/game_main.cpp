#include "game.h"
#include <iostream>
#include <string>

bool user_continue()
{
    std::string str;
    std::cin >> str;
    if(str=="DA") return 1;
    return 0;
}

int main(void)
{
  // uèitaj ulazno stanje iz datoteke. Datoteka je pocetno_stanje.txt
  // ili je zadana argumentom komandne linije
  std::string input_file("pocetno_stanje.txt");

  GameOL gol;  // defaultni konstruktor

  // Inicijaliziraj Game Of Live objekt s poèetnim stanjem
  // koje je zadano u datoteci input_file
  gol.init(input_file);
  // iscrtaj poèetno stanje
  gol.print();

  while( user_continue() )
  {
    gol.update();  // prijelaz automata u novo stanje
    gol.print();
    std::cout << "Next step ? ";
  }
  // ispiši završno stanje u datoteku
//  gol.print("zavrsno_stanje.txt");

  return 0;
}
