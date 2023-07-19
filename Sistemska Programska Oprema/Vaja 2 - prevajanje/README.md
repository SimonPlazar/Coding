Stopnje prevajanja
Napišite preprost program v programskem jeziku C in pripadajočo zbirko pravil za prevajanje Makefile, ki bosta prikazovala stopenjsko prevajanje izvorne kode.

Zbirka Makefile bo vsebovala dve množici različnih pravil, ki bosta prikazovali stopenjsko prevajanje izvorne kode. V prvi množici bodo pravila imenovana build_raw_*, ki bodo za prevajanje na različnih stopnjah uporabljala programe cpp, gcc, as in ld. V drugi množici bodo pravila imenovana build_gcc_*, ki bodo za prevajanje na vseh stopnjah uporabljala samo program gcc.

 

Struktura projekta
Projekt naj vsebuje naslednje zbirke:

main.c - vsebuje klic poljubne funkcije
function.h - vsebuje deklaracijo poljubne funkcije
function.c - vsebuje definicijo poljubne funkcije
Makefile - vsebuje pravila prevajanja
 

Zbirka function.h:

Vsebuje deklaracijo funkcije s poljubnim imenom, ki ne vrača ničesar (void).

 

Zbirka function.c:

Vsebuje definicijo poljubne funkcije iz zbirke function.h. Poljubna funkcija na stadardni izhod izpiše poljuben niz.

 

Zbirka main.c:

Vsebuje začetno funkcijo int main, ki pokliče poljubno funkcijo iz zbirke function.h.

 

Zbirka Makefile:

vsebuje pravilo all
pravilo kliče pravili build in run
vsebuje pravilo build
pravilo kliče pravili build_raw in build_gcc
vsebuje pravilo run
pravilo kliče pravili run_raw in run_gcc
vsebuje pravilo clean
pravilo kliče pravili clean_raw in clean_gcc
 

vsebuje pravilo build_raw
pravilo kliče pravilo build_raw_l
vsebuje pravilo build_raw_l
pravilo kliče pravilo build_raw_o
pravilo izvede povezovanje zbirk main_raw.o in function_raw.o v izvedljiv program demo_raw
uporabite program ld
vsebuje pravilo build_raw_o
pravilo kliče pravilo build_raw_s
pravilo izvede zbiranje zbirk main_raw.s in function_raw.s v zbirki main_raw.o in function_raw.o
uporabite program as
vsebuje pravilo build_raw_s
pravilo kliče pravilo build_raw_i
pravilo izvede prevajanje zbirk main_raw.i in function_raw.i v zbirki main_raw.s in function_raw.s
uporabite program gcc
vsebuje pravilo build_raw_i
pravilo izvede predprocesiranje zbirk main.c in function.c v zbirki main_raw.i in function_raw.i
uporabite program cpp
 

vsebuje pravilo build_gcc
pravilo kliče pravilo build_gcc_l
vsebuje pravilo build_gcc_l
pravilo kliče pravilo build_gcc_o
pravilo izvede povezovanje zbirk main_gcc.o in function_gcc.o v izvedljiv program demo_gcc
uporabite program gcc
vsebuje pravilo build_gcc_o
pravilo kliče pravilo build_gcc_s
pravilo izvede zbiranje zbirk main_gcc.s in function_gcc.s v zbirki main_gcc.o in function_gcc.o
uporabite program gcc
vsebuje pravilo build_gcc_s
pravilo kliče pravilo build_gcc_i
pravilo izvede prevajanje zbirk main_gcc.i in function_gcc.i v zbirki main_gcc.s in function_gcc.s
uporabite program gcc
vsebuje pravilo build_gcc_i
pravilo izvede predprocesiranje zbirk main.c in function.c v zbirki main_gcc.i in function_gcc.i
uporabite program gcc
 

vsebuje pravilo run_raw
pravilo zažene preveden program demo_raw
vsebuje pravilo run_gcc
pravilo zažene preveden program demo_gcc
 

vsebuje pravilo clean_raw
pravilo odstrani zbirko demo_raw in vse zbirke ustvarjene med njenim nastajanjem
pravilo ne izpiše napake tudi v primeru, da katera izmed zbirk ne obstaja
vsebuje pravilo clean_gcc
pravilo odstrani zbirko demo_gcc in vse zbirke ustvarjene med njenim nastajanjem
pravilo ne izpiše napake tudi v primeru, da katera izmed zbirk ne obstaja
 

Oddaja rešitve
Pri implementaciji rešitve bodite posebej pozorni na naslednje stvari:

program je napisan v programskem jeziku C
pri pisanju pravil build_raw_* uporabljate programe ld, as, gcc in cpp
pri pisanju pravil build_gcc_* uporabljate program gcc
pravilo clean ne izpiše napake tudi v primeru, da katera izmed zbirk ne obstaja
Na sistem za vaje oddajte arhiv zip, ki vsebuje celoten projekt (Makefile, main.c, function.h in function.c) z vašo implementacijo.