# Cevovod

## Navodila 

Dopolnite program *pipeline*, ki prebere serijo ukazov iz standardnega vhoda ali zbirke, vsako vrstico izvede kot svoj ukaz (parametri ločeni s presledki) in jih poveže v cevovod. Standardni izhod prvega ukaza se preusmeri na standardni vhod drugega ukaza, standardni izhod drugega ukaza se preusmeri na standardni vhod tretjega ukaza in tako dalje. 

V projektu vas čaka pripravljeno ogrodje, ki prebere ukaze z standardnega vhoda ali podane zbirke.
Ukaze razreže na ustrezne žetone in kliče funkcijo *execute_pipeline*. 

Vaša naloga je implementirati funkcijo *int execute_pipeline(char\*\*\* cmd_list, int input_fd, int output_fd, int err_fd)*. 
Parameter *cmd_list* je kazalec na seznam ukazov.
Parameter *input_fd* je oprimek vhoda prvega ukaza.
Parameter *output_fd* je oprimek izhoda zadnjega ukaza.
Parameter *err_fd* je oprimek izhoda za napake za vse ukaze.
Vsak ukaz tipa je kazalec na seznam argumentov.
Vsak seznam argumentov je kazalec na seznam nizev.
Seznami so zaključeni z kazalcem NULL (0).
Priložen diagram prikazuje kako so ti podatki hranjeni v pomnilniku.

Okostje vas čaka v *src/pipeline.c*. Priložena implementacija se z zanko sprehodi čez vse ukaze in izpiše hranjene argumente.

Za vsak ukaz v *cmd_list* se pričakuje, da boste:

+ ustvarili ustvarili ustrezno cev (po potrebi) za izhod 
+ ustvarili nov proces (s klicem *fork()*)
+ v novem procesu
    + preusmerili izhod prejšnjega procesa v vhod tega procesa
    + preusmerili izhod tega procesa v pripravljeno cev
    + preusmerili izhod za napake tega procesa v *err_fd*
    + zaprli oprimek vhoda za naslednji proces (!!! zelo pomembno !!!)
    + zaprli neuporabljane oprimke
    + izvedli ukaz (s klici *exec*, ki iščejo ukaze v nastavljeni poti)
+ v originalnem procesu
    + zaprli oprimek vhoda za ustvarjen proces
    + zaprli oprimek vhoda za naslednji proces

** !!! V primeru napake v postopku se naj program *pipeline* zaključi. !!! **
Ko so vsi ukazi uspešno pognani v svojih procesih naj originalni proces stori naslednje:

+ počaka vsakega izmed ustvarjenih procesov (s klicem *waitpid()*)
+ prebere status/izhodno vrednost počakanega procesa
+ vrne izhodno vrednost prvega procesa, ki ni vrnil 0
+ v kolikor je kateri izmed procesov prekinjen s signalom, naj vrne 255 



... 

## Primeri zagonov

...

```bash
$ ...
```

## Pregled testiranih podrobnosti implementacije

+ zagon in preusmeritve enega ukaza
    + absolutna pot
    + sistemski ukaz
    + parametri
+ zagon im preusmeritve dveh ukazov
+ zagon in preusmeritve poljubnega stevila ukazov
    + vsi ukazi na isti err_fd

+ napaka v postopku
    + napacno ime ukaza

+ vrnjena vrednost
    + vsi ukazi uspesni
    + prvi ukaz neuspesen
    + zadnji ukaz neuspesen
    + ukaz na sredi neuspesen
    + srednji ukaz prekinjen s signalom



