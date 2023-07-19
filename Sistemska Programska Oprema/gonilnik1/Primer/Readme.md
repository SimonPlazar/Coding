OS do strojne opreme ne dostopa neposredno, temveč preko gonilnikov, ki poskrbijo, da lahko dostopi do vsake naprave na enak način, ne glede na to, na kaj je namenjena.

Na UNIX-u je vsaka naprava, proces, zbirka, kazalo, pomnilnik, itd. vidna kot **zbirka**. Na večini UNIX sistemov lahko v kazalu /dev najdete dostopne naprave.

Posebnost vsake naprave je, da ima dve številki (major, minor number). 
Naprave so lahko blokovne ali znakovne:
- blokovna naprava je trdi disk
- zlogovne naprave je terminal

Uporabniške aplikacije ne smejo direktno dostopati do strojne opreme, saj lahko ogrozijo delovanje celotnega sistema. Uporabniške aplikacije tudi nimajo pravice izvajati priviligiranih ukazov za delo z V/I napravami, kakor tudi ne morejo dostopati do realnega (fizičnega) pomnilnika.

Običajno operacijski sistemi omogočajo pisanje gonilnikov, ki so lahko gonilniki dejanskih naprav ali navideznih. Pod operacijskim sistemom Linux pa je možno iti še korak dalje. Celotno jedro je napisano modularno, tako da so v pomnilniku naloženi samo tisti deli jedra, ki se v danem trenutku uporabljajo. Ti deli jedra se imenujejo **moduli jedra**.

# Modul jedra
Modul jedra je program, ki se po zahtevi naloži v jedro in tako razširi delovanje jedra, ne da bi za to morali ponovno zagnati računalnik (kot je to običajno pri nekaterih drugih operacijskih sistemih). Primer modula so tudi gonilniki. Pomembno je da ločimo med naslovnim prostorom uporabnika, v katerem se izvajajo uporabniške aplikacije (procesi) in naslovni prostorom jedra, v katerem se izvaja jedro. Do jedra uporabniški programi ne morejo direktno dostopiti, lahko pa uporabljajo njegove storitve (z uporabo sistemskih klicev).

Zaradi varnosti tudi programi iz jedra ne morejo klicati funkcij iz uporabniškega prostora, saj bi se tako lahko navaden proces izvajal v naslovnem prostoru jedra in zlorabil zaupanje. To pomeni, da ne moremo klicati funkcij kot so npr. printf itd. Funkcija **sprintf** in še več drugih uporabnih funkcij ima zato svojega **dvojnika** v jedru. 

Seznam naloženih modulov v danem trenutku lahko pridobimo z ukazom **lsmod**.
- lsmod

# Preprost primer modula
Poglejmo primer spo_module_a.c in Makefile

Prevedimo in poglejmo informacije o modulu
- modinfo spo_module_a.ko

Modul naložimo v jedro z ukazom **insmod**, odstranimo pa z ukazom **rmmod**. 
- sudo insmod spo_module_a.ko

Preverimo seznam naloženih modulov
- lsmod | grep 'spo_'

Preverimo vsebino dnevnika
- sudo dmesg | grep 'SPO'

Odstranimo modul iz jedra
- sudo rmmod spo_module_a

Preverimo vsebino dnevnika
- sudo dmesg | grep 'SPO'

# Naslednji primer
Poglejmo primer spo_module_b.c in Makefile

Prevedimo in naložimo modul
- sudo insmod spo_module_b.ko

Preverimo ali naprava **spo_device** obstaja
- cat /proc/devices

Ko gonilnik naložimo, moramo ustvariti posebno datoteko v mapi /dev, da lahko napravo uporabimo kakor datoteko. Poznati moramo moramo poznati major number modula (najdemo ga lahko tudi v datoteki /proc/devices).
Parameter c predstavlja character device; master številka 236; minor številka 0
- sudo mknod /dev/spo_driver c 236 0
- sudo chmod ugo+rw /dev/spo_driver

Preverimo ali spo_driver obstaja v /dev
- ll -l /dev

Preberimo iz gonilnika
cat /dev/spo_driver

Berimo iz gonilnika
watch -n 0.2 "cat /dev/spo_driver"

Odstranimo modul
- rmmod spo_module_b

Odstranimo datoteko v /dev
- unlink /dev/spo_driver

# Dodatno
Preverjanje IOPort-ov naprav
- sudo cat /proc/ioports

Branje zadnje vrednosti iz PS/2 tipkovnice
- uint8_t val = inb(0x60);