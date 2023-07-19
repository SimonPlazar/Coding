# Knjižnice

Poznamo dve vrsti knjižnic:
- statične
    - Linux: .a
    - Windows: .lib
    - MacOS: .a
- dinamične
    - Linux: .so
    - Windows: .dll
    - MacOS: .dylib

Dinamične knjižnice poznajo dve vrsti povezovanja:
- implicitno povezovanje
- eksplicitno povezovanje

## Statična knjižnica

Prevedi izvorne zbirke v objektne zbirke:
```
$ gcc -c -o print.o print.c
```

Arhiviraj objektne zbirke v statično knjižnico:
```
$ ar crs libprint.a print.o
```

### Povezovanje

Prevedi glavni program in ga poveži s statično knjižnico:
```
$ gcc -o prog_static main.c libprint.a
```

Zaženi program:
```
$ ./prog_static
```

Analiziraj simbole:
```
$ nm libprint.a
$ nm prog_static
```

Analiziraj povezave:
```
ldd prog_static
```

Odstrani ustvarjene zbirke:
```
$ rm -f print.o libprint.a prog_static
```

## Dinamična knjižnica

Prevedi izvorne zbirke v objektne zbirke:
```
$ gcc -c -fPIC -o print.o print.c
```

Poveži objektne zbirke v dinamično knjižnico:
```
$ gcc -shared -o libprint.so.1.3 -Wl,-soname,libprint.so.1 print.o
```

Ustvari simbolne povezave: navidezna povezava druge datoteke na prvo:
```
$ ln -sf libprint.so.1.3 libprint.so.1
$ ln -sf libprint.so.1 libprint.so
```

Imena zbirk dinamičnih knjižnic imajo posebno ime in pomen:
```
zbirka             ime            pomen
------             ---            -----
libprint.so        linker-name    uporabi povezovalnik (linker)
libprint.so.1      soname         uporabi nalagalnik (loader)
libprint.so.1.3    real-name      posodobi razvijalec
```

### Implicitno povezovanje

Prevedi glavni program in ga implicitno poveži z dinamično knjižnico: 

-L. pove povezovalniku, da naj v trenutni mapi poišče zbirko libprint.so

-l[dl] pove povezovalniku, da naj poišče zbirko lib[dl].so

```
$ gcc -o prog_dyn_imp main.c -L. -lprint
```

Zaženi program (napaka):
```
$ ./prog_dyn_imp
```

Zaženi program:
```
$ LD_LIBRARY_PATH=. ./prog_dyn_imp
```

Analiziraj simbole:
```
$ nm libprint.so
$ nm prog_dyn_imp
```

Odstrani ustvarjene zbirke:
```
$ rm -f print.o libprint.so libprint.so.1 libprint.so.1.3 prog_dyn_imp
```

### Eksplicitno povezovanje

Prevedi glavni program in ga eksplicitno poveži z dinamično knjižnico:
```
$ gcc -o prog_dyn_exp main_exp.c -ldl
```

```
man dlopen
```

Zaženi program:
```
$ ./prog_dyn_exp
```

Analiziraj simbole:
```
$ nm libprint.so
$ nm prog_dyn_exp
```

Odstrani ustvarjene zbirke:
```
$ rm -f print.o libprint.so libprint.so.1 libprint.so.1.3 prog_dyn_exp
```

## Viri

https://tldp.org/HOWTO/Program-Library-HOWTO/index.html

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/gcc-compiling-code

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/gcc-using-libraries

https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/developer_guide/creating-libraries-gcc

https://learn.microsoft.com/en-us/cpp/build/linking-an-executable-to-a-dll?view=msvc-170

https://man7.org/linux/man-pages/man8/ld.so.8.html
