Gonilnik - osnovno
Napišite modul za jedro Linux v programskem jeziku C, ki implementira branje podatkov iz RTC modula in njihov izpis v tok sporočil iz jedra (dmegs).

Implementacija naj upošteva naslednje zahteve:

Struktura projekta:

Projekt naj vsebuje naslednje zbirke:

Makefile - vsebuje naj pravila "all", "build", "load", "unload" in "clean"
spo_module.c - vsebuje naj implementacijo vašega modula
spo_module.h - vsebuje naj zaglavje vašega modula
Prevajanje projekta:

Pripravite zbirko "Makefile", ki bo vsebovala pravila za prevajanje projekta:

vsebuje naj pravilo "all"
pravilo kliče drugi pravili "build"
vsebuje naj pravilo "build"
pravilo iz podanih zbirk prevede modul
ime zbirke prevedenega programa naj bo spo_module.ko
pravilo ne sme naložiti prevedenega modula
vsebuje naj pravilo "load"
pravilo naj naloži preveden modul
pravilo naj ustvari znakovno napravo v "/dev/spo_driver_1", če tega ne naredite že v samem modulu
Pazite na uporabo pravilne "master" številke - kot je zapisana v /proc/devices
predpostavite, da imate administrativne privilegije
vsebuje naj pravilo "unload"
pravilo naj izvrže preveden modul
pravilo naj odstrani znakovno napravo v "/dev/spo_driver_1", če tega ne naredite že v samem modulu
predpostavite, da imate administrativne privilegije
vsebuje naj pravilo "clean"
pravilo naj odstrani vse ustvarjene zbirke
Delo z modulom:

Pripravite zbirko "spo_module.c" z implementacijo modula za jedro Linux:

Modul naj opravlja naslednje operacije:

Zajem časa iz RTC modula in izpis v tok sporočil iz jedra (dmesg):

implementirajte dogodek za branje iz znakovne naprave
v dogodku preberite trenutni čas iz RTC modula - uporabite lahko samo out in inb - brez C-jevskih knjižnic! 
izpišite zajet podatek s sistemskim sporočilom
uporabite ukaz printk
format izpisa v dmesg naj bo "SPO date-time: 2023-05-04 09:15:45"
lahko se zgodi, da čas v RTC ni enak času, ki ga prikazuje OS
Primeri izpisa:

[300149.904713] SPO date-time: 2023-05-03 13:25:37
Opombe:

če se projekt ne prevede preko "make build" pravila, se naloga oceni z 0 točk
če ne upoštevate predpisanega izpisa se naloga oceni z -50% točk
 

Zahtevane zbirke za implementacijo naj se nahajajo v korenu imenika arhiva.

V arhivu naloga.zip oddajte naslednje zbirke:

Makefile
spo_module.c
spo_module.h