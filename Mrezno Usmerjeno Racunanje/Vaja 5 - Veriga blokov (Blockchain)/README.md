Vaja 5 - Veriga blokov (Blockchain)

Izdelajte aplikacijo (spletno ali namizno) z grafičnim vmesnikom, ki bo omogočala delo z verigo blokov. Implementirajte validacijo blokov in celotne verige kot tudi ustvarjanje novih blokov (rudarjenje). Rudarjenje novih blokov implementirajte z algoritmom konsenza "proof-of-work". Dodatno implementirajte spremenljivo težavnost generiranja novih blokov v omrežju, validacijo časovnih značk in kumulativno težavnost. Komunikacija med večimi instancami vaše aplikacije mora potekati po omrežju! V nasprotnem primeru, bo naloga ocenjena z 0 točkami!

Struktura bloka
Vsak blok naj ima naslednje elemente:

indeks
podatek (data)
časovna značka (timestamp)
zgoščena vrednost bloka (hash)
zgoščena vrednost prejšnjega bloka (previousHash)
Ko ustvarite prvi blok v verigi bodite pozorni na vrednost zgoščene vrednosti prejšnjega bloka, ki naj bo enaka 0.



Validacija bloka in verige
Ko se novi bloki dodajajo v verigo, jih je potrebno validirati oz. preveriti njihovo integriteto. Izpolnjeni morajo biti naslednji pogoji:

indeks trenutnega bloka je za 1 večji od prejšnjega bloka
zgoščene vrednosti morajo biti ustrezne
currentBlock.previousHash == previousBlock.hash
calculateHash(currentBlock) == currentBlock.hash
Zgoščeno vrednost bloka izračunajte iz elementov bloka. Uporabite zgoščevalno funkcijo SHA-256.

hash = sha256(index + timestamp + data + previousHash)
Integriteto celotne verige preverimo tako, da preverimo integriteto vseh blokov, ki so v verigi. V kolikor ugotovite, da bloka ali verige ni moč validirati, to izpišite oz. izrišite v grafičnem vmesniku aplikacije. Zaradi sočasnosti se lahko zgodi, da boste dobili različna stanja verig na posameznih vozliščih. V tem primeru velja daljša veriga.

Rudarjenje in algoritem "proof-of-work"
Če blok lahko validiramo, ga lahko dodamo v verigo blokov, saj izpolnjuje pogoje za integriteto. To ni vedno zaželjeno, saj lahko tako v porazdeljenem sistemu kdorkoli dodaja nove bloke v verigo. Ker želimo to omejiti uvedemo računski problem, ki mora biti rešen, da se nov blok lahko doda v verigo. Postopku reševanja tega računskega problema pravimo rudarjenje.

Pri implementaciji rudarjenja razširite strukturo bloka z žetonom za enkratno uporabo (nonce) in vrednostjo težavnosti. Vrednost težavnosti bo število ničel, ki jih mora imeti zgoščena vrednost bloka na začetku, da bo blok veljaven.

diff=5 => 000007e13d3a75526946a3bcf00daec9fc9c9c4d51ddc7cc5df888f74dd434d1
diff=11 => 00000000000f58d61cf048d168aa6f5e492dea166d8bb54ec06c30de07db57e1
Žeton za enkratno uporabo (nonce) in vrednost težavnosti uporabite pri izračunu zgoščene vrednosti.

hash = sha256(index + timestamp + data + previousHash + diff + nonce)
Algoritem za rudarjenje (proof-of-work) implementirajte s preprostim algoritmom (brute-force), ki bo računal ustrezne zgoščene vrednosti ob spreminjajočem žetonu za enkratno uporabo.

nonce = 0
while(true)
  hash = sha256(index + timestamp + data + previousHash + diff + nonce)
  if( hash ustreza diff ) then 
     return new Block(index, timestamp, data, hash, previousHash, diff, nonce)
  else
     nonce++
end while
Trenutna težavnost v omrežju
Vsa vozlišča v omrežju se morajo strinjati o težavnosti, zato je potrebno definirati pravila kako določiti trenutno težavnost v omrežju. V ta namen dodajte konstanti intervala generiranja blokov in intervala popravka težavnosti. Interval generiranja blokov pove v kakšnem času, se lahko najde nov blok. Za vrednost uporabite enoto časa (npr. 10 sekund - vsakih 10 sekund lahko v verigo vstavimo nov blok). Interval popravka težavnosti pove kako pogosto se bo težavnost spremenila. Za vrednost uporabite število blokov (npr. 10 blokov - po 10 dodanih blokih se bo težavnost spremenila). Zmnožek teh dveh konstant nam pove pričakovan čas generiranja bloka, ki ga uporabimo v algoritmu za popravek težavnosti. Težavnost povečamo za 1, če generiranje traja vsaj 2-krat manj časa kot je pričakovano in pomanjšamo za 1, če generiranje traja vsaj 2-krat dalj časa kot je pričakovano.

previousAdjustmentBlock = Blockchain[Blockchain.length - diffAdjustInterval]
timeExpected = blockGenerationInterval * diffAdjustInterval
timeTaken = latestBlock.timestamp - prevAdjustmentBlock.timestamp

if ( timeTaken < (timeExpected / 2) ) then
   return prevAdjustmentBlock.difficulty + 1 // povečanje težavnosti
else if ( timeTaken > (timeExpected * 2) ) then
   return prevAdjustmentBlock.difficulty - 1 // pomanjšanje težavnosti
else
   return prevAdjustmentBlock.difficulty // težavnost ostane enaka
Validacija časovnih značk in kumulativna težavnost
Časovna značka je pomemben podatek, saj ob uvedbi trenutne težavnosti v omrežju vpliva na težavnost rudarjenja. Zato potrebujemo validacijo časovnih značk. Implementirajte naslednji dve pravili validacije:

blok je ustrezen, če je njegova časovna značka največ 1 minuto večja od našega trenutnega časa
blok v verigi je ustrezen če je njegova časovna značka največ 1 minuto manjša od časovne značke prejšnjega bloka
Zaradi uvedbe težavnosti na nivoju omrežja moramo spremeniti način validacije celotne verige. Ob konfliktih zaradi sočasnosti ne velja več najdaljša veriga, temveč veriga z največjo kumulativno težavnostjo. To je veriga, kjer je bilo potrebno porabiti največ sistemskih sredstev in časa. Izračun kumulativne težavnosti verige je preprost, saj za vsak blok v verigi izračunamo 2block.difficulty  in vrednosti seštejemo.



Ocenjevanje
Osnovno delovanje verige blokov (20 točk)
struktura bloka, povezovanje blokov v verigo (10 točk)
validacija zgoščenih vrednosti, blokov in verige (10 točk)
Ustvarjanje novih blokov (rudarjenje) (30 točk)
razširitev strukture bloka, algoritem proof-of-work
Trenutna težavnost v omrežju (20 točk)
Nadgradnja validacije (20 točk)
validacija časovnih značk (10 točk)
validacija verige s kumulativno težavnostjo (10 točk)
Grafični vmesnik za prikaz delovanja (10 točk)