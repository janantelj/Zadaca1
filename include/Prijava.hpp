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
        int getId()const;
        void setId(int id);
        std::string getImeKorisnika()const;
        void setImeKorisnika(std::string imeKorisnika);
        std::string getNazivUredjaja()const;
        void setNazivUredjaja(std::string nazivUredjaja);
        std::string getOpisKvara()const;
        void setOpisKvara(std::string opisKvara);
        std::string getDatumPrijema()const;
        void setDatumPrijema(std::string datumPrijema);
        int getHitnostPopravke()const;
        void setHitnostPopravke(int hitnostPopravke);
        std::string getStatus()const;
        void setStatus(std::string status);
        void ispisiPrijavu()const;
};