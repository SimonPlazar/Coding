# Vaja 1 - HTML

Pri naslednjih nalogah boste pisali kodo HTML. Pred oddajo validirajte vaše HTML datoteke z validatorjem. Vse potrebne datoteke (HTML in slike) stisnite v datoteko ZIP in pravočasno oddajte.

Naloga 1 (4 točke):

S poljubnim urejevalnikom besedila ustvarite nov dokument z imenom "index.html". Ustrezno nastavite doctype na HTML5. V html dokumentu definirajte glavo ter telo dokumenta. V glavi html dokumenta dodajte naslov spletne strani ter nastavite kodiranje strani na utf-8.

V html dokument dodajte naslov 'X spletna stran', kjer črko X nadomestite s svojim imenom (npr. "Sandijeva spletna stran"). Besedilo označite kot naslov (Heading).

Pod naslovom ustvarite neoštevilčen seznam, ki bo predstavljal meni spletne strani. V seznam dodajte spletne povezave na:

"Domov", ki vodi na "index.html"
"Ponudba", ki vodi na "ponudba.html"
"Anketa", ki vodi na "anketa.html"
"Vaje", ki vodi na "https://estudij.um.si"
Seznam povezav označite s HTML5 značko za navigacijo. Navigacijo in naslov označite s HTML5 značko za sekcijo glave.

V dokument dodajte besedilo "O meni", ki ga označite kot podnaslov. Pod podnaslov dodajte kratek opis sebe in strani, ki jo ustvarjate. Opis naj vsebuje vsaj 3 povedi, ki jih ločite s HTML značko za prelom vrstice. Opis mora vsebovati:

Vaše ime in priimek, z dodano povezavo na vaš naslov elektronske pošte
Ime fakultete, zapisano krepko
Ime predmeta, ki je podčrtano
Pod odstavek dodajte poljubno sliko, ki ji nastavite 600px širine in 400px višine. Pod sliko zapišite še kratek opis slike. Sliko in komentar slike označite z ustreznima HTML5 značkama (figure in figcaption).

Za sliko dodajte vodoravno črto.

Pod črto vključite poljuben videoposnetek, širino predvajalnika pa nastavite na 600px. Lahko uporabite posnetek iz w3schools.

Pri reševanju si pomagajte z zaslonskim posnetkom.

Naloga 2 (3 točke):

Na spletu poiščite 6 avtomobilov, ki jih boste vključili v ponudbo na vaši spletni strani. Za vsak avtomobil potrebujete naziv, fotografijo, 2 tehnična podatka in ceno.

Ustvarite nov dokument z imenom "ponudba.html". Ustrezno nastavite glavo HTML dokumenta, naslov strani in navigacijo (enako kot pri nalogi 1). V telesu dokumenta ustvarite tabelo, ki ima 3 vrstice in 2 stolpca. Tabeli vključite obrobo širine 1px*. V vsako izmed celic dodajte naziv avtomobila, ki ga označite z značko za naslove (heading). Pod naziv vstavite sliko avtomobila, ki ji nastavite širino 400px in višino 300px. Dodajte povezavo, ki ob kliku na sliko to odpre v novem oknu (zavihku) v originalnih dimenzijah. Pod sliko vstavite še opisni seznam (description list), v katerega zapišete ceno in vsaj 2 tehnični lastnosti avtomobila.

Pred tabelo dodajte zaznamek z vrednostjo 'vrh'. Na konec strani dodajte besedilo 'Na vrh', ki ga označte kot povezavo, ki naj kaže na zaznamek 'vrh' (URL fragment).

Pri reševanju si pomagajte z zaslonskim posnetkom.

*Opomba: Obrobe tabele po standardu HTML5 ni mogoče nastaviti brez uporabe CSS, ki ga bomo spoznali šele pri naslednji vaji. Kljub temu, braskalniki še vedno sprejemajo atribut border, ki ga tokrat lahko izjemoma uporabite.Validator bo v tem primeru javil napako, ki jo lahko ignorirate.

Naloga 3 (3 točke):

Ustvarite nov dokument z imenom "anketa.html". Ustrezno nastavite glavo HTML dokumenta, naslov strani in navigacijo (enako kot pri nalogi 1). V dokument dodajte obrazec, ki bo uporabniku omogočal, da izpolni anketo o avtomobilih.

Obrazec naj poošilja podatke na naslov "anketa.html" po metodi GET. V obrazec dodajte naslednja vnosna polja:

Ime in priimek: besedilo
Kraj: besedilo z možnostjo samodejnega izpolnjevanja (autocomplete) s seznamom (datalist) vsaj 5 večjih slovenskih mest
Elektronska pošta: besedilo
Tip vozila: izbira enega izmed: "Kombilimuzina", "Limuzina", "Enoprostorec", "Karavan", "Terensko vozilo"
Priljubljene znamke: izbira več izmed vsaj 5 različnih avtomobilskih znamk
Želje: večvrstično besedilo, ki mu nastavite širino na 60 znakov in višino na 10 vrstic
Na konec obrazca dodajte gumb "Pošlji", ki pošlje podatke iz obrazca. Preverite ali se poslani podatki pravilno dodajo v naslov URL v obliki parametrov.

Pri reševanju si pomagajte z zaslonskim posnetkom. Če želite, da so vnosna polja poravnana kot na sliki, morate oznake in vnosna polja vstaviti v tabelo: v prvi stolpec tabele oznake, v drugi stolpec pa vnosna polja.