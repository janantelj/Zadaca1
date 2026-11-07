<style>
  body {

    font-size: 11.5px;
    line-height: 1.35;

  }
  h1 { font-size: 16px; margin-bottom: 6px; }
  h3 { font-size: 13px; margin-top: 10px; margin-bottom: 4px; }
  p, ul { margin-top: 2px; margin-bottom: 6px; }
  li { margin-bottom: 3px; }

  pre, code, .hljs {

    page-break-inside: auto !important;
    break-inside: auto !important;

    white-space: pre-wrap !important;
    word-wrap: break-word !important;
    display: block !important;

}

/* Rešava problem kada je kod unutar liste ili tabele */
li pre, td pre {

    page-break-inside: auto !important;
    break-inside: auto !important;

}
</style>

# Konzolna aplikacija za vođenje evidencije prijava kvarova u servisnom centru

U okviru ovog projekta implementirana je konzolna aplikacija u programskom jeziku C++ koja simulira prijem i obradu prijava kvarova u servisnom centru. Sistem omogućava vođenje kompletne evidencije kvarova, automatsko dodjeljivanje identifikatora, raspoređivanje zahtjeva prema stepenu hitnosti, obradu po prioritetu, istorijat obrada sa mogućnošću poništavanja (Undo), kao i pretragu i filtriranje prijava prema datumu. Aplikacija je razvijena sa fokusom na samostalnu implementaciju osnovnih struktura podataka (jednostruko ulančana lista, prioritetni red i stek). U skladu sa zahtjevima zadatka, nisu korištene gotove strukture iz Standardne biblioteke, već su sve strukture isprogramirane od nule kroz dinamičko upravljanje memorijom, pokazivače i principe objektno-orijentisanog programiranja uz poštovanje separacije odgovornosti.

### Strukture podataka

Projekat je podijeljen u nekoliko logičkih cjelina (modula) radi poštovanja principa enkapsulacije i jedinstvene odgovornosti:

* **Prijava:** Klasa koja modeluje sam kvar sa svim potrebnim podacima (ID, ime korisnika, naziv uređaja, opis kvara, datum prijema, hitnost i status).
* **Node:** Čvor jednostruko ulančanih struktura koji sadrži objekat prijave i pokazivač na sljedeći čvor.
* **LinkedList:** Predstavlja bazu podataka u memoriji i čuva kompletnu evidenciju servisa. Posjeduje pokazivače na glavu (head) i rep (head), što omogućava dodavanje novih prijava na kraj liste u $O(1)$ složenosti bez prolaska kroz listu.
* **PriorityQueue:** Prioritetni red koji sadrži samo prijave koje su na čekanju. Prilikom umetanja prijave se automatski slažu po hitnosti (od 10 prema 1), dok se pri istoj hitnosti poštuje redoslijed prijema (ranije pristigla prijava ima prednost, a kako se ID dodjeljuje automatski, to je bas ona prijava koja ima manji ID).
* **Stack:** Struktura sa LIFO pristupom koja služi kao istorija obrada unutar trenutne sesije programa, odnosno u trenutnom izvrsenju programa. Koristi se za realizaciju povratka (Undo) posljednje obrađene prijave nazad u red čekanja, gdje se ona dodaje po kriterijumima po kojima je i prvi put bila dodana.
* **fileIO:** Odvojen modul sa funkcijama za učitavanje podataka iz datoteke prijave.txt na početku i trajno snimanje ažurirane liste na disku, u istoj datoteci, prilikom zatvaranja programa.

### Analiza vremenske složenosti i moguće optimizacije

* **Dodavanje prijave:** Upis u glavnu listu (evidenciju) ima složenost $O(1)$, zbog atributa tail, koji je pokazivač na kraj liste, a umetanje u prioritetni red $O(N)$ jer se prolaskom kroz red traži odgovarajuće mjesto po hitnosti. Pošto imamo fiksan i mali broj prioriteta (samo cijeli brojevi od 1 do 10), red je moguće dodatno optimiyovati primjenom tzv. *Bucket Queue* strukture. To znači da bi red enkapsulirao niz od 10 pokazivača, pri čemu je niz[i] pokazivač na kraj (posljednji element) sekcije liste koja sadrži prijave prioriteta i+1, i važi $i \in \{0, 1, ..., 9\}$. Utom slučaju umetanje nove prijave bilo bi **$O(1)$**, jer bi se prijava na osnovu prioriteta direktno kačila na kraj odgovarajućeg dijela (čime bi automatski bio ispoštovan i redoslijed dolaska). Tada bi vađenje najhitnije prijave zahtijevalo najviše 10 provjera u nizu, što predstavlja fiksno vrijeme, odnosno  složenost **$O(1)$**. 
* **Obrada naredne prijave:** Uklanjanje sa početka prioritetnog reda je $O(1)$, stavljanje na vrh steka $O(1)$, dok je pronalaženje i izmjena statusa u evidenciji $O(N)$.
* **Poništavanje obrade (Undo):** Skidanje sa steka je $O(1)$, a ponovno vraćanje u red $O(N)$.
* **Pretraga po ID-ju:** Složenost za ovu opciju je $O(N)$, uz prekid petlje čim se naiđe na veći identifikator, dakle, neće se bespotrebno iterirati kroz cijelu listu.
* **Filtriranje po opsegu datuma:** Izdvajanje prijava koje su primljene u servis u zadatom opsegu datuma u pomoćni niz pokazivača traje $O(N)$, a sortiranje tog podskupa pomoću Selection Sort algoritma iznosi $O(K^2)$, gdje je $K$ broj pronađenih prijava u tom intervalu. Odnosno, u memoriji se rezerviše niz kapaciteta koji odgovara najgorem slučaju, ali se sortira samo frakcija niza koja se popuni pri izdvajanju odgovarajućih prijava.

### Rezultati testiranja

Aplikacija je testirana kroz simulaciju svih funkcionalnosti na dva nezavisna primjera:
1. Zvanični skup podataka sa Moodle stranice (prijave.txt sa 20 unosa).
2. Sopstveni testni fajl sa 5 unosa (moje_prijave.txt).
U oba slučaja potvrđeno je ispravno rukovanje graničnim slučajevima (poziv poništavanja kada je stek prazan, pretraga nepostojećeg identifikatorai opseg datuma bez rezultata).

<br>

<p align="right">
<b>Jana Antelj, 1178/25</b>
</p>

<br>
<br>

### Prilog: Logovi simulacije (datoteka prijave.txt sa Moodle stranice)

```text
Ucitano je 20 prijava iz evidencije. Broj prijava sa statusom 'na čekanju je' 15.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 3
Nije moguce izvrsiti undo, nema više obrada za poništavanje.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 2
Prijava sa ID brojem 1 je uspješno obrađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 2
Prijava sa ID brojem 13 je uspješno obrađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 3
Obrada prijave sa ID brojem 13 je uspješno poništena

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 1
Unesite ime korisnika: Test korisnik
Unesite naziv uređaja: Test uredjaj
Unesite kratak opis kvara: Test kvar
Unesite datum prijema u formatu GGGG-MM-DD: 2026-10-18
Unesite hitnost popravke (1-10): 10
Prijava sa ID brojem 21 je uspjesno dodata.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 2
Unesite ID broj prijave: 21
Prijava sa ID brojem 21 je uspješno pronađena:
21;Test korisnik;Test uredjaj;Test kvar;2026-10-18;10;na čekanju

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 2
Unesite ID broj prijave: 999
Prijava sa ID brojem 999 nije pronađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 3
Izaberite status: 
 (1) Na čekanju
 (2) Završena
2
Prikaz svih prijava sa statusom završena:
1;Marko Petrović;Laptop Lenovo ThinkPad;Uređaj se ne uključuje;2026-10-12;10;završena
2;Ana Jovanović;Štampač HP LaserJet;Papir se zaglavljuje pri štampanju;2026-10-12;5;završena
5;Stefan Ilić;Mobilni telefon Samsung;Baterija se brzo prazni;2026-10-14;3;završena
9;Luka Stanković;Skener Canon;Skener nije prepoznat na računaru;2026-10-16;4;završena
15;David Knežević;Monitor LG;Ekran ostaje taman nakon uključivanja;2026-10-21;8;završena
19;Nemanja Milićević;Ruter Asus;Bežična mreža nije dostupna;2026-10-26;7;završena

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 5
Unesite početni datum (GGGG-MM-DD):2026-10-12
Unesite krajnji datum (GGGG-MM-DD):2026-10-14
Prikaz svih prijava u sistemu sa datumom prijema izmedju 2026-10-12 i 2026-10-14 sortirano rastuce po datumu, a zatim po ID broju: 
1;Marko Petrović;Laptop Lenovo ThinkPad;Uređaj se ne uključuje;2026-10-12;10;završena
2;Ana Jovanović;Štampač HP LaserJet;Papir se zaglavljuje pri štampanju;2026-10-12;5;završena
3;Nikola Savić;Monitor Dell;Slika povremeno treperi;2026-10-13;4;na čekanju
4;Jelena Kovačević;Desktop računar;Računar se samostalno gasi;2026-10-13;9;na čekanju
5;Stefan Ilić;Mobilni telefon Samsung;Baterija se brzo prazni;2026-10-14;3;završena
6;Milica Đurić;Ruter TP-Link;Veza se prekida više puta dnevno;2026-10-14;8;na čekanju

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 0
 ```

### Prilog: Logovi simulacije (datoteka moje_prijave.txt)

```text
Ucitano je 5 prijava iz evidencije. Broj prijava sa statusom 'na čekanju je' 4.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 3
Nije moguce izvrsiti undo, nema više obrada za poništavanje.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 2
Prijava sa ID brojem 2 je uspješno obrađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 2
Prijava sa ID brojem 3 je uspješno obrađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 3
Obrada prijave sa ID brojem 3 je uspješno poništena

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 1
Unesite ime korisnika: Test korisnik
Unesite naziv uređaja: Test uredjaj
Unesite kratak opis kvara: test kvar
Unesite datum prijema u formatu GGGG-MM-DD: 2026-10-18
Unesite hitnost popravke (1-10): 10
Prijava sa ID brojem 6 je uspjesno dodata.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 2
Unesite ID broj prijave: 6
Prijava sa ID brojem 6 je uspješno pronađena:
6;Test korisnik;Test uredjaj;test kvar;2026-10-18;10;na čekanju

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 2
Unesite ID broj prijave: 999
Prijava sa ID brojem 999 nije pronađena.

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 4

----------- PREGLED I PRETRAGA -----------
 (1) Prikaz svih prijava
 (2) Pronalaženje prijave prema ID broju
 (3) Prikaz prijava po statusu
-------------------------------------------
Unesite izbor: 3
Izaberite status: 
 (1) Na čekanju
 (2) Završena
2
Prikaz svih prijava sa statusom završena:
2;Elena Vranic;Maticna ploca Asus;Ne prepoznaje RAM memoriju;2026-11-02;9;završena
4;Milena Topic;SSD Kingston;Sistem ne vidi particiju;2026-11-03;4;završena

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 5
Unesite početni datum (GGGG-MM-DD):2026-11-01
Unesite krajnji datum (GGGG-MM-DD):2026-11-03
Prikaz svih prijava u sistemu sa datumom prijema izmedju 2026-11-01 i 2026-11-03 sortirano rastuce po datumu, a zatim po ID broju: 
1;Igor Simic;Graficka karta RTX 3060;Pregrijavanje i pad fps-a;2026-11-01;8;na čekanju
2;Elena Vranic;Maticna ploca Asus;Ne prepoznaje RAM memoriju;2026-11-02;9;završena
3;Bojan Nedic;Napajanje Seasonic;Cuje se zujanje i pucketanje;2026-11-02;9;na čekanju
4;Milena Topic;SSD Kingston;Sistem ne vidi particiju;2026-11-03;4;završena

==================== MENI ====================
 (1) Dodavanje nove prijave
 (2) Obrada naredne prijave
 (3) Poništavanje prethodne obrade (Undo)
 (4) Pregled i pretraga prijava
 (5) Filtriranje prijava po opsegu datuma
 (0) Kraj rada i čuvanje evidencije
==============================================
Unesite broj opcije: 0
```
