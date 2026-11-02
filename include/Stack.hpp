#pragma once
#include "Node.hpp"

class Stack
{
private:
    Node *topOfStack;
    int size;

public:
    Stack();
    int getSize();
    bool isEmpty();
    Prijava *peek();
    void push(Prijava prijava);
    void pop(Prijava &prijava);
    ~Stack();
};