#pragma once
#include "Node.hpp"
#include "Prijava.hpp"
#include <string>
#include <iostream>

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList();
    int getSize();
    Node *getHead();
    Node *getTail();
    void dodaj(Prijava prijava);
    Prijava *pretraziPoId(int id);
    void ispisiSve();
    void ispisiSvePoStatusu(std::string status);
    void ispisiSvePoDatumu(std::string odDatuma, std::string doDatuma);
    ~LinkedList();
};