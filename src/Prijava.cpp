#include "Prijava.hpp"
#include <iostream>

Prijava::Prijava()
{
    this->id = -1;
    this->hitnostPopravke = 0;
}

// ASSUME podaci su validni (datum je u formatu GGGG-MM-DD, hitnost u opsegu 1-10)
Prijava::Prijava(int id, std::string imeKorisnika, std::string nazivUredjaja, std::string opisKvara, std::string datumPrijema, int hitnostPopravke, std::string status)
{
    this->id = id;
    this->imeKorisnika = imeKorisnika;
    this->nazivUredjaja = nazivUredjaja;
    this->opisKvara = opisKvara;
    this->datumPrijema = datumPrijema;
    this->hitnostPopravke = hitnostPopravke;
    this->status = status;
}

int Prijava::getId()const
{
    return this->id;
}

void Prijava::setId(int id)
{
    this->id = id;
}

std::string Prijava::getImeKorisnika()const
{
    return this->imeKorisnika;
}

void Prijava::setImeKorisnika(std::string imeKorisnika)
{
    this->imeKorisnika = imeKorisnika;
}

std::string Prijava::getNazivUredjaja()const
{
    return this->nazivUredjaja;
}

void Prijava::setNazivUredjaja(std::string nazivUredjaja)
{
    this->nazivUredjaja = nazivUredjaja;
}

std::string Prijava::getOpisKvara()const
{
    return this->opisKvara;
}

void Prijava::setOpisKvara(std::string opisKvara)
{
    this->opisKvara = opisKvara;
}

std::string Prijava::getDatumPrijema()const
{
    return this->datumPrijema;
}

void Prijava::setDatumPrijema(std::string datumPrijema)
{
    this->datumPrijema = datumPrijema;
}

int Prijava::getHitnostPopravke()const
{
    return this->hitnostPopravke;
}

void Prijava::setHitnostPopravke(int hitnostPopravke)
{
    this->hitnostPopravke = hitnostPopravke;
}

std::string Prijava::getStatus()const
{
    return this->status;
}

void Prijava::setStatus(std::string status)
{
    this->status = status;
}

void Prijava::ispisiPrijavu()const
{
    // Format: 19;Nemanja Milićević;Ruter Asus;Bežična mreža nije dostupna;2026-10-26;7;završena
    std::cout << this->id << ";" << this->imeKorisnika << ";" << this->nazivUredjaja << ";" << this->opisKvara << ";" << this->datumPrijema << ";" << this->hitnostPopravke << ";" << this->status << std::endl;
}