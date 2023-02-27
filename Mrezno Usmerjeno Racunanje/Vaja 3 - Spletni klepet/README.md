Vaja 3 - Spletni klepet

Na teh vajah se boste seznanili s komunikacijo programov z vtičnicami (sockets) in komunikacijo procesov z nitmi (threads) na primeru aplikacije za spletni klepet (web chat). Implementirali boste dve aplikaciji (strežnik in odjemalec) kjer bo strežnik konzolna, odjemalec pa okenska/spletna aplikacija. Za komunikacijo med njima boste uporabili vtičnice, po katerih si boste pošiljali sporočila. Sporočila lahko pošiljate v obliki nizov ali binarno. Pri programiranju poskrbite za robustnost obeh aplikacij (uporaba izjem, lep izpis napak pri komunikaciji, ustrezno rokovanje s predhodnim izhodom, ...). 

 

Strežnik naj sprejme nove odjemalce in vodi seznam povezanih odjemalcev. Vsak dogodek (nov uporabnik se prijavi/odjavi, pošlje sporočilo, ...) se naj smiselno izpiše v ukazni vrstici. Strežnik naj prav tako oddaja (broadcast) vsa sporočila vsem povezanim odjemalcem.

 

Odjemalec naj omogoča povezavo na strežnik ob vnosu uporabniškega imena. Nato naj omogoči pošiljanje sporočil na strežnik. Pri tem se naj vsa dobljena sporočila izpisujejo. Izpis naj bo kombinacija uporabnika in njegovega sporočila (npr. [uporabnik] pravi: [sporočilo]).

 



 

Za uspešno implementacijo naloge boste morali definirati protokol. To je dogovor o načinu pošiljanja in obliki sporočil. Protokol zasnujte sami. Pri protokolu uporabite obliko glava-vsebina (header-payload), kjer glava sporočila hrani tip, preostanek pa vsebino sporočila. V primerih na sliki, je protokol sestavljen iz različnih tipov sporočil:

#J|uporabnik1 -> uporabnik1 se je pridružil (join)
#M|zdravo -> sporočilo "zdravo" (message)
Dodatno implementirajte tudi igro ugibanja besed. Na strežniku hranite seznam besed, ki jih nato uporabite pri igri. Beseda naj bo vsem uporabnikom delno skrita tako dolgo, dokler en izmed njih besede ne ugane. Prav tako na strežniku hranite rezultate igre. Igro zaženite in ustavite na ukaz (sporočilo) npr. #GAMESTART in #GAMESTOP.

 





 

Za konec naj se vsa sporočila med strežnikom in odjemalci šifrirajo s poljubnim šifrirnim algoritmom. Bodite pazljivi pri izmenjavi šifrirnih ključev! Strežnik naj vedno dekodira sporočilo, ga prepozna in ga šifriranega razpošlje (broadcast) vsem odjemalcem.

 

Ocenjevanje
Izdelava strežnika in odjemalca (10 točk)
Komunikacija strežnik-odjemalci in protokol (10 točk)
Implementacija klepeta (30 točk)
Implementacija igre ugibanja besed (20 točk)
Šifriranje sporočil (20 točk)
Robustnost kode (izjeme, niti) (10 točk)