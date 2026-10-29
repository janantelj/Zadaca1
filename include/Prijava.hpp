#pragma once
#include <string>

class Prijava{
    private:
        int id;
        std::string imeKorisnika;
        std::string nazivUredjaja;
        std::string opisKvara;
        std::string datumPrijema;
        int hitnostPopravke;
        std::string status;

    public:
        Prijava();
        Prijava(int id, std::string imeKorisnika, std::string nazivUredjaja, std::string opisKvara, std::string datumPrijema, int hitnostPopravke, std::string status);
        int getId();
        void setId(int id);
        std::string getImeKorisnika();
        void setImeKorisnika(std::string imeKorisnika);
        std::string getNazivUredjaja();
        void setNazivUredjaja(std::string nazivUredjaja);
        std::string getOpisKvara();
        void setOpisKvara(std::string opisKvara);
        std::string getDatumPrijema();
        void setDatumPrijema(std::string datumPrijema);
        int getHitnostPopravke();
        void setHitnostPopravke(int hitnostPopravke);
        std::string getStatus();
        void setStatus(std::string status);
        void ispisiPrijavu();
};