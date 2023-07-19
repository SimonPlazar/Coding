Delo s sistemskimi klici
Napišite program v programskem jeziku C, ki implementira upravljanje z imeniki (mapami) in zbirkami (datotekami) z uporabo sistemskih klicev.

Upravljanje naj vsebuje ustvarjanje imenik, prestavitev delovne poti v ustvarjeno imenik, ustvarjanje nove zbirke ter nastavljanje privilegijev nove zbirke.

Implementacija naj upošteva naslednje zahteve:

Struktura projekta:

Projekt naj vsebuje naslednje zbirke:

Makefile - vsebuje naj pravila "all", "build", "run" in "clean"
main.c - vsebuje naj demo vašega programa
Prevajanje projekta:

Pripravite zbirko "Makefile", ki bo vsebovala pravila za prevajanje projekta:

izhod prevajanja naj bo 32-bitni program
vsebuje naj pravilo "all"
pravilo kliče drugi pravili "build" in "run"
vsebuje naj pravilo "build"
pravilo iz podanih zbirk prevede program
ime zbirke prevedenega programa naj bo demo_klici
pravilo ne sme zagnati prevedenega programa
vsebuje naj pravilo "run"
pravilo naj zažene preveden program
vsebuje naj pravilo "clean"
pravilo naj odstrani vse ustvarjene zbirke
Delo s sistemskimi klici:

Pripravite zbirko "main.c" z implementacijo uporabe sistemskih klicev:

Vaša program naj izvede operacije:

Ustvarjanje imenika (mape):

samo s sistemskim klicem ustvarite imenik (mapo) z imenom "SysDir"
imenik ustvarite v istem imeniku, kjer je bil zagnan vaš program
zbirko ustvarite s pomočjo sistemskih klicev
Premik v imenik (mapo):

prestavite delovno pot v pravkar narejen imenik (mapo)
pot spremenite s pomočjo sistemskih klicev
Ustvarjanje zbirke (datoteke):

v ustvarjenem imeniku (mapi) ustvarite zbirko (datoteko) z imenom "PidTimeData.dat"
zbirko ustvarite s pomočjo sistemskih klicev
Nastavljanje parametrov zbirke (datoteke):

spremenite stopnjo zaščite zbirke:
tako da bo lahko uporabnik (user) datoteko bral in vanjo pisal
skupina (group) jo bo lahko samo brala
ostalim (others) pa bo delo z zbirko v celoti onemogočeno
stopnjo zaščite spremenite s pomočjo sistemskih klicev
Pisanje v zbirko (datoteko):

novo ustvarjeno zbirko (datoteko) odprite za pisanje
s pomočjo sistemskih klicev
v zbirko zapišite PID in trenutni čas
PID in čas pridobite z uporabo sistemskih klicev
Opozorilo:

Za izvedbo sistemskih klicev lahko uporabljate samo inline asm!.

Program mora biti preveden v 32-bitnem načinu - uporabite zastavico -m32.

Program se mora prevesti brez opozoril o PIE (ne smete uporabiti zastavice -no-pie) - uporabite zastavico -fPIE.

 

Opozorilo:

Lahko pridete do situacije, kjer s sistemskim klicem ustvarite imenik ali zbirko, ne morete se pa še prestaviti v njo ali prebrati njene atribute. To se zgodi, kadar sam imenik ali zbirka še ni bila fizično zapisana na disk (tehnologija SSD in "caching" doprineseta k temu). V tem primeru morate še klicati "sync" ter počakati, da ukaz resnično izvede.

 

Zahtevane zbirke za implementacijo naj se nahajajo v korenu imenika arhiva.

V arhivu naloga.zip oddajte naslednje zbirke:

Makefile
main.c
