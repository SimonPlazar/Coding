# Primer 1 - example_a.c

Sistemski klic ptrace() ponuja možnost, da en izmed procesov (zasledovalec -
ang. "tracer") opazuje in kontrolira izvajanje drugega procesa (zasledovanca -
ang. "tracee"). Zasledovalec lahko prav tako pregleduje in spreminja pomnilnik
in registre zasledovanca. Primarno se uporablja za implementacijo
razhroščevalnika s prekinitvami in sledenja sistemskih klicev.

- make
- ./example_a

## Upravljanje
- Ctrl + C

Posljemo signal SIGINT.
Signali ne prekinejo izvajanja procesa, pac pa ga samo zaustavijo.
Izjema je signal SIGKILL, ki prekine izvajanje procesa.

- ps -eo pid,stat,comm | grep --color -E "example_1|$"

STAT == t => stopped by debugger during the tracing.
Vrednost STAT je enaka t, kar pomeni, da je proces zaustavljen med sledenjem.

- kill -SIGKILL PID

Procesu z ID-jem PID posljemo signal SIGKILL.
Izvajanje procesa se prekine.

- ps -eo pid,stat,comm | grep --color -E "example_1|$"

Preverimo, da procesa res ni vec med trenutnimi procesi.

# Primer 2 - example_b.c
## Ustavljanje in ponovni zagon

- make
- ./example_b

# Primer 3 - example_c.c
## Branje in modifikacija vrednosti registrov

- make
- ./example_c

# Primer 4 - example_d.c
## Branje in modifikacija vrednosti spremenljivk

- make
- ./example_d

# Primer 5 - example_d.c
## Tocke zaustavitve

- make
- ./example_d