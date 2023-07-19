Kontrola procesov s signali - Razhroščevalnik (debugger)
Napišite program v programskem jeziku C, ki implementira osnovne funkcije razhroščevalnika.

Vaš razhroščevalnik implementirajte z uporabo funkcije ptrace.

Implementacija naj upošteva naslednje zahteve:

Struktura projekta:

Projekt naj vsebuje naslednje zbirke:

    Makefile - vsebuje naj pravila "all", "build", "run" in "clean"
    main.c - vsebuje naj implementacijo vašega razhroščevalnika

Prevajanje projekta:

Pripravite zbirko "Makefile", ki bo vsebovala pravila za prevajanje projekta:

    izhod prevajanja naj bo 32-bitni program
    vsebuje naj pravilo "all"
        pravilo kliče drugi pravili "build" in "run"
    vsebuje naj pravilo "build"
        pravilo iz podanih zbirk prevede program
        ime zbirke prevedenega programa naj bo spo_debug
        pravilo ne sme zagnati prevedenega programa
    vsebuje naj pravilo "run"
        pravilo naj zažene preveden program
    vsebuje naj pravilo "clean"
        pravilo naj odstrani vse ustvarjene zbirke

Lasten razhroščevalnik:

Implementacija razhroščevalnika naj upošteva naslednje zahteve:

z razhroščevalnikom se upravlja preko ukazne vrstice terminala
ukazi naj bodo v obliki "ukaz" + "parameter" + ENTER
ob zagonu naj bo izvajanje programa ustavljeno
da omogočimo izvrševanje ukazov
(20t) Nastavljanje točke zaustavitve (break point):

z ukazom "b" + "naslov v šestnajstiški obliki" + "ENTER
podprite samo en breakpoint na enkrat
ko "otrok" pride to točke zaustavitve jo odstranite - "otrok" ne sme nadaljevati z izvajanjem, čaka naslednji ukaz
z ukazom "bs" + "naslov v šestnajstiški obliki" + "ENTER
podprite samo en breakpoint na enkrat
ko "otrok" pride do točke zaustavitve ne odstranite točke - "otrok" ne sme nadaljevati z izvajanjem, čaka naslednji ukaz
ko program zadane točko, zamenjajte prekinitev z izvornim ukazom
popravite eip register
izvedite en korak - single step
ponovno na naslov točke zaustavitve nastavite prekinitev
z ukazom "br" + "ENTER
odstranite nastavljen breakpoint, če le ta obstaja
(5t) Izvedi naslednji naslov (step):

z ukazom "s" + "ENTER
(5t) Nadaljuj z izvajanjem programa (continue):

z ukazom "c" + "ENTER
(10t) Izpis vsebine spremenljivke (print):

z ukazom "p" + "naslov v šestnajstiški obliki" + "ENTER
Pri ukazih "b", "bs", "br" in "p", "otrok" ne sme nadaljevati z izvajanjem ampak čaka na naslednji ukaz.

 

Primer uporabe:

zaženemo razhroščevanje z ./spo_debug ime_programa
izvedemo korak
s + ENTER
nastavimo breakpoint
b 0x1234 + ENTER
nadaljujemo z izvajanjem
c + ENTER
program pride do točke prekinitve (0x1234) - prekinitev se odstrani - izpišimo vrednost spremenljivke
p 0x4321 + ENTER
nastavimo nov breakpoint, nižje po strukturi programa
bs 0x5678 + ENTER
nadaljujemo z izvajanjem
c + ENTER
program pride do točke prekinitve (0x5678) - izvedemo korak
s + ENTER
odstranimo prekinitev (0x5678)
br + ENTER
nadaljujemo z izvajanjem
c + ENTER
Za testiranje razhroščevalnika lahko uporabite pripet program - test_debug.c

Program debug se mora izvajati dokler se "otrok" ne zaključi.

 

Opombe:

če se projekt ne prevede preko "make build" pravila, se naloga oceni z 0 točkami
če preveden program ne bo 32-bitni, se naloga oceni z -50% točk
če ne upoštevate predpisanega izpisa se naloga oceni z -50% točk
če uporabljate -no-pie se naloga oceni z 0 točkami - lahko pa uporabite personality(ADDR_NO_RANDOMIZE);
pri prevajanju morate uporabit zastavico -fPIE
 

Zahtevane zbirke za implementacijo naj se nahajajo v korenu imenika arhiva.

V arhivu naloga.zip oddajte naslednje zbirke:

Makefile
main.c