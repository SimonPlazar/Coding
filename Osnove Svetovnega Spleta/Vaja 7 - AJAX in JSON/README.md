# Vaja 7 - AJAX in JSON
 
Naloga 1 (11 točk)

Izdelajte novo datoteko potopi.php. V njej s pomočjo zanke izrišite tabelo dimenzije 10x10. Uporabite CSS sloge, s katerimi nastavite sivo ozadje celic v tabeli, poskrbite pa tudi, da bodo vidni robovi med celicami.

V datoteki potopi.php najprej ustvarite sejo in pripravite sejne spremenljivke, ki jih boste potrebovali. Naključno zgenerirajte položaj ladjice z dolžino 5 v mreži 10x10 polj. Položaj ladjice si hranite v sejni spremenljivki. Priporočam, da si položaj ladjice predstavite kot polje petih točk, pri čemer je vsaka točka svoje polje s koordinatama X in Y. Poleg položaja ladje, v seji hranite tudi število poskusov. Začetno vrednost poskusov nastavite na 0. Ob vsaki osvežitvi spletne strani, naj se generira nov položaj ladje in se ponastavijo vse sejne spremenljivke na privzete začetne vrednosti. Za izpis sejnih spremenljivk v fazi testiranja lahko uporabite naslednjo vrstico kode:

echo '<hr/><pre>' . print_r($_SESSION, 1) . '</pre><hr/>';
Izdelajte datoteko preveri.php, ki s pomočjo GET metode pridobi podatek o vrstici in stolpcu ter izvede preverjanje, ali se v podani celici tabele nahaja ladjica ali ne. Podatka sta lahko podana kar v URL naslovu, na primer: preveri.php?x=3&y=5.

Za preverjanje zadetka morate primerjati podane koordinate z vsemi točkami ladjice, ki jih imate shranjene v sejni spremenljivki. Če najdete ujemanje, potem zadeto točko odstranite iz polja v sejni spremenljivki (funkcija unset).

Če se v sejni spremenljivki ne nahaja nobena točka več, pomeni da je uporabnik potopil vse ladjice.

Ob vsakem klicu skripte preveri.php morate povečati število poskusov, ki ga hranite v sejni spremenljivki.

Datoteka preveri.php naj vrača JSON objekt s tremi lastnostmi:

zadetek: true/false, pove ali se v celici podani z x in y koordinato v GET metodi nahaja ladjica
konec: true/false, pove ali je uporabnik potopil vse ladjice
poskusi: število poskusov, ki jih je uporabnik porabil do zdaj
Datoteko potopi.php dopolnite z Javascript kodo. Dovoljena je uporaba knjižnice jQuery. Ob vsakem kliku na posamezno celico v tabeli, morate pridobiti koordinate kliknjene celice. Nato generirate AJAX klic na stran preveri.php in ji podate ustrezne koordinate. Kot odgovor prejmete JSON objekt, ki ga vrača datoteka preveri.php.

Če je uporabnik zadel ladjico, kliknjeno celico obarvajte rdeče. V nasprotnem primeru jo obarvajte modro. V vsakem primeru onemogočite dogodek ob kliku na kliknjeno celico.

Če je uporabnik potopil zadnjo točko ladjice, mu izpišite obvestilo (alert) o uspešnem zaključku in število poskusov, ki jih je potreboval za dokončanje. Prav tako onemogočite dogodke ob kliku za vse celice v tabeli.

Naloga 2 (4 točke)
Nadgradite nalogo 1 tako, da namesto ene ladjice generirate 5 ladjic: 1x5, 1x4, 2x3 in 1x2. Ladjice se med seboj ne smejo prekrivati. Ustrezno spremenite zmagovalni pogoj, da mora uporabnik potopiti vseh 5 ladjic.

Omogočite tudi ponastavitev igre na začetno stanje brez osvežitve strani. Dodajte gumb »nova igra«, ki bo s pomočjo AJAX klica poklical skripto ponastavi.php. Ta naj generira nove položaje ladjic in nastavi sejne spremenljivke na privzete začetne vrednosti. Po izvedbi AJAX klica morate poskrbeti še, da imajo vse celice v tabeli dodan dogodek, ki ob kliku na celico pokliče skripto preveri.php.