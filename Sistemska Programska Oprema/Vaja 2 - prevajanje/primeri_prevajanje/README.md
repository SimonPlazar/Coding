# Prevajanje

## Prevajanje z ukazom *gcc*

```
gcc -o hello main.c hello.c
```

## Stopnje prevajanja

Prevajanje programskega jezika *C* je sestavljeno iz naslednjih 4 stopenj:

```
           |
           |  izvorna koda (.c, .h)
           ↓
+---------------------+
| 1. Predprocesiranje |  predprocesor (cpp)
+---------------------+
           |
           |  predprocesirana koda (.i) - vključene knjižnice, razširjeni makroji
           ↓
+---------------------+
| 2. Prevajanje       |  prevajalnik (gcc)
+---------------------+
           |
           |  zbirna koda (.s)
           ↓
+---------------------+
| 3. Zbiranje         |  zbirnik (as)
+---------------------+
           |
           |  objektna koda (.o)
           ↓
+---------------------+
| 4. Povezovanje      |  povezovalnik (ld)
+---------------------+
           |
           |  izvedljiva strojna koda
           |
```

## Izpis posameznih stopenj prevajanja

```
gcc -v -o hello main.c hello.c
```

## Stopenjsko prevajanje z ukazi *cpp*, *gcc*, *as* in *ld*

1. Predprocesiranje:
```
cpp -o main.i main.c
cpp -o hello.i hello.c
```

2. Prevajanje:
```
gcc -S -o main.s main.i
gcc -S -o hello.s hello.i
```

3. Zbiranje:
```
as -o main.o main.s
as -o hello.o hello.s
```

4. Povezovanje:
```
ld                                           \
-o hello                                     \
--dynamic-linker /lib64/ld-linux-x86-64.so.2 \
main.o                                       \
hello.o                                      \
/usr/lib/x86_64-linux-gnu/Scrt1.o            \
-lc
```

## Stopenjsko prevajanje z ukazom *gcc*

1. Predprocesiranje:
```
gcc -E -o main.i main.c
gcc -E -o hello.i hello.c
```

2. Prevajanje:
```
gcc -S -o main.s main.i
gcc -S -o hello.s hello.i
```

3. Zbiranje:
```
gcc -c -o main.o main.s
gcc -c -o hello.o hello.s
```

4. Povezovanje:
```
gcc -o hello main.o hello.o
```

## Pregled posameznih datotek

Datoteke s končnico *.i* ali *.s* lahko odpremo z ukazom *cat*.

Datoteke s končnico *.o* ali brez končnice lahko odpremo z ukazom *objdump -D*.

## Viri

https://gcc.gnu.org/onlinedocs/

https://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html

https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

## Optimizacija

Brez optimizacije:
```
gcc -O0 opt.c -o opt
time ./opt
size ./opt
```

Majhna optimizacija hitrosti:
```
gcc -O1 opt.c -o opt
time ./opt
size ./opt
```

Srednja optimizacija hitrosti:
```
gcc -O2 opt.c -o opt
time ./opt
size ./opt
```

Velika optimizacija hitrosti:
```
gcc -O3 opt.c -o opt
time ./opt
size ./opt
```

Optimizacija velikosti:
```
gcc -Os opt.c -o opt
time ./opt
size ./opt
```
