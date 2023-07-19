# Vaja 2 (2022)
 
Izdelajte grafični uporabniški vmesnik, ki bo uporabniku omogočal generiranje N naključnih točk, ki predstavljajo množico χ. Točke χ se morajo nahajati znotraj vašega okna in jih tudi izrišite. Omogočite uporabniku izbiro med dvema načinoma tvorjenja naključnih točk:

enakomerno porazdeljene,
normalno oz. Gaussovo porazdeljene točke.
Nato omogočite uporabo treh različnih algoritmov za gradnjo konveksne (izbočene) lupine. Konveksna lupina množice točk χ je najmanjša podmnožica od χ, ki tvori konveksni mnogokotnik, kjer se  vse točke množice χ nahajajo v notranjosti ali na robu danega mnogokotnika. Iz tega sledita dve pomembni lastnosti konveksne lupine:

vsak notranji kot je manjši ali enak 180°,
vsaka daljica med dvema poljubno izbranima točkama leži znotraj ali na robu konveksne lupine.
Pri vsakem zagonu posameznega algoritma izrišete dobljeno konveksno lupino, kjer so sosednje konveksne točke povezane z daljicami. Prav tako izpišete pretečen čas od posameznega algoritma za izdelavo konveksne lupine nad N točkami.
Delovanje algoritmov testirajte pri velikostih N=100000, kjer bi morale biti razvidne časovne razlike algoritmov.
Za izdelavo aplikacije lahko uporabite kateri koli jezik (če ne bo C/C++, C# ali Java mi prosim sporočite). Velikost okna mora biti vsaj 800x600. Bodite pozorni na zaokrožitvene napake, sploh pri veliki količini točk! Pri vseh mejah in izračunih upoštevajte določeno toleranco.
Postopki algoritmov:
 
a) Jarvisov obhod (ang. Jarvis's march)

Poiščite ekstremno točko E (npr. tista, ki ima najmanjšo y in x vrednost) v χ. Ta točka je  zagotovo del konveksne lupine.
Za vsako točko S = χ\{E} izračunajte polarni kot glede x koordinatne osi, kjer je točka E izhodišče polarnega koordinatnega sistema in poiščite točko S1 z najmanjšim kotom. V primeru, da imata dva vektorja enak kot, ima prednost tista točka, ki ima manjšo evklidsko razdaljo d(E, S)= √((Ex-Sx)2+(Ey-Sy))2.
Točka E in točka S1 sta del konveksne lupine. Množici S odstranite točko S1 in dodajte točko E.
Izračunajte kote med vektorjem A=Pi - Pi-1 (zadnji dve dodani točki na konveksni lupini) in vektorji Bj=Sj - Pi, kjer Pi predstavlja zadnjo dodano točko na konveskni lupini, Sj pa j-ta točka v seznamu točk, ki niso del lupine. Iz izračunanih kotov izberemo najmanjšega min(Φj), pri katerem velja, da je Sj naslednja točka konveksne lupine. Točko Sj odstranite iz množice S.
Kot med dvema vektorjema se izračuna s pomočjo skalarnega produkta:
cos(Φ)=(A • B) / (|A| |B|)=(Ax*Bx + Ay*By) / (√(Ax2+Ay2) * √(Bx2 + By2))
Pri tem je kot med 0 in π (180°).
Četrti korak izvajate, dokler Pi ≠ E.
b) Grahamovo prebiranje (ang. Graham's scan)

Izberite tri naključne točke iz množice χ ter izračunajte njihovo težiščno točko O (povprečje treh točk je enako njihovem težišču). Ta točka je z visoko verjetnostjo znotraj konveksne lupine in ne na njenem robu.
S pomočjo točke O izračunajte kote glede na x os (podobno kot pri Jarvisovem obhodu) in točke shranite v seznam. Pozorni bodite na to, da so tukaj koti med 0 in 2π.  Za upoštevanje kotov med -π in π, ali 0 do 2π, si lahko pomagate z funkcijo atan2:
     Δθi =  atan2(xi - Ox, yi - Oy)
     if (Δθ < 0)  Δθ + = 2π
Seznam točk uredite glede na velikost kota.
V urejenem seznamu poiščite ekstremno točko E (npr. tista, ki ima najmanjšo/največjo y ali x vrednost). Ta točka je zagotovo del konveksne lupine.
Prve tri točke, ki jih upoštevate iz urejenega seznama so: E, P1 in P2, kjer sta P1 in P2 naslednji dve točki v urejenem seznamu.
Sprehodite se skozi sortiran seznam točk, kjer vedno upoštevajte 3 točke v seznamu: Pi, Pi+1 in Pi+2. Izračunajte vektorski produkt med danimi tremi točkami:
U = (Pi+1-Pi) x (Pi+2-Pi) = (x2-x1)(y3-y1) - (x3-x1)(y2-y1)
Če U<0 imamo desno usmerjenost trikotnika Δ(Pi, Pi+1, Pi+2) in kadar U>0 imamo levo usmerjenost. V primeru U=0 so točke kolinearne. Leva usmerjenost nam pove, da je točka Pi+1 del konveksne lupine in tako izberite naslednje 3 točke iz seznama: Pi=Pj+1, Pi+1=Pj+2 in Pi+2=Pj+3, kjer j=i. Sicer odstranite Pi+1 iz seznama ter izberite naslednje tri točke: Pi=Pj-1, Pi+1=Pj in Pi+2=Pj+1, kjer j=i.
Četrti korak izvajate, dokler Pi+1 ≠ E.
 
c) Hitra konveksna lupina (ang. QuickHull)

Poiščite ekstremni točki E1 in E2, ki imata najmanjšo in največjo abcisno vrednost x. Ti dve točki sta zagotovo na konveksni lupini.
Daljica med E1 in E2 razpolovi preostalo množico točk na dve podmnožici S1 in S2. Na začetku velja Ea=E1 in Eb=E2. Izvedite naslednji korak za posamezno podmnožico S1 in S2.
Za dano podmnožico poiščite točko E, ki tvori trikotnik Δ(Ea, E, Eb) z največjo ploščino. V primeru, da je več točk, ki tvori trikotnike z enako ploščino, se upošteva tista točka Ej, ki ima največji kot (Ea, Ej, Eb). Ta točka je zagotovo del konveksne lupine. Nato konstruirate dva vektorja: |E-Ea| in |Eb-E|. Točke, ki ležijo desno od posameznega vektorja niso del konveksne lupine. Točke na levi strani obeh vektorjev pa tvorijo dve novi podmnožici Sa in Sb.
Tretji korak ponovno izvedite nad posamezno množico Sa in Sb, v primeru, da ni prazna.
 
Vrednost naloge: 8 točk
1 točka (skupaj 2 točki):
generiranje enakomerno porazdeljenih točk
generiranje normalno porazdeljenih točk
2 točki (skupaj 6 točk):
Jarvisov obhod
Grahamovo prebiranje
Hitra konveksna lupina