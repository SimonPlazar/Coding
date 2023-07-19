Statično in dinamično povezovanje
Napišite preprost program v programskem jeziku C in pripadajočo zbirko pravil za prevajanje Makefile, ki bosta prikazovala statično ter dinamično implicitno in eksplicitno povezovanje.

 

Struktura projekta
Projekt naj vsebuje naslednje zbirke:

add.h - deklaracija funkcije za seštevanje
add.c - definicija funkcije za seštevanje
mul.h - deklaracija funkcije za množenje
mul.c - definicija funkcije za množenje
main.c - funkcija main, ki kliče funkciji seštevanja in množenja, uporabljena pri statičnem in dinamičnem implicitnem povezovanju
main_exp.c - funkcija main, ki kliče funkciji seštevanja in množenja, uporabljena pri dinamičnem eksplicitnem povezovanju
Makefile - pravila prevajanja
 

Zbirka add.h:

Vsebuje deklaracijo funkcije za seštevanje naslednje oblike:

int32_t add(int32_t a, int32_t b);
 

Zbirka add.c:

Vsebuje definicijo funkcije za seštevanje iz zbirke add.h. Funkcija vrne vsoto vrednosti a in b.

 

Zbirka mul.h:

Vsebuje deklaracijo funkcije za množenje naslednje oblike:

float mul(float a, float b);
 

Zbirka mul.c:

Vsebuje definicijo funkcije za množenje iz zbirke mul.h. Funkcija vrne zmnožek vrednosti a in b.

 

Zbirka main.c:

Vsebuje naslednje korake:

vključi zbirki add.h in mul.h z deklaracijama funkcij
znotraj funkcije main kliče funkcijo add s parametrom a enakim 2 in parametrom b enakim 4, ter na standardni izhod izpiše vrnjen rezultat
znotraj funkcije main kliče funkcijo mul s parametrom a enakim 2 in parametrom b enakim 4, ter na standardni izhod izpiše vrnjen rezultat
 

Zbirka main_exp.c:

Vsebuje naslednje korake:

vključi zbirki add.h in mul.h z deklaracijama funkcij
znotraj funkcije main s funkcijo dlopen odpre dinamično knjižnico libmath.so
znotraj funkcije main s funkcijo dlsym prebere naslov funkcije add
znotraj funkcije main kliče funkcijo add s parametrom a enakim 2 in parametrom b enakim 4, ter na standardni izhod izpiše vrnjen rezultat
znotraj funkcije main s funkcijo dlsym prebere naslov funkcije mul
znotraj funkcije main kliče funkcijo mul s parametrom a enakim 2 in parametrom b enakim 4, ter na standardni izhod izpiše vrnjen rezultat
znotraj funkcije main s funkcijo dlclose zapre dinamično knjižnico libmath.so
 

Zbirka Makefile:

vsebuje pravilo all
pravilo kliče pravili build in run
vsebuje pravilo build
pravilo kliče pravila build_static, build_dyn_imp in build_dyn_exp
vsebuje pravilo run
pravilo kliče pravila run_static, run_dyn_imp in run_dyn_exp
vsebuje pravilo clean
pravilo odstrani vse zbirke ustvarjene med prevajanjem
vsebuje pravilo build_static
zbirki add.c in mul.c prevede v objektni zbirki add.o in mul.o
iz zbirk add.o in mul.o ustvari statično knjižnico libmath.a
zbirko main.c prevede in statično poveže s knjižnico libmath.a v program z imenom prog_static
vsebuje pravilo build_dyn_imp
zbirki add.c in mul.c prevede v objektni zbirki add.o in mul.o
iz zbirk add.o in mul.o ustvari dinamično knjižnico libmath.so.2.4 z vrednostjo soname enako libmath.so.2
ustvari simbolni povezavi libmath.so.2 in libmath.so
zbirko main.c prevede in dinamično implicitno poveže s knjižnico libmath.so v program z imenom prog_dyn_imp
vsebuje pravilo build_dyn_exp
zbirki add.c in mul.c prevede v objektni zbirki add.o in mul.o
iz zbirk add.o in mul.o ustvari dinamično knjižnico libmath.so.2.4 z vrednostjo soname enako libmath.so.2
ustvari simbolni povezavi libmath.so.2 in libmath.so
zbirko main_exp.c prevede in dinamično eksplicitno poveže s knjižnico libmath.so v program z imenom prog_dyn_exp
vsebuje pravilo run_static
pravilo zažene preveden program prog_static
vsebuje pravilo run_dyn_imp
pravilo zažene preveden program prog_dyn_imp
vsebuje pravilo run_dyn_exp
pravilo zažene preveden program prog_dyn_exp
 

Oddaja rešitve
Pri implementaciji rešitve bodite posebej pozorni na naslednje stvari:

vsi programi so napisani v programskem jeziku C
program prog_static uporabi statično povezovanje
program prog_dyn_imp uporabi dinamično implicitno povezovanje
program prog_dyn_exp uporabi dinamično eksplicitno povezovanje
Na sistem za vaje oddajte arhiv zip, ki vsebuje celoten projekt (Makefile, main.c, main_exp.c, add.h, add.c, mul.h, mul.c) z vašo implementacijo.