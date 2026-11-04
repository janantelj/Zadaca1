#pragma once
#include "Prijava.hpp"

class Node
{
private:
    Prijava prijava;
    Node *next;

public:
    Node();
    Node(Prijava prijava);
    Prijava *getPrijava();
    void setPrijava(Prijava prijava);
    Node *getNext()const;
    void setNext(Node *next);
    ~Node();
};