#pragma once
#include "Node.hpp"

class PriorityQueue
{
private:
    Node *head;
    int size;

public:
    PriorityQueue();
    int getSize();
    bool isEmpty();
    Node *getHead();
    void enqueue(Prijava prijava);
    void dequeue(Prijava &prijava);
    ~PriorityQueue();
};