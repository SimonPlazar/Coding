# Projektna vaja 1 (2022)
 
Pri tej vaji boste implementirali algoritem Quickhull za tvorbo izbočene lupine v 3D. Quickhull, ki ste ga že implementirali v 2D, boste dopolnili z manjšimi nadgradnjami, ki so potrebne, da deluje tudi v 3D. Ker gre za projektno vajo, jo lahko rešite kot skupina.

Najprej boste implementirali generacijo naključnih točk v 3D. Tokrat je dovolj, da podprete le normalno distribucijo točk. Tako dobljen seznam točk nato uporabimo za vhod v algoritem. 3D Quickhull je sestavljen iz dveh korakov: tvorba začetnega tetraedra in "rekurzivno" dodajanje točk.

Tvorba začetnega tetraedra

Poiščemo šest ekstremnih točk: točko z minimalno koordinato X, točko z maksimalno koordinato X, točko z minimalno koordinato Y, točko z maksimalno koordinato Y, točko z minimalno koordinato Z in točko z maksimalno koordinato Z. Izmed teh določimo dve, ki sta med seboj najbolj oddaljeni. Ti dve točki bosta tvorili prvi rob našega tetraedra. Rob nato razširimo s tretjo točko, ki nam določi začetni trikotnik. To storimo tako, da med štirimi preostalimi točkami poiščemo tisto, ki je od roba najbolj oddaljena. Uporabite izračun razdalje med daljico in točko iz prve vaje. Nato moramo določiti še četrto točko začetnega tetraedra. Najprej določimo normalo trikotnika. To storimo z izračunom vektorskega produkta med vektorjema, ki predstavljata dve od stranic trikotnika. Definiramo npr. V1=P2−P1=(x1,y1,z1)
 in V2=P3−P1=(x2,y2,z2)
, kjer so P1
, P2
 in P3
 oglišča trikotnika. Normalo na trikotnik nato izračunamo kot Vn=V1×V2=(y1z2−y2z1,z1x2−z2x1,x1y2−x2y1)
. Vrh tetraedra določimo tako, da v celotni množici točk poiščemo tisto točko, katere vektor od enega od oglišč trikotnika nam da največjo absolutno vrednost skalarnega produkta z normalo trikotnika. Povedano drugače, določimo vektor Vp=P−P1=(xp,yp,zp)
, kjer je P poljubna točka iz množice, nato pa izračunamo absolutno vrednost skalarnega produkta |Vn⋅Vp|
.

  

Dodajanje točk

Definiramo podatkovno strukturo, s katero bomo predstavili trikotnike. Podatkovna struktura mora hraniti vsaj:

indekse oglišč v seznamu točk,
normalo trikotnika (VEDNO mora biti usmerjena izven objekta).
V podatkovno strukturo trikotnika lahko vstavimo tudi seznam točk, ki z normalo trikotnika dajo pozitiven skalarni produkt, in dejanske koordinate točk. Nato ustvarimo sklad, na katerega bomo dodajali trikotnike. S tem se izognemo rekurzivnim klicem funkcije, saj bi z rekurzijo težje obdelali robne primere. Ustvarimo štiri instance strukture trikotnik, ki bodo predstavljali lica začetnega tetraedra. Njihove normale določimo s pomočjo četrte točke. Npr., normalo trikotnika ΔP1P2P3
 določimo s pomočjo točke P4 takole: Vn=V1×V2,V3=P4−P1,o=Vn⋅V3
. V primeru, ko je spremenljivka o večja od 0, moramo vektor normale obrniti, torej Vn=−Vn
.

Tako dobljene začetne trikotnike postavimo na sklad. Dokler sklad ni prazen, dodajamo nove točke v izbočeno lupino po naslednjem postopku:

Vzamemo trikotnik s sklada. Poiščemo točko, ki nam da največjo vrednost skalarnega produkta z normalo trikotnika (POZOR: tukaj ne računamo absolutne vrednosti skalarnega produkta!). Ponovno, če imamo ΔP1P2P3
 in točko P, določimo vektor Vp=P−P1
 in izračunamo skalarni produkt kot Vp⋅Vn
. Če nobena točka ne da pozitivnega skalarnega produkta (trikotnik ne vidi nobene točke), smo s to iteracijo končali.
Pregledamo preostale trikotnike na skladu in poiščemo vse tiste, katerih normalni vektor da pozitivno vrednost skalarnega produkta z izbrano točko. Uporabimo enak način izračuna kot pri prejšnji alineji. Tukaj lahko dobimo dva scenarija:
Z nobenim trikotnikom na skladu nismo dobili pozitivnega skalarnega produkta. To je trivialni primer. Točke trikotnika povežemo z izbrano točko in tvorimo nove robove. Tvorimo nove trikotnike ΔP1P2P,ΔP1P3P,ΔP2P3P
. Njihove normale izračunamo s pomočjo neuporabljene točke izbranega trikotnika (normala mora vedno kazati izven objekta).
Vsaj en trikotnik na skladu nam je dal pozitiven skalarni produkt. V tem primeru definiramo slovar, kjer indeks točke predstavlja ključ, število pojavitev pa vrednost. V slovar vstavimo oglišča vseh trikotnikov, ki so nam dali pozitiven skalarni produkt. Ob vsaki ponovitvi povečamo števec pojavitev te točke. Točke nato ločimo v dve skupini: a) točka se pojavi enkrat ali dvakrat, b) Točka se pojavi več kot dvakrat. Točke b) odstranimo z izbočene lupine. Prav tako odstranimo vse robove, ki imajo katero od krajišč v taki točki. Nato poiščemo vse robove, katerih obe oglišči pripadata množici a). Iz le-teh tvorimo nove robove in trikotnike z novo točko, enako kot v primeru 1. Na koncu iteracije odstranimo vse trikotnike, ki so nam dali pozitiven skalarni produkt s sklada.
Vizualizacija

Za lažjo vizualizacijo 3D podatkov priporočam uporabo programskega jezika Python in knjižnic Numpy ter Matplotlib. Primer programa izgleda takole:

V tem primeru je spremenljivka hull seznam indeksov točk, ki predstavljajo krajišča robov. For zanka se sprehodi skozi vse pare krajišč robov in jih izriše.

Točkovanje

Generacija in prikaz točk v 3D - 1 točka

Tvorba začetnega tetraedra - 2 točki

Algoritem izbočene lupine v 3D - 3 točke