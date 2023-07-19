# Vaja 4 - Javascript
 
Pri tej vaji boste spoznali osnove skriptnega jezika JavaScript (v nadaljevanju JS), ki je ena od bistvenih tehnologij spletnih aplikacij. JS se izvaja v brskalniku, torej na strani odjemalca (uporabnika).

Vse datoteke zapakirajte v paket s končnico .zip in oddajte na sistem.

Naloga 1 (7,5 točk):
Ustvarite datoteko tabela.html, v katero pišite vso HTML, CSS in JS kodo. Implementirajte stran, ki od uporabnika zahteva vnos št. vrstic (celo število med 5 in 20) in št. stolpcev (celo število med 10 in 40). Za vnos uporabite funkcijo window.prompt. Uporabnika sprašujte tako dolgo, dokler ne vnese ustreznih števil. Ko uporabnik vnese ustrezni števili, izrišite tabelo s 16 celicami. V vsako celico vstavite sličico iz te priloge. Pod to tabelo izrišite tabelo z dimenzijami, ki ustrezajo uporabnikovemu vnosu. S CSS nastavite fiksno širino in višino, ki naj se prilega sličicam iz priloge. Nastavite srebrno ozadje in sivo obrobo celic ter odstranite prostor med celicami v tabeli. Skušajte se čim bolj približati rezultatu na zaslonskem posnetku.

S pomočjo dogodkov omogočite, da uporabnik izbere sličico v prvi tabeli. Dodajte tudi dogodek, ki ob kliku na celico v drugi tabeli, v celico vstavi izbrano sličico.

Zgled: začetno stanje, izpolnjena tabela

Naloga 2 (7,5 točk):
Ustvarite dokument obrazec.html in v njem implementirajte spletni obrazec z naslednjimi vnosnimi polji:

Uporabniško ime: besedilno vnosno polje
E-pošta: besedilno vnosno polje
Geslo: vnosno polje za geslo
Ponovi geslo: vnosno polje za geslo
Spol: radio gumbi za izbiro spola "moški" ali "ženski"
Gumb "Pošlji" za pošiljanje podatkov
Implementirajte lastno Javascript preverjanje pravilnosti izpolnjenih podatkov. Pri tej nalogi za validacijo ne smete uporabljati namenskih HTML atributov in naprednih vnosnih polj. Vneseni podatki morajo izpolnjevati naslednje pogoje:

Uporabniško ime:
dolžina med vključno 3 in 20 znakov
Uporabniško ime se ne sme podvajati. Ustvarite polje s vsaj 5 obstoječimi uporabniškimi imeni in preverjajte, če vnešeno ime že obstaja v polju.
E-pošta:
Preverite ustrezno obliko vnesenega elektronskega naslova s pomočjo regularnih izrazov. Ustrezen regularni izraz lahko poiščete na spletu, v tem primeru v komentar zapišite povezavo, kje ste izraz našli.
Geslo:
Dolžina vsaj 6 znakov
Vsebovati mora vsaj eno malo črko angleške abecede
Vsebovati mora vsaj eno veliko črko angleške abecede
Vsebovati mora vsaj eno števko
Ponovi geslo:
Mora biti enako kot geslo
Spol:
Mora biti izbran
Vnosna polja validirajte sproti, ko uporabnik vnaša podatke in ga hkrati obvečajte o napakah. Validacijo izvedite tudi, ko uporabnik klikne na gumb "Pošlji" in preprečite pošiljanje podatkov, če ne ustrezajo kriterijem.