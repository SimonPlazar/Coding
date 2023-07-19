## Kako lahko preverimo kateri sistemski klici se izvajajo na OS

# Izpis
strace echo "SPO"

# Datoteka
strace touch spo.dat

# Zapišimo "SPO" v datoteko "spo.dat" in preberimo nazaj
echo "SPO" > spo.dat
strace cat spo.dat