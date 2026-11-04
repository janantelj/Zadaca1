#include "Stack.hpp"
#include <iostream>

Stack::Stack()
{
    this->topOfStack = nullptr;
    int size = 0;
}

int Stack::getSize()const
{
    return this->size;
}

bool Stack::isEmpty()const
{
    return (this->size == 0);
}

Prijava *Stack::peek()const
{
    return this->topOfStack->getPrijava();
}

void Stack::push(Prijava prijava)
{
    Node *newNode = new Node();
    newNode->setNext(this->topOfStack);
    newNode->setPrijava(prijava);
    this->topOfStack = newNode;
    this->size++;
}

void Stack::pop(Prijava &prijava)
{
    if (isEmpty())
    {
        std::cout << "Nije moguce uraditi undo(stack je prazan)" << std::endl;
        return;
    }
    prijava = *(this->topOfStack->getPrijava());
    Node *del = this->topOfStack; // Node za brisanjee
    this->topOfStack = this->topOfStack->getNext();
    delete del;
    this->size--;
}

Stack::~Stack()
{
    Node *del = nullptr;
    for (int i = 0; i < this->size; i++)
    {
        del = this->topOfStack;
        this->topOfStack = this->topOfStack->getNext();
        delete del;
    }
}