#pragma once
#include "Node.hpp"

class Stack
{
private:
    Node *topOfStack;
    int size;

public:
    Stack();
    int getSize()const;
    bool isEmpty()const;
    Prijava *peek()const;
    void push(Prijava prijava);
    void pop(Prijava &prijava);
    ~Stack();
};