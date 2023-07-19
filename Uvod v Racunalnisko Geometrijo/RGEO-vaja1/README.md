# Vaja 1 (2022)
 
Izdelajte grafični uporabniški vmesnik, ki bo uporabniku omogočal vnos:

dveh točk,
ene točke in ene daljice,
ter dveh daljic.
Posamezno daljico določimo z dvema točkama. Točke naj bo možno vnesti na dva načina in sicer:

preko vnosnih polj,
interaktivno z uporabo miške.
Pri prvem načinu uporabite dialog z ustreznimi vnosnimi polji. Pri drugem načinu lahko uporabnik z klikanjem po zaslonu določi točke in/ali daljice; če so omogočene točke potem se naj prvi kliki določijo točke šele nato pa daljice. Aplikacija naj po vnosu vseh točk izriše točke in/ali daljice.

 

Naloga je razdeljena na pet delov:

 

1.  Izračun manhattan, evklidske in chebyshejeve razdalje med točkama T1 in T2

2a. Pravokotna projekcija točke T1 na daljico določeno s točkama T2, T3

2b. Najkrajša evklidska razdalja od točke T1 do daljice T2,T3

2c. Ali se točka T1 nahaja na levi ali desni strani daljice T2,T3

3.  Določitev presečišča med daljicama T1,T2 in T3,T4

 

1 del. Med točkama T1(x1, y1) in T2(x2, y2) izračunajtemanhattanavo, evklidsko in chebyshejevo razdaljo. Vse razdalje nato izpišite v aplikaciji.
 

2a del. Tokrat pravokotno projecirajte točko T1 na daljico, ki jo določata točki T2 in T3. Koordinate projecirane točke Tp izpišite v aplikaciji. Če točke T1 ni možno pravokotno projecirati na daljico, potem to tudi izpišite.

 

2b del. Kadar obstaja projekcija točke na daljico, potem lahko enostavno določimo najkrajšo razdaljo točke T1 do daljice T2,T3. To naredimo kar kot izračun evklidske razdalje med točkama T1 in Tp.

Kadar pravokotna projekcija ne obstaja, potem mora biti najkrajša razdalja do daljice ali med točkama T1,T2 ali točkama T1,T3.

Dobljeno najkrajšo razdaljo točke T1 do daljice T2,T3 izpišite v aplikaciji.



2c del. Da določite ali se točka T1 nahaja na levi ali desni strani daljice T2,T3 uporabite 2D vektorski produkt med vektorjem V1 = T1 - T2 in V2 = T3 - T2. Položaj točke lahko nato določite s predznakom rezultata. V kolikor je pozitiven se točka T1 nahaja na levi strani, v primeru da je negativen pa na desni strani. Tukaj je potrebno upoštevati robni primer kadar točka leži na sami daljici! Takrat ni ne na levi ali desni strani.

3 del. Pri iskanju presečišča upoštevajte naslednje scenarije in v aplikaciji izpišite za kateri scenarij gre:
daljici se sekata: izpišite koordinate presečišča in ga izrišite,
daljici se ne sekata,
daljici se dotikata v eni točki: izpišite koordinate presečišča in ga izrišite,
daljici sovpadata: označite odsek sovpadanja (namig: točke sortirajte in uporabite sredinski 2, ki predstavljata vektor prekrivanja)
daljici sta vzporedni.
 
Za izdelavo aplikacije lahko uporabite katerikoli jezik. Velikost okna mora biti vsaj 800x600. Bodite pozorni na zaokrožitvene napake! Pri vseh mejah in izračunih upoštevajte določeno toleranco.
 
Uporabne lastnosti:
1. Med dvema točkama T1 in T2 je razdalja določena na slediči način:
   Manhattanova razdalja - |T1−T2|=abs(x1−x2)+abs(y1−y2)

   Evklidska razdalja - |T1−T2|=(x1−x2)2+(y1−y2)2√

   Chebysheva razdalja - |T1−T2|=max(abs(x1−x2),abs(y1−y2))

2. Ortogonalno projekcijo točke T1 na poljubno premico, na kateri se nahajata točki T2 in T3, izračunamo sledeče:

T2 vzamem za novo koordinatno izhodišče ter določimo vektorja V1 in V2, ki kažeta na točki T1 in T3:
V1 = T3-T2
V2 = T1-T2
Vektor V1 normaliziramo in dobimo bazni vektor Vn. Le tega si lahko predstavljamo kot vektor, ki določa našo novo X os.
Skalarni produkt sp = Vn · V2 poda skalarno vrednost, s pomočjo katere dobimo projecirano točko Tp:
Tp = T2 + Vn * sp
Dodatno moramo upoštevati da mora biti 0 ≤ sp ≤ | V1 |, saj drugače projecirana točka Tp leži izven daljice določene z točkama T2 in T3.

 

3. Rezultat 2D vektorskega produkta V1(x1, y1) in V2(x2, y2) je ploščina paralelograma definiranega s stranicama |V1| in |V2|. Vektorski produkt: V1 x V2 = |V1| |V2| sin(Θ)= x1*y2 - x2*y1

Če točke T1,T2 in T3 ponazorimo z vektorjema V1 = (T2-T1) in V2=(T3-T1), ter izvedemo vektorski produkt med njima, lahko ugotovimo ali točka T3 leži na levi (pozitivni predznak) ali desni (negativni predznak) strani daljice T1,T2. Točke so koliniarne oz. sovpadajo (ležijo na isti premici), če je rezultat enak 0.

Postopek za tretji del naloge:
 
a) Ali presečišče sploh obstaja?
Klasična primerjava funkcij f(x) = g(x), vendar moramo vektorja najprej predstaviti kot funkciji. Ti sta v našem primeru definirani kot T1+Ua(T2-T1) in T3+Ub(T4-T3). Presečišče tako obstaja, če velja:
T1+Ua(T2-T1) = T3+Ub(T4-T3)
 
Pri tem nas zanimata neznani skalarni vrednosti oz. parametra Ua in Ub. Ko upoštevamo vsako koordinato posebej dobimo sistem enačb:
x1+Ua(x2-x1) = x3+Ub(x4-x3)
y1+Ua(y2-y1) = y3+Ub(y4-y3)
 
Iz tega lahko izračunamo neznana parametra, kjer po preurejanju enačb dobimo sledeče vektorske produkte:

D = (T2-T1) x (T4-T3) = (x2 - x1)(y4 - y3) - (x4 - x3)(y2 - y1)
A = (T4-T3) x (T1-T3) = (x4 - x3)(y1 - y3) - (x1 - x3)(y4 - y3)
B = (T2-T1) x (T1-T3) = (x2 - x1)(y1 - y3) - (x1 - x3)(y2 - y1)
V primeru, da daljici sovpadata, velja D=A=B=0 in smo končali.
 
Nato izračunamo parametra:
Ua = A/D
Ub = B/D
 
Najprej preverimo, ali je D enak 0. Če je, sta daljici vzporedni in smo končali. Sicer preverimo še dva pogoja:
0 ≤ Ua ≤ 1
0 ≤ Ub ≤ 1
 
Če oba pogoja držita, potem se daljici sekata, zato lahko nadaljujemo z naslednjim korakom, kjer izračunamo točko presečišča. 
 
b) Izračun točke presečišča
x = x1+Ua(x2-x1) ali x = x3+Ub(x4-x3)
y = y1+Ua(y2-y1) ali y = y3+Ub(y4-y3)
 
Primer programa opisanega v nalogi si lahko prenesete iz priloge. Program vam naj služi kot pomoč pri lastni implementaciji.
Pri nalogi je možno dobiti 8 točk. Kriterij je sledeč:

1 del - 1 točka
 - razdalje med dvema točkama
2 del - 2 točki
 - projekcija točke na daljico
 - pravilni izračun nakrajše razdalje točke do daljice in na kateri strani daljice se nahaja
3 del - 5 točk
 - daljici se sekata: izpišite koordinate presečišča in ga izrišite,
 - daljici se ne sekata,
 - daljici se dotikata v eni točki: izpišite koordinate presečišča in ga izrišite,
 - daljici sovpadata: označite odsek sovpadanja (namig: točke sortirajte in uporabite sredinski 2, ki        
 - daljici sta vzporedni.

Primer programa si lahko pogledate tukaj.