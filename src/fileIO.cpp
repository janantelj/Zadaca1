#include "fileIO.hpp"
#include <iostream>
#include <fstream>
#include <string>

void readFile(LinkedList &list, PriorityQueue &queue, int &maxId)
{
    std::ifstream file("prijave.txt");

    if (!file.is_open())
    {
        std::cout << "Neuspjesno otvaranje fajla." << std::endl;
        return;
    }

    // ASSUME format: 1;Marko Petrović;Laptop Lenovo ThinkPad;Uređaj se ne uključuje;2026-10-12;10;na čekanju
    std::string idStr, ime, uredjaj, opis, datum, hitnostStr, status;
    Prijava prijava;
    while (std::getline(file, idStr, ';'))
    {
        prijava.setId(stoi(idStr));
        std::getline(file, ime, ';');
        prijava.setImeKorisnika(ime);
        std::getline(file, uredjaj, ';');
        prijava.setNazivUredjaja(uredjaj);
        std::getline(file, opis, ';');
        prijava.setOpisKvara(opis);
        std::getline(file, datum, ';');
        prijava.setDatumPrijema(datum);
        std::getline(file, hitnostStr, ';');
        prijava.setHitnostPopravke(stoi(hitnostStr));
        std::getline(file, status);
        prijava.setStatus(status);

        list.dodaj(prijava);
        if (prijava.getId() > maxId)
            maxId = prijava.getId();
        if (status == "na čekanju")
            queue.enqueue(prijava);
    }
}

void writeFile(const LinkedList &list)
{
    std::ofstream file("prijave.txt");
    if (!file.is_open())
    {
        std::cout << "Neuspjesno otvaranje fajla." << std::endl;
        return;
    }

    // ASSUME format: 1;Marko Petrović;Laptop Lenovo ThinkPad;Uređaj se ne uključuje;2026-10-12;10;na čekanju
    Node *tmp = list.getHead();
    for (int i = 0; i < list.getSize(); i++)
    {
        file << tmp->getPrijava()->getId() << ";"
             << tmp->getPrijava()->getImeKorisnika() << ";"
             << tmp->getPrijava()->getNazivUredjaja()
             << ";" << tmp->getPrijava()->getOpisKvara() << ";"
             << tmp->getPrijava()->getDatumPrijema() << ";"
             << tmp->getPrijava()->getHitnostPopravke() << ";"
             << tmp->getPrijava()->getStatus() << "\n";
        tmp = tmp->getNext();
    }
}
