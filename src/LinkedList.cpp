#include "LinkedList.hpp"

LinkedList::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

Node *LinkedList::getHead()
{
    return this->head;
}

Node *LinkedList::getTail()
{
    return this->tail;
}

void LinkedList::dodaj(Prijava prijava)
{
    Node *newNode = new Node(prijava);
    if (this->size == 0)
    {
        this->head = this->tail = newNode;
    }
    else
    {
        this->tail->setNext(newNode);
        this->tail = newNode;
    }
    this->size++;
}

Prijava *LinkedList::pretraziPoId(int id)
{
    Node *tmp = this->head;
    while (tmp && tmp->getPrijava()->getId() <= id)
    {
        if (tmp->getPrijava()->getId() == id)
            return tmp->getPrijava();
        tmp = tmp->getNext();
    }
    return nullptr;
}

void LinkedList::ispisiSve()
{
    std::cout << "Prikaz svih prijava u sistemu: " << std::endl;
    Node *tmp = this->head;
    for (int i = 0; i < this->size; i++)
    {
        tmp->getPrijava()->ispisiPrijavu();
        tmp = tmp->getNext();
    }
}

// TODO dodati flag i neka funkcija ispisuje poruku ako nema nijedna prijava sad atim tatusom
void LinkedList::ispisiSvePoStatusu(std::string status)
{
    std::cout << "Prikaz svih prijava sa statusom " << status << ":" << std::endl;
    Node *tmp = this->getHead();
    if (status == "na cekanju")
    {
        for (int i = 0; i < this->size; i++)
        {
            if (tmp->getPrijava()->getStatus() == "na cekanju")
                tmp->getPrijava()->ispisiPrijavu();
            tmp = tmp->getNext();
        }
    }
    else if (status == "zavrsena")
    {
        for (int i = 0; i < this->size; i++)
        {
            if (tmp->getPrijava()->getStatus() == "zavrsena")
                tmp->getPrijava()->ispisiPrijavu();
            tmp = tmp->getNext();
        }
    }
    else
    {
        std::cout << "Status " << status << "nije validan. Validni statusi su: 'na cekanju' i 'zavrsena' " << std::endl;
    }
}

// TODO dodati flag i nek funkcija ispisuje poruku ako nema nijedan u datom opsegu
void LinkedList::ispisiSvePoDatumu(std::string odDatuma, std::string doDatuma)
{
    Node *tmp = this->getHead();
    int found = 0;
    Prijava **arr = new Prijava *[this->size];

    for (int i = 0; i < this->size; i++)
    {
        if (tmp->getPrijava()->getDatumPrijema() >= odDatuma && tmp->getPrijava()->getDatumPrijema() <= doDatuma)
        {
            arr[found] = tmp->getPrijava();
            found++;
        }
        tmp = tmp->getNext();
    }

    for (int i = 0; i < found; i++)
    {
        int best = i;
        for (int j = i + 1; j < found; j++)
        {
            if ((arr[j]->getDatumPrijema() <= arr[i]->getDatumPrijema()) || ((arr[j]->getDatumPrijema() == arr[i]->getDatumPrijema()) && arr[j]->getId() < arr[i]->getId()))
                best = j;
        }
        Prijava *tmp = arr[i];
        arr[i] = arr[best];
        arr[best] = tmp;
    }

    std::cout << "Prikaz svih prijava u sistemu sa datumom prijema izmedju " << odDatuma << " i " << doDatuma << " sortirano rastuce po datumu, a zatim po ID broju: " << std::endl;
    for (int i = 0; i < found; i++)
        arr[i]->ispisiPrijavu();

    delete[] arr;
}

LinkedList::~LinkedList()
{
    Node *tmp = this->head, *del = nullptr;
    for (int i = 0; i < this->size; i++)
    {
        del = tmp;
        tmp = tmp->getNext();
        delete (del);
    }
}