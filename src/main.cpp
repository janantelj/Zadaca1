#include <windows.h>
#include <iostream>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "PriorityQueue.hpp"
#include "fileIO.hpp"

int main()
{
    SetConsoleOutputCP(CP_UTF8); // izlaz latinica
    SetConsoleCP(CP_UTF8);       // ulaz latinica
    LinkedList llist;
    PriorityQueue pqueue;
    Stack stack;
    int maxId = 0;
    readFile(llist, pqueue, maxId);
    std::cout << "Ucitano je " << llist.getSize() << " prijava iz evidencije. Broj prijava sa statusom 'na čekanju je' " << pqueue.getSize() << "." << std::endl;

    // MENU
    int flag = 1, izbor = -1;
    while (flag)
    {
        std::cout << "\n==================== MENI ====================\n";
        std::cout << " (1) Dodavanje nove prijave\n";
        std::cout << " (2) Obrada naredne prijave\n";
        std::cout << " (3) Poništavanje prethodne obrade (Undo)\n";
        std::cout << " (4) Pregled i pretraga prijava\n";
        std::cout << " (5) Filtriranje prijava po opsegu datuma\n";
        std::cout << " (0) Kraj rada i čuvanje evidencije\n";
        std::cout << "==============================================\n";
        std::cout << "Unesite broj opcije: ";
        std::cin >> izbor;
        std::cin.ignore();

        switch (izbor)
        {
        case 0:
        { // Kraj rada i cuvanje evidencije
            flag = 0;
            break;
        }

        case 1:
        { // Dodaj novu prijavu
            maxId++;
            Prijava novaPrijava;
            novaPrijava.setId(maxId);
            std::string imeKorisnika, nazivUredjaja, opisKvara, datumPrijema, hitnost, status;

            std::cout << "Unesite ime korisnika: ";
            std::getline(std::cin, imeKorisnika);
            novaPrijava.setImeKorisnika(imeKorisnika);

            std::cout << "Unesite naziv uređaja: ";
            std::getline(std::cin, nazivUredjaja);
            novaPrijava.setNazivUredjaja(nazivUredjaja);

            std::cout << "Unesite kratak opis kvara: ";
            std::getline(std::cin, opisKvara);
            novaPrijava.setOpisKvara(opisKvara);

            std::cout << "Unesite datum prijema u formatu GGGG-MM-DD: ";
            std::cin >> datumPrijema;
            novaPrijava.setDatumPrijema(datumPrijema);

            // ASSUME 1 <= hitnost <= 10
            std::cout << "Unesite hitnost popravke (1-10): ";
            std::cin >> hitnost;
            novaPrijava.setHitnostPopravke(stoi(hitnost));

            novaPrijava.setStatus("na čekanju");

            llist.dodaj(novaPrijava);
            pqueue.enqueue(novaPrijava);

            std::cout << "Prijava sa ID brojem " << maxId << " je uspjesno dodata." << std::endl;
            break;
        }

        case 2: // Obradi
        {
            if (pqueue.isEmpty())
            {
                std::cout << "Nema prijava sa statusom 'na čekanju'." << std::endl;
                break;
            }
            Prijava obradjena;
            pqueue.dequeue(obradjena);
            obradjena.setStatus("završena");
            Prijava *obradjenaUListi = llist.pretraziPoId(obradjena.getId());
            obradjenaUListi->setStatus("završena");
            stack.push(obradjena);
            std::cout << "Prijava sa ID brojem " << obradjena.getId() << " je uspješno obrađena." << std::endl;
            break;
        }
        case 3: // ponistavanje obrade
        {
            if (stack.isEmpty())
            {
                std::cout << "Nije moguce izvrsiti undo, nema više obrada za poništavanje." << std::endl;
                break;
            }
            Prijava vracena;
            stack.pop(vracena);
            vracena.setStatus("na čekanju");
            Prijava *vracenaUListi = llist.pretraziPoId(vracena.getId());
            vracenaUListi->setStatus("na čekanju");
            pqueue.enqueue(vracena);
            std::cout << "Obrada prijave sa ID brojem " << vracena.getId() << " je uspješno poništena" << std::endl;
            break;
        }
        case 4: // pregled i pretraga
        {
            std::cout << "\n----------- PREGLED I PRETRAGA -----------\n";
            std::cout << " (1) Prikaz svih prijava\n";
            std::cout << " (2) Pronalaženje prijave prema ID broju\n";
            std::cout << " (3) Prikaz prijava po statusu\n";
            std::cout << "-------------------------------------------\n";
            std::cout << "Unesite izbor: ";
            int izbor4;
            std::cin >> izbor4;

            switch (izbor4)
            {
            case 1: // prikaz svih prijava
            {
                llist.ispisiSve();
                break;
            }
            case 2: // pretrazi po ID
            {
                int id;
                std::cout << "Unesite ID broj prijave: ";
                std::cin >> id;

                Prijava *nadjena = llist.pretraziPoId(id);
                if (!nadjena)
                {
                    std::cout << "Prijava sa ID brojem " << id << " nije pronađena." << std::endl;
                    break;
                }
                std::cout << "Prijava sa ID brojem " << id << " je uspješno pronađena:" << std::endl;
                nadjena->ispisiPrijavu();
                break;
            }
            case 3: // prikaz po statusu
            {
                int status;
                std::cout << "Izaberite status: " << std::endl;
                std::cout << " (1) Na čekanju\n";
                std::cout << " (2) Završena\n";
                std::cin >> status;

                if (status == 1)
                {
                    llist.ispisiSvePoStatusu("na čekanju");
                }

                else if (status == 2)
                {
                    llist.ispisiSvePoStatusu("završena");
                }

                else
                {
                    std::cout << "Niste unijeli validan status. Povratak na glavni meni..." << std::endl;
                }
                break;
            }
            default:
            {
                std::cout << "Izbor nije validan. Povratak na glavni meni..." << std::endl;
                break;
            }
            }
            break;
        }
        case 5: // filtriranje
        {
            std::string odDatuma, doDatuma;
            std::cout << "Unesite početni datum (GGGG-MM-DD):";
            std::cin >> odDatuma;
            std::cout << "Unesite krajnji datum (GGGG-MM-DD):";
            std::cin >> doDatuma;
            llist.ispisiSvePoDatumu(odDatuma, doDatuma);
            break;
        }
        default:
        {
            std::cout << "Izbor nije validan. Povratak na glavni meni..." << std::endl;
            break;
        }
        }
    }

    writeFile(llist);
    return 0;
}