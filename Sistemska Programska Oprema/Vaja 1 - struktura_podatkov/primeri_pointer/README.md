# Struktura podatkov

## Prevajanje primera

Na 64-bitni arhitekturi se program privzeto prevede v 64-bitnem načinu. Če želimo program prevesti v 32-bitnem načinu, moramo prevajalniku GCC podati zastavico ```-m32```. Za prevajanje v 32-bitnem načinu moramo posebej namestiti tudi ustrezne knjižnice, ki privzeto niso nameščene. Na distribuciji Ubuntu ustrezne knjižnice namestimo z ukazom ```sudo apt install gcc-multilib```. V primeru, da knjižnice niso ustrezno nameščene, bo prevajanje neuspešno, prevajalnik pa bo javil napako ```fatal error: bits/libc-header-start.h: No such file or directory```.

Prevajanje programov:  
```make build```

Zagon prevedenih programov:  
```make run```

Prevajanje in zagon prevedenih programov:  
```make all```

## Poravnava podatkov v pomnilniku

### Primer strukture

```
struct
{
    uint8_t  a;
    uint16_t b;
    uint32_t c;
    float    d;
    double   e;
}
```

### Poravnava podatkov v privzetem (64-bitnem) načinu

Posamezen element strukture je privzeto poravnan na naslov, ki je deljiv z velikostjo elementa v zlogih. Tako je na primer element tipa *uin8_t* poravnan na naslov deljiv z 1, element tipa *uint16_t* na naslov deljiv z 2 in element tipa *uint32_t* na naslov deljiv s 4. Kazalec, ki je v 64-bitnem načinu velik 8 zlogov, je poravnan na naslov deljiv z 8. Celotna struktura pa je poravnana na naslov, ki je deljiv z velikostjo največjega elementa strukture v zlogih.

```
element    tip         velikost    naslov       skupna velikost
-------    ---         --------    ------       ---------------
a          uint8_t          1 B    0x00  (0)                1 B
padding                     1 B    0x01  (1)                2 B
b          uint16_t         2 B    0x02  (2)                4 B
c          uint32_t         4 B    0x04  (4)                8 B
d          float            4 B    0x08  (8)               12 B
padding                     4 B    0x0C (12)               16 B
e          double           8 B    0xA0 (16)               24 B
```

### Poravnava podatkov v 32-bitnem načinu

V 32-bitnem načinu so spremenljivke tipa *double* privzeto poravnane na 4 zloge. Poravnavo na 8 zlogov lahko vklopimo z zastavico ```-malign-double```. Prav tako so kazalci, ki so v 32-bitnem načinu veliki 4 zloge, poravnani na naslove deljive s 4.

```
element    tip         velikost    naslov       skupna velikost
-------    ---         --------    ------       ---------------
a          uint8_t          1 B    0x00  (0)                1 B
padding                     1 B    0x01  (1)                2 B
b          uint16_t         2 B    0x02  (2)                4 B
c          uint32_t         4 B    0x04  (4)                8 B
d          float            4 B    0x08  (8)               12 B
e          double           8 B    0x0C (12)               20 B
```

### Neporavnani podatki

Poravnavo podatkov lahko za posamezno strukturo izklopimo s pomočjo rezerviranih besed ```__attribute__ ((packed))```. Več o tem v uradni dokumentaciji prevajalnika GCC: https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html#Common-Type-Attributes

```
element    tip         velikost    naslov       skupna velikost
-------    ---         --------    ------       ---------------
a          uint8_t          1 B    0x00  (0)                1 B
b          uint16_t         2 B    0x01  (1)                3 B
c          uint32_t         4 B    0x03  (3)                7 B
d          float            4 B    0x07  (7)               11 B
e          double           8 B    0x0B (11)               19 B
```

### Viri

http://www.catb.org/esr/structure-packing/
