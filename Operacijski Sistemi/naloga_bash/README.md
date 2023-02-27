# Poganjalec poslov

## Navodila 

Napišite skripto pozeni_posle, ki v trenutni poti in podpoteh poišče vse posle in jih izvede.

Veljavni posli so bash skripte poimenovane po shemi 'posel_<ime\>.sh'. Ime je lahko poljuben niz, ki je del veljavnega imena zbirke (npr. vsebuje lahko presledke, ne more pa vsebovati znaka /). Vsak posel mora v prvi vrsti imeti komentar, ki pove, da so to bash skripte: '#!/bin/bash'.

Posli nimajo nastavljenega bita za izvajanje, pognati jih moramo eksplicitno z ukazom bash.

Zagon posameznega posla naj se izvede znotraj njegove poti.
To lahko dosežete tako, da si zapomnite izhodiščno delovno pot, nato se pomaknete v pot ciljnega posla, ga poženete, nato pa se pomaknete nazaj v izhodiščno pot.

Izhod posameznega posla naj se zapiše v 'posel_<ime\>.out' v isti poti kot sam posel.
V kolikor ta zbirka že obstaja, naj se vsebina prepiše.

Vsak posel bo na standardni izhod v zadnji vrstici izpisal 'Ok' kadar se je posel izvedel uspešno ali 'Fail' kadar se ni.
Skripta naj na koncu izpiše seznam neuspešnih poslov.

## Primeri zagonov

Primer preprostega zagona in izpisa:

```bash
$ find .
.
./A
./A/posel_p2.sh
./posel_p1.sh
$ bash ../scripts/pozeni_posle.sh
neuspesni posli:
./A/posel_p2.sh
$ find .
.
./posel_p1.out
./A
./A/posel_p2.sh
./A/posel_p2.out
./posel_p1.sh
```

## Kaj morate implementirati pri tej nalogi?

+ iskanje poslov za zagon
    + ne sme izbrati poslov, katerih ime se ne ujema s predpisano obliko
    + ne sme izbrati map, katerih ime se ujema z obliko
    + ne sme izbrati poslov, katerih prva vrstica ne vsebuje ustreznega komentarja
    + imena poslov lahko imajo presledke
    + poti lahko imajo presledke
+ zagon posla
    + zagon znotraj poti posla
    + izpis posla v ustrezno izhodno datoteko
    + preverjanje izhoda posla
+ izpis neuspešnih poslov


