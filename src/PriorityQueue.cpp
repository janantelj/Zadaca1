#include "PriorityQueue.hpp"
#include <iostream>

PriorityQueue::PriorityQueue()
{
    this->size = 0;
    this->head = nullptr;
}

int PriorityQueue::getSize()const
{
    return this->size;
}

bool PriorityQueue::isEmpty()const
{
    return (this->size == 0);
}

Node *PriorityQueue::getHead()const
{
    return this->head;
}

void PriorityQueue::enqueue(Prijava prijava)
{
    Node *newNode = new Node(prijava);
    Node *tmp = this->head;

    if (tmp == nullptr || (tmp->getPrijava()->getHitnostPopravke() < prijava.getHitnostPopravke() || (tmp->getPrijava()->getHitnostPopravke() == prijava.getHitnostPopravke() && tmp->getPrijava()->getId() > prijava.getId())))
    {
        newNode->setNext(tmp);
        this->head = newNode;
        this->size++;
        return;
    }

    while (tmp->getNext() != nullptr && (tmp->getNext()->getPrijava()->getHitnostPopravke() > prijava.getHitnostPopravke() ||
                                         (tmp->getNext()->getPrijava()->getHitnostPopravke() == prijava.getHitnostPopravke() && tmp->getNext()->getPrijava()->getId() < prijava.getId())))
        tmp = tmp->getNext();

    newNode->setNext(tmp->getNext());
    tmp->setNext(newNode);
    this->size++;
}

void PriorityQueue::dequeue(Prijava &prijava)
{
    if (isEmpty())
    {
        std::cout << "Nije moguce uzeti prijavu iz reda(red je prazan)." << std::endl;
        return;
    }
    prijava = *(this->head->getPrijava());
    this->size--;
    Node *del = this->head;
    this->head = this->head->getNext();
    delete del;
}

PriorityQueue::~PriorityQueue()
{
    Node *del;
    for (int i = 0; i < this->size; i++)
    {
        del = this->head;
        this->head = this->head->getNext();
        delete del;
    }
}
