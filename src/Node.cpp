#include "Node.hpp"

Node::Node()
{
    this->next = nullptr;
}

Node::Node(Prijava prijava)
{
    this->setPrijava(prijava);
    this->next = nullptr;
}

Prijava *Node::getPrijava()
{
    return &(this->prijava);
}

void Node::setPrijava(Prijava prijava)
{
    this->prijava = prijava;
}

Node *Node::getNext()
{
    return this->next;
}

void Node::setNext(Node *next)
{
    this->next = next;
}

Node::~Node()
{
    // this->next = nullptr
}