Računanje z uporabi SIMD inštrukcij

Implementacijske zahteve:

1) Z uporabo SIMD inštrukcij (AVX, AVX2, AVX512, ...) izvedite množenje dveh velikih polj ter rezultat shranite v novo polje

Tip podatkov naj bo double
Velikost polj naj bo vsaj 100 milijonov elementov (zagotovite, da bo dolzina polja veckratnik dolzine registra v zlogih)
Elemente polja nastavite na naključne vrednosti iz območja 0-10
Velikost vektorjev prilagodite vašemu sistemu (128, 256 ali 512 bitov) - uporabite največje možno, kar vaš sistem podpira (cat /proc/cpuinfo)
Po izracunu izpisite prvo in zadnjo vrednost polja z rezultati
2) V polju rezultatov (iz točke 1), z uporabo SIMD inštrukcij, poiščite največje in najmanjše število.

Izpisite najmanjso in najvecjo najdeno vrednost
3) Rešitev z uporabo SIMD inštrukcij primerjajte z iterativno implementacijo in uporabo zastavice -O2 (pri prevajanju z gcc)

Izvedite časovno primerjavo
Rezultate zapisite v PDF
Struktura projekta:

Projekt naj vsebuje naslednje zbirke:

Makefile - vsebuje naj pravila "build" in "clean"
spo_simd.c - vsebuje naj implementacijo vašega modula
spo_simd.h - vsebuje naj zaglavje vašega modula
Prevajanje projekta:

Pripravite zbirko "Makefile", ki bo vsebovala pravila za prevajanje projekta:

vsebuje naj pravilo "build"
pravilo iz podanih zbirk prevede program
vsebuje naj pravilo "clean"
pravilo naj odstrani vse ustvarjene zbirke
Opombe:

če se projekt ne prevede preko "make build" pravila, se naloga oceni z 0 točk
Zahtevane zbirke za implementacijo naj se nahajajo v korenu imenika arhiva (.zip).