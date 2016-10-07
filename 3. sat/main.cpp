#include <iostream>
#include "red.h"

void help()
{
  std::cout << std::endl
<< "Program cita jednu komandu po liniji ulaza. Na primjer" << std::endl
<< "ako je komanda S onda program vraca celo reda." << std::endl
<< std::endl
<< " Naredbe: :" << std::endl
<< "A - Dodaj sljedeci znak u red." << std::endl
<< "S - Prikazi celo reda." << std::endl
<< "R - Izbaci i prikazi celo reda." << std::endl
<< "# - Trenutna duljina reda.  " << std::endl
<< "C - Obrisi red." << std::endl
<< "P - Ispisi red. " << std::endl
<< "H - Ispisi ovaj ekran." << std::endl
<< "Q - Izlaz" << std::endl;
}


int dodaj_novi(Queue &red)
{
    QueueEntry znak;
    std::cout << "Upisite sto zelite dodati:" <<std::endl;
    std::cin >> znak;
    if (red.push_back(znak) == Queue::overflow)
    {
        std::cout << "Nema mjesta" << std::endl;
        return 0;
    }
    return 1;
}

int celo(Queue &red)
{
    QueueEntry znak;
    if (red.front(znak) == Queue::underflow)
    {
        std::cout << "Nema elemenata" << std::endl;
        return 0;
    }
    std::cout << "Na celu reda se nalazi: " << znak <<std::endl;
    return 1;
}

int izbaci_i_celo(Queue &red)
{
    red.pop_front();
    celo(red);
    return 1;

}

int trenutna_duljina(Queue &red)
{
    std::cout << "Trenutna duljina reda je: " << red.size() <<std::endl;
    return 1;
}

int obrisi_red(Queue &red)
{
    while(!red.empty())
        red.pop_front();
    return 1;
}

int ispisi_red(Queue &red)
{
    if (red.empty())
    {
        std::cout << "Red je prazan." << std::endl;
        return 1;
    }
    for(int i=0; i<red.size(); i++)
    {
        QueueEntry vrh;
        red.front(vrh);
        std::cout << i+1 << ". u redu: " << vrh << std::endl;
        red.pop_front();
        red.push_back(vrh);
    }
    return 1;
}

int izlaz()
{
    return 1;
}




int do_command(char znak, Queue &red)
{
    int kraj=1;
    switch( znak )
		{
			case 'A': dodaj_novi(red); break;
			case 'S': celo(red); break;
			case 'R': izbaci_i_celo(red); break;
			case '#': trenutna_duljina(red); break;
			case 'C': obrisi_red(red); break;
			case 'P': ispisi_red(red); break;
			case 'H': help(); break;
			case 'Q': izlaz(); kraj = 0; break;
		}
    return kraj;
}

char get_command()
{
    char znak;
    std::cout << "Upisi zeljenu naredbu" << std::endl;
    std::cin >> znak;
    return znak;

}

int main()
{
  Queue red;
  help();
  while (do_command(get_command(), red));

  return 0;
}
