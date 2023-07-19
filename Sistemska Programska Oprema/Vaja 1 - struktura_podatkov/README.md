Podatkovni tipi in pomnilniški prostor v jeziku C
Napišite program v programskem jeziku C, ki bo v rezerviran prostor v pomnilniku shranil podatke različnih tipov.

V tem primeru boste v polje tipa uint16_t dolžine 6 elementov shranili naslednje podatke: 3 x char, 1 x float, 1 x uint32_t ter 1 x char. Skupno boste torej ustvarili polje dolžine 12 zlogov in vanj shranili prav toliko zlogov podatkov.

 

Struktura projekta
Projekt naj vsebuje naslednje zbirke:

Makefile - vsebuje pravila all, build, run in clean
main.c - vsebuje klice funkcij in prikaže delovanje programa
buffer.h - vsebuje deklaracije funkcij
buffer.c - vsebuje definicije funkcij
 

Zbirka Makefile:

vsebuje pravilo all
pravilo kliče pravili build in run
vsebuje pravilo build
pravilo prevede program z imenom data_buffer
uporabite prevajalnik GCC
vključite zastavice -Wall -Wextra -Werror -Wpedantic
vsebuje pravilo run
pravilo zažene preveden program
vsebuje pravilo clean
pravilo odstrani vse ustvarjene zbirke
 

Zbirka buffer.h:

Vsebuje deklaracije naslednjih funkcij:

uint16_t *buffer_alloc(size_t size);
void buffer_free(uint16_t *buffer);
void buffer_fill(uint16_t *buffer);
void buffer_print(uint16_t *buffer);
Kjer je size_t size velikost alociranega pomnilnika v zlogih in uint16_t *buffer kazalec na alociran pomnilnik.

 

Zbirka buffer.c:

Vsebuje definicije deklariranih funkcij iz zbirke buffer.h:

buffer_alloc
s funkcijo malloc rezerviraj dinamični pomnilnik s podano velikostjo
iz funkcije vrni kazalec na začetek alociranega pomnilnika
buffer_free
s funkcijo free sprosti dinamični pomnilnik na podanem naslovu
buffer_fill
v pomnilnik na podanem naslovu zapiši podatke v naslednjem vrstnem redu:
znak "S" tipa char (1 zlog)
znak "P" tipa char (1 zlog)
znak "O" tipa char (1 zlog)
število s plavajočo vejico "3.141593" tipa float (4 zloge)
celo število "25947" tipa uin32_t (4 zloge)
znak "!" tipa char (1 zlog)
buffer_print
izpiši vsebino pomnilnika na podanem naslovu
posamezen tip podatka izpiši v svoji vrstici
Izpis funkcije buffer_print bi v tem primeru izgledal takole:

S
P
O
3.141593
25947
!
 

Zbirka main.c:

vključite zbirko z deklaracijo funkcij
v funkciji int main opravite klice funkcij v naslednjem vrstnem redu
buffer_alloc
buffer_fill
buffer_print
buffer_free
 

Oddaja rešitve
Pri implementaciji rešitve bodite posebej pozorni na naslednje stvari:

program je napisan v programskem jeziku C
program se prevede s prevajalnikom GCC z vključenimi zastavicami -Wall -Wextra -Werror -Wpedantic
ime zbirke prevedenega programa je data_buffer
velikost alociranega pomnilnika je res točno 12 zlogov (6 elementov tipa uint16_t)
Na sistem za vaje oddajte arhiv zip, ki vsebuje celoten projekt (Makefile, main.c, buffer.h in buffer.c) z vašo implementacijo.