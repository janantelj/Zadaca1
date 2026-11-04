#pragma once
#include "Node.hpp"
#include "Prijava.hpp"

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList();
    int getSize()const;
    Node *getHead()const;
    Node *getTail()const;
    void dodaj(Prijava prijava);
    Prijava *pretraziPoId(int id)const;
    void ispisiSve()const;
    void ispisiSvePoStatusu(std::string status)const;
    void ispisiSvePoDatumu(std::string odDatuma, std::string doDatuma)const;
    ~LinkedList();
};