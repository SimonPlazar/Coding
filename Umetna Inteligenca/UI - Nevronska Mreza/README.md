# Vaja 3 - Večplastna nevronska mreža

Implementirajte aplikacijo, ki bo s pomočjo večplastne nevronske mreže razpoznavala pisane posamezne simbole. Uporabnik najprej nastavi parametre nevronske mreže in učnega algoritma backpropagation, nato pa vnese po en ali več primerkov vsakega simbola, ki naj se ga nevronska mreža nauči. Vnos poteka v glavno okno aplikacije s pomočjo miške ali poljubne druge vhodne naprave.

   

Vsak narisan znak se najprej pretvori v ustrezno število točk, tako da zaporedno najbližji dve točki zamenjujemo z njunim središčem, dokler ne ostane N+1 točk. Pri tem prvo in zadnjo točko znaka fiksiramo, da ne pride do prehude popačitve. Te določajo N vektorjev, ki jih normaliziramo (t.j. delimo z njihovo dolžino) in tako dobimo vektorski opis znaka. Ta vektorski zapis predstavlja vhod v nevronsko mrežo, ki pričakuje 2N realnih vhodov.

  

Vsi vnešeni simboli se shranijo v seznam, v katerem je vsakemu simbolu prirejena tudi oznaka (niz oz. oznaka simbola, npr. '1' za simbol 1). Po zaključku vnosa se izvede učenje nevronske mreže. Število izhodnih nevronov iz nevronske mreže je določeno s številom simbolov, ki naj jih nevronska mreža prepoznava. Če recimo želimo, da nevronska mreža prepoznava števke od 1 do 6, bo imela 6 izhodov, ki signalizirajo razpoznavo posameznega simbola na vhodu. Z učnim algoritmom backpropagation želimo doseči, da nevronska mreža vrne izhodne vrednosti (1,0,0,0,0,0) kadar na vhod postavimo vektorski zapis simbola 1, izhod (0,1,0,0,0,0) kadar na vhod postavimo simbol 2, itd. Število skritih nevronov, hitrost učenja in meja napake, pri kateri učenje zaključimo, se določi med parametri nevronske mreže. Vsi nevroni naj uporabljajo logistično aktivacijsko funkcijo.

  

Po zaključku učenja aplikacija uporabnika o tem obvesti in mu omogoči vnos simbolov za prepoznavo. Vsak vneseni simbol se sproti pretvori v vektorski zapis in postavi na vhod nevronske mreže. Ta izračuna svoje izhode in signalizira prepoznavo simbola, ki mu je pripadel najvišji izhod. Oznaka prepoznanega simbola se izpiše.

  

Opis algoritma backpropagation najdete v učbeniku, poglavje 10.3.

Vrednost naloge je 10 točk, od tega:

Implementacija nevronske mreže (3 točke)
Implementacija algoritma vzvratnega razširjanja (3 točke)
Vektorizacija znakov (2 točki) <-
Grafični uporabniški vmesnik (2 točki) <-