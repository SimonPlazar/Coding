# strežnik

./server

Imena spremenljivk omejena na 128 znakov, velikost spremenljivke omejena na 4096 znakov.

# odjemalec
./client <ukaz> <ime spremenljivke> [-t <milisekunde> -d <milisekunde>]

Parametra <ukaz> in <ime spremenljivke> sta pozicijska (najprej ukaz, nato ime). Zastavice so lahko na poljubnem mestu.


## ukazi
Možni ukazi:

- SET
- UNSET
- GET
- WAIT

### SET

Nastavi vrednost spremenljivke.
Novo vrednost prebere z standardnega vhoda in jo zapiše v spremenljivko.
Izbran 'delay' čas je neodvisen od dolžina branja z standardnega vhoda.
Izbran 'timeout' lahko prekine branje z standardnega vhoda.
Z standardnega vhoda prebere največ maksimalno dolžino podatkov spremenljivke.

### UNSET

Izbriše spremenljivko z strežnika.

### GET

Pridobi vrednost spremenljivke, jo izpiše na standardni izhod.

### WAIT

Počaka na spremembo spremenljivke - operacijo SET ali UNSET nad njo.
Kot status vrne operacijo, ki jo je dočakal.

## ime spremenljivke

128 znakov/zlogov, izpisljivi znaki

## zatavica -t (timeout)

Čas prekinitve v milisekundah, če bi ukaz blokiral izvajanje. Brez zastavice 
program čaka, dokler strežnik ne vrne rezultata.

## zastavica -d (delay)

Čas trajanja izvedbe ukaza v milisekundah. Program prične izvajanje ukaza (poveze se z strežnikom, pošlje ukaz in pridobi dostop do spremenljivke), nato počaka tukaj podan čas, nato izvede operacijo in to sporoči strežniku. Brez zastavice se ukaz izvede kolikor hitro je mogoče.

## vrnjeni statusi odjemalca

0 - ukaz se je uspešno izvedel (SET, UNSET, GET)
1 - spremenljivka s tem imenom ne obstaja (UNSET, GET, WAIT)
2 - napaka pri ustvarjanju (SET)
3 - spremenljivka je bila nastavljena (WAIT je prejel SET)
4 - spremenljivka je bila izbrisana (WAIT je prejel UNSET)
5 - potekel je izbran timeout (SET, UNSET, GET)

## Testi za študentske naloge

- na različnih spremenljivkah lahko hkrati izvedemo vse ukaze (uporaba niti na strežniku)
- na isti spremenljivki:
    - ukaz SET mora počakati na vse druge SET, UNSET in GET ukaze 
    - ukaz GET mora počakati na SET, UNSET
    - ukaz WAIT se lahko izvede kadarkoli
    - ukaz WAIT mora počakati na izveden SET, USNET
