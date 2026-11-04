#pragma once
#include "Node.hpp"

class PriorityQueue
{
private:
    Node *head;
    int size;

public:
    PriorityQueue();
    int getSize()const;
    bool isEmpty()const;
    Node *getHead()const;
    void enqueue(Prijava prijava);
    void dequeue(Prijava &prijava);
    ~PriorityQueue();
};