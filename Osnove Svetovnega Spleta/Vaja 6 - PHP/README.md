# Vaja 6 - PHP
 
Pri tej vaji bomo spoznali programski jezik PHP. Programska koda se izvede na strežniku, preden se pošljejo podatki odjemalcu v obliki HTTP odgovora.

Tukaj je datoteka s podatki, ki bo nadomestila podatkovno bazo: prenesi.

Vse datoteke zapakirajte v paket s končnico .ZIP in oddajte na sistem.

Opomba: izgled spletnih strani se ne ocenjuje. Za demonstracijske namene smo na zaslonskih posnetkih uporabili knjižnico Bootstrap.

Naloga 1 (6 točk)
Ustvarite spletno stran index.php. Vanjo vključite datoteko baza.php iz predloge.

Ustvarite glavo spletne strani, ki naj vsebuje naslov in gumb, ki bo služil za prijavo na spletno stran.

Na strani izpišite seznam novic iz polja $novice, ki se nahaja v datoteki baza.php. Izpišite vse podatke o novici, razen njene celotne vsebine. Pri vsaki novici dodajte gumb, ki bo služil kot povezava za branje celotne novice.

Ustvarite spletno stran novica.php. Vanjo vključite datoteko baza.php. Stran naj prebere GET parameter 'id' iz URL naslova. Vrednost parametra predstavlja ID novice, ki se naj prikaže. Poiščite novico s takšnim ID-jem v polju $novice. Če novica s takšnim ID-jem ne obstaja, izpišite opozorilo uporabniku. Če novica obstaja, izpišite vse podatke iz objekta (naslov, povzetek, vsebina, avtor, datum objave).

Na spletni strani index.php, pri vsaki novici dodajte povezavo na gumb za branje celotne novice. Povezava naj vodi na spletno stran novica.php in naj hkrati nastavi GET parameter 'id' v URL naslovu.

Naloga 2 (9 točk)
Ko uporabnik obišče vašo spletno stran, zanj ustvarite sejo. Veljavnost seje naj bo 30 minut in naj se podaljša ob vsaki uporabnikovi aktivnosti.

Ustvarite spletno stran prijava.php, ki naj uporabniku ponudi obrazec za vnos uporabniškega imena ter gesla. Podatki iz obrazca naj se pošljejo na stran prijava.php po metodi POST. Ko strežnik prejme podatke, naj preveri ali uporabnik s takšnim uporabniškim imenom in geslom obstaja v polju $uporabniki, ki je podano v datoteki baza.php (ne pozabite vključiti datoteke baza.php na stran prijava.php). Če je uporabnik vnesel ustrezno uporabniško ime ter geslo, si zapomnite njegovo uporabniško ime v sejni spremenljivki. To bo pomenilo, da je uporabnik prijavljen.  Nato ga preusmerite na index.php. Če prijavni podatki niso pravilni, uporabniku na strani prijava.php izpišite opozorilo.

Ustvarite skripto odjava.php, ki naj počisti in uniči trenutno sejo. Na ta način boste izbrisali shranjeno uporanbiško ime prijavljenega uporabnika. Nato naj uporabnika preusmeri na stran index.php.

Na strani index.php preverite, ali je uporabnik prijavljen. Če ni prijavljen, mu v glavi spletne strani izpišite povezavo na spletno stran prijava.php. Če je prijavljen, mu izpišite pozdrav z njegovim uporabniškim imenom, ki ga imate shranjenega v sejni spremenljivki. Izpišite mu tudi povezavo na stran odjava.php.

Na strani novica.php dodajte preverjanje, ali je uporabnik prijavljen ali ne. Izpišite vsebino novice le, če je uporabnik prijavljen. Če ni prijavljen, mu izpišite opozorilo, naj se prijavi.