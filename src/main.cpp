#include <stdio.h>
#include "LinkedList.hpp"

int main()
{
    Prijava p1(1, "Marko", "Lenovo laptop1", "ne radi ekran", "2025-11-10", 5, "na cekanju");
    //p1.ispisiPrijavu();
    Prijava p2(2, "Markoo", "Lenovo laptop2", "ne radi tastatura", "2025-12-10", 5, "zavrsena");
    Prijava p3(3, "Markooo", "Lenovo laptop3", "ne radi zvucnik", "2025-12-09", 5, "na cekanju");
    LinkedList lista;
    lista.dodaj(p1);
    lista.dodaj(p2);
    lista.dodaj(p3);
    lista.ispisiSve();
    lista.ispisiSvePoDatumu("2025-11-11", "2025-12-09");
    lista.ispisiSvePoStatusu("zavrsena");
    return 0;
}