#include <iostream>

#include "poruka.h"


// Pomoæna funkcija za ispis
void ispis(Poruka const & poruka){
    std::cout << "[ Poruka: " << poruka.sadrzaj()
              << ": Kategorije: " << poruka.kategorije()
              << " ]\n";
 }

 // generiranje poruke
Poruka prazna_poruka(Kategorija& kat){
     Poruka tmp("b.o.");
     tmp.dodaj(kat);
     return tmp;
}

int main()
{
    // Definiramo 3 kategorije, no moguæ je proizvoljan broj kategorija
    Kategorija redovno("Redovno");
    Kategorija vazno("Vazno");
    Kategorija hitno("Hitno");


    // Definiramo nekoliko poruka
    Poruka p1("New USB device found");
    Poruka p2("Manufacturer: Broadcom Corp");
    Poruka p3("[sda] Attached SCSI disk");
    Poruka p4("Disk quotas exceeded");
    Poruka p5("Kernel panic");

    // Dodajmo poruke u neke kategorije
    p1.dodaj(redovno); p1.dodaj(vazno);
    p2.dodaj(redovno);
    p3.dodaj(redovno); p3.dodaj(vazno);
    p4.dodaj(redovno); p4.dodaj(vazno); p4.dodaj(hitno);
    p5.dodaj(vazno); p5.dodaj(hitno);

    // Ispis radi kontrole
    std::cout << "Poruke:\n";
    ispis(p1);
    ispis(p2);
    ispis(p3);
    ispis(p4);
    ispis(p5);
    // test uklanjanja
    p1.ukloni(vazno);
    p4.ukloni(redovno);

    // Ispis radi kontrole
    std::cout << "Modificirane poruke:\n";
    ispis(p1);
    ispis(p4);

    Poruka p6{p5};
    std::cout << "CCtor:\n";
    ispis(p6);

    p6 = p1;
    p5 = p5;
    std::cout << "OP\n";
    ispis(p6);
    ispis(p5);

    p6 = prazna_poruka(redovno);
    std::cout << "M-OP\n";
    ispis(p6);

    Poruka* pp7 = new Poruka("Watching system buttons");
    pp7->dodaj(redovno);
    Poruka p8(std::move(*pp7));
    std::cout << "M-Ctor\n";
    ispis(p8);
    delete pp7;

    return 0;
}
