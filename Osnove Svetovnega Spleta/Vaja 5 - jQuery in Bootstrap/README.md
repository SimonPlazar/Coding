# Vaja 5 - jQuery in Bootstrap
 
Pišite čiljivo HTML, CSS in JavaScript kodo, uporabljajte zamike, pišite v več vrsticah in pri JavaScript-u komentirajte funckije oz. večje bloke kode. Pomagajte si s primeri, ki jih najdete na W3Schools, ter z vodiči po jQuery.

Datoteke zapakirajte v paket s končnico .zip in oddajte na sistem.

Naloga 1 (9 točk):
Izdelajte spletno stran opravila.html. Vanjo vključite knjižnjico jQuery. Vključite tudi datoteko script.js, v katero boste zapisali vso Javascript kodo za vašo spletno stran.

Spletna stran bo omogočala vnos vaših opravil v seznam. Sestavljena naj bo iz dveh delov.

Prvi del naj bo seznam kategorij. V njega dodajte vsaj tri kategorije, ki bodo uporabniku prikazane že ob nalaganju strani. Nad seznam dodajte vnosno polje ter gumb, s katerim omogočite dodajanje novega elementa v seznam. Ob izbiri (kliku) na element seznama, naj se ta označi (obarva oz. se mu doda razred). Omgočite, da bo hkrati lahko izbran le en element. Označen element naj bo mogoče nato s pritiskom na gumb "izbriši" odstraniti. Gumb izbriši lahko dodate na poljubno mesto (nad ali pod seznam, v sam element seznama,...).

Drugi del strani naj bo tabela, v kateri definirate glavo (thead) s štirimi stolpci. Prvi naj predstavlja zaporedno številko, drugi opis opravila, tretji kategorijo opravila in četrti datum vnosa opravila. Nad tabelo dodajte vnosno polje in gumb dodaj, pod tabelo pa gumb briši. Po pritisku na gumb dodaj, se doda nov element v tabelo, pri čemer se poveča zaporedna številka, opis opravila je vrednost vnosnega polja nad tabelo, vrednost kategorije pa izbrana kategorija iz prvega dela strani. Na koncu še dodate trenutni čas in datum kot datum dodajanja opravila. Ob kliku na vsako opravilo v tabeli, naj se to označi, pri čemer je mogoče izbrati več elementov. Ob pritisku na gumb briši, se izbrišejo vsi označeni elementi v tabeli. Pri izdelavi uporabljajte JQuery knjižnico.

Seznama kategorij in opravil hranite tudi v lokalni shrambi (local storage). Ob spremembi (vstavljanju ali brisanju) posodobite vrednosti v lokalni shrambi. Ko se spletna stran naloži, iz lokalne shrambe naložite seznam kategorij in opravil. Na tak način se bodo podatki v tabelah ohranili tudi, ko uporabnik osveži spletno stran ali zapre okno brskalnika.

Primer izgleda: slika

Naloga 2 (6 točk):
Stran opravila.html oblikujte s knjižnico Bootstrap. Omogočite mrežno postavitev in dodajte tri vrstice:

Glava (max. širina v mreži)
Dva enako široka dela, prvi za seznam kategorij in drugi za tabelo z opravili.
Noga (max. širina v mreži)
Stran naj bo prilagojena za tablične računalnike (širina md).

Poskrbite, da bo seznam kategorij prikazan kot list-group ter da bo izbran element označen kot aktiven element takšne skupine. Gumbe oblikujte v skladu z Bootstrap temo, pri čemer naj bosta vnostno polje in gumb za dodajanje skupina gumbov (v obeh primerih).

Tabelo oblikujte tako, da bodo vrstice izmenično pobarvane ter da bo imela obrobe. Označene vrstice naj bodo označene z razredom danger, prav tako tudi gumb za brisanje opravil.

Dodajte potrditvena okna pri brisanju elementov. Uporabite Bootstrap modal.