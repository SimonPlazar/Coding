obj-m += spo_module_b.o

K_VER = $(shell uname -r)

all:

# Za prevajanje uporabimo kbuild, ki ga Linux jedro uporablja za prevajanje

# Najenostavneje je, da uporabimo "make" za pripravo modulov.

# zastavica -C      - sprememba poti
# /lib/modeules/... - pot do izvorne kode jedra, kbuild, ...
# uname -r          - vrne različico trenutnega jedra
# zastavica -M      - zastavica za kbuild - pot do izvorne kode modula
# modules           - namestitev modula v privzeto pot za module

	make -C /lib/modules/$(K_VER)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(K_VER)/build M=$(PWD) clean
