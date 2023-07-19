# Vaja 4 (2022)
 
Podobno kot pri drugi vaji izdelajte grafični uporabniški vmesnik, ki bo uporabniku omogočal generiranje N naključnih točk, ki predstavljajo množico χ. Točke χ se morajo nahajati znotraj vašega okna in jih tudi izrišite. V vmesniku omogočite uporabo spodnjih dveh algoritmov za izračun ravninske triangulacije.

Pri vsakem zagonu posameznega algoritma izrišete dobljeno ravninsko triangulacijo. Prav tako izpišete pretečen čas od posameznega algoritma. Za izdelavo aplikacije lahko uporabite poljuben programski jezik.
 
Lastnosti triangulacije so:
- vsak rob pripada točno dvema trikotnikoma


a) Minimalna utežena triangulacija

Triangulacija bo minimizirala dolžino vseh robov. Obstaja več aproksimativnih algoritmov, vendar si bomo na vajah ogledali najenostavnejši algoritem. Algoritem temelji na požrešni metodi in je sestavljen iz naslednjih korakov:
- Povežemo vse točke iz množice χ. Dobimo m = n * (n - 1) / 2 daljic. Ta seznam daljic uredimo glede na njihovo dolžino.  
- Najkrajšo daljico vzamemo kot začetno daljico, ki je zagotovo del triangulacije.
- Preostale daljice obravnavamo po vrstnem redu in jih lahko zavržemo ali sprejmemo. Daljico zavržemo v primeru, če le-ta seka katero izmed že do sedaj sprejetih daljic. V tem primeru, če ne seka nobene, jo dodamo v seznam sprejetih daljic.
- Algoritem prekinite, ko sprejmete 3 * n - 3 - k robov (daljic), kjer je n število točk, k pa število točk na konveksni lupini, saj je triangulacija končana.   


b) Hamiltonova triangulacija

Cilj triangulacije je tvorba trikotniškega traku. Algoritem realizirajte s pomočjo poljubnega (delujočega) algoritma za izgradnjo konveksne lupine iz druge vaje. Triangulacija sestoji iz dveh korakov:
- tvorba spiralnega seznama
- tvorba posplošenega trikotniškega traku nad spiralnim seznamom točk

Spiralni seznam tvorimo tako da:
1. Nad množico χ tvorimo konveksno lupino. 
2. Konveksno lupino ter njene točke si shranimo in jih iz množice χ tudi odstranimo.
3. Nad χ ponovimo korak 1 in 2 dokler ni množica χ prazna.
4. Dobljene konveksne lupine moramo povezati. Označimo najbolj zunanjo lupino kot L = 1 in naslednjo, notranjo lupino, kot L + 1. Za prvo točko v konveksni lupini vzamemo tisto točko, ki ima največjo vrednost y koordinate. Vzamemo zadnjo točko iz L konveksne lupine in jo povežemo s prvo točko L + 1 konveksne lupine. Nato naj bo L = L + 1 in postopek ponavljamo dokler niso povezane vse lupine. S tem, ko smo povezali vse lupine, dobimo spiralno urejen seznam točk S.

Tvorba posplošenega trikotniškega traku:

Kot prvi trikotnik v trikotniškem traku vzamete točke Sa, Sb in Sc, kjer je:
- a indeks zadnje točke v L=1 konveksni lupini,
- b indeks prve točke v L+1 konveksni lupine, 
- ter c indeks prve točke v L konveksni lupini.

Vsi indeksi kažejo na mesto točk v spiralno urejenem seznamu.

Naslednji indeksi naj bodo:

a = b

b = c

c = min(N, b + 1)

Minimalni izraz za indeks c poskrbi da ne presežemo spiralnega seznama (N je število generiranih točk oz. velikost spiralnega seznama) in povzroči da v samem zaključku algoritma tvorimo nekaj potrebnih degeneriranih trikotnikov.

Preden pa lahko trikotnik a,b,c sprejmemo pa preverimo sledeča dva robna pogoja:
- v trikotniku ne sme biti vsebovana naslednja točka spiralnega seznama (naslednji indeks c oziroma naslednja točka od trenutnega b)



- nova povezava ne seka daljic spiralnega seznama (torej, tvorjen trikotnik ne seka predhodnika).





V kolikor se zgodi vsaj en robni primer, moramo tvoriti degeneriran trikotnik. To storimo s preprosto posodobitvijo indeksa c = a. Tako pa bomo tvorili degeneriran trikotnik a, b, a (oz. črto). 



Postopek nadaljujete tako da vzamete naslednje indekse po zgornjem postopku :)

 

Skupno je naloge vredna 9 točk.

3 točk za implementacijo minimalno utežene triangulacije
6 točk za Hamiltonovo triangulacijo