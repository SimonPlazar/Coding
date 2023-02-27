# Ukazni program

## Navodila 

Napišite ukazni program *countbytes*, ki iz standardnega vhoda bere zloge (znake), prešteje število ponovitev posameznega zloga, na koncu pa na standardni izhod izpiše seznam zlogov in število njihovih ponovitev.

Ukazni program naj podpira naslednje zastavice:
    -h --help
    Izpis pomoči. Le ta mora vsebovati vse zastavice in njihove kratke opise.

    -l --letters
    Izpiše statistiko za zloge, ki ustrezajo črkam (funkcija 'isalpha').

    -n --numbers
    Izpiše statistiko za zloge, ki ustrezajo števkam (funkcija 'isdigit').

    -x --hex
    Izpiše statistiko za vse zloge, zloge pa izpiše kot njihove hexadecimalne vrednosti s predpono 0x.

    -s=<> --select=<>
    Izpiše samo statistiko za podane zloge. Lahko nastavimo preko okoljske spremenljivke *SELECT*.

Zastavice so lahko podane v poljubnem vrstnem redu.

Zastavici -h in --help imata prednost pred ostalimi.
V kolikor je podana ena izmed teh zastavic se izpiše pomoč program pa se zaključi.
Druge zastavice se tako ignorirajo.

Zastavice -l, -n, -x in njihove dolge različice lahko poljubno kombiniramo.
Zastavico -s in njeno dolgo različico je smiselno kombinirati smo z zastavico -x oziroma --hex.

Zastavico -s ali --select ima prednost pred zastavicami -l, -n ali njihovimi dolgimi različicami. Kadar je podana zastavica -s ali --select se te druge ignorirajo.

Zastavico -s ali --select lahko uporabnik poda tudi preko okoljske spremenljivke SELECT. V kolikor je podana zastavica in nastavljena okoljska spremenljivka ima prednost zastavica.

Za branje posameznega zloga lahko uporabite funkcijo *getchar()*.
Za formatiran izpis vrednosti pa funkcijo *printf()*. 
Privzeto zloge izpišite kot znake.
Pri izpisu izpišite samo statistiko tistih zlogov, ki so bili prisotni.


## Primeri zagonov
Primeri uporabe:

$ ./

## Kaj morate implementirati pri tej nalogi?

- branje zastavic
    - poljuben vrstni red
    - prednostne nastavitve
- branje okoljske spremenljivke
- izpis statistike
    - vsi znaki
    - črke
    - števila
    - črke in števila
