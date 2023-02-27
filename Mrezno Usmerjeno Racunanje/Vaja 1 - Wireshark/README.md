Vaja 1 - Wireshark (ICMP, HTTP)

Na vajah boste spoznali orodje za analizo omrežnih protokolov Wireshark (packet sniffer). Orodje se uporablja pri odpravljanju omrežnih in aplikacijskih težav, podpira analizo več sto omrežnih protokolov in deluje na mnogih platformah, kot so Windows, Linux in OS X. Orodje in uporabniška navodila se nahajajo na uradni strani.

 

Pri vaji bomo obdelali protokola ICMP in HTTP. Pri vsakem izmed protokolov je potrebno odgovoriti na zastavljena vprašanja.  Vrednost vprašanja v točkah je zapisana zraven vprašanja. Vprašanja in odgovore zapišite v datoteko (.DOC/.DOCX/.ODT/.PDF) ter jih opremite s slikami.

ICMP
Protokol ICMP(Internet Control Message Protocol) se uporablja za pošiljanje nadzornih sporočil in sporočil stanja internet omrežja. Pakete ICMP razlikujemo po tipu sporočila, ki ga nosijo. To je lahko zahteva, odgovor na zahtevo, statusna informacija in vrsta napake. Ti paketi ne vsebujejo izvornih in ciljnih vrat, pač pa tip sporočila, ki ima številsko oznako.

V tem sklopu boste generirali ICMP sporočila s programom ping. Zaženite orodje Wireshark ter začnite z analizo omrežnih protokolov. Nato v ukazni vrstici (cmd) izvedite ukaz ping na stran www.feri.um.si:

ping -n 10 www.feri.um.si

 

Poskusite enako še na operacijskem sistemu Linux z ukazom:

ping -c 10 www.feri.um.si

 

Odgovorite na vprašanja za oba operacijska sistema:


Koliko paketov se dejansko prenese med izvorom in ciljem? (5 točk)
Kakšnega tipa so paketi za zahtevo in kakšnega tipa so paketi za odgovor? (5 točk)
Zapišite MAC naslov mrežne kartice, ki se nahaja v ciljnem računalniku. (5 točk)
Koliko zlogov se prenaša v polja "Data" in kakšna je vsebina polja? (5 točk)
Komentirajte razlike in podobnosti med izvedbo ukaza ping na sistemu Windows in Linux. Razlike utemeljite. (10 točk)
HTTP
Protokol HTTP je komunikacijski protokol med odjemalci in strežniki. HTTP odjemalec (npr. spletni brskalnik) zahtevo začne tako, da vzpostavi TCP povezavo na izbranih vratih na oddaljenem gostitelju (privzeta številka vrat je 80). HTTP strežnik na teh vratih pričakuje, da bo odjemalec poslal svoj zahtevek, ki se ponavadi začne z:

GET / HTTP/1.1

 

Ko strežnik prejme tak zahtevek in morebitno sporočilo, na to odgovori npr. z "200 OK" (če ni prišlo do napake) in lastnim sporočilom, katerega vsebina je npr. vsebina spletne strani, zahtevana datoteka ali pa kaka druga informacija.

Zaženite orodje Wireshark in začnite z analizo omrežnih protokolov. Nato s spletnim brskalnikom obiščite spletno stran http://www.httpvshttps.com/ ter počakajte, da se vsebina spletne strani v celoti prenese.

Zapišite IP naslov vašega računalnika, IP naslov strežnika in različico HTTP protokola. (5 točk)
V katerih jezikih želi vaš spletni brskalnik sprejeti vsebino spletne strani? Kako se imenuje polje protokola HTTP v katerem so definirani jeziki? (5 točk)
Koliko zlogov je bilo prenešenih na vaš računalnik (vsebina HTML strani, CSS, JavaScript, Flash, slike, ...)? Koliko časa (v sekundah) je preteklo od prve zahteve vašega spletnega brskalnika do zadnje prenešene vsebine iz spletnega strežnika? (5 točk)
Kakšne statusne kode in koliko le-teh je vrnil spletni strežnik? (5 točk)
Tvorite graf poteka prometa (flow graph) za protokol HTTP in pokomentirajte stanje. (10 točk)
Ocenjevanje časa HTTP prenosa
Čas, ki preteče od trenutka pošiljanja zahteve do trenutka prejemanja odgovora imenujemo čas prenosa(round-trip time). Slednjega označujemo s kratico RTT in ga merimo v milisekundah. Ko z brskalnikom pošljemo zahtevo strežniku, se vzpostavi HTTP povezava, ki je lahko:

nepersistentna povezava
nepersistentna povezava s paralelnimi povezavami
persistentna povezava brez cevovodov
persistentna povezava s cevovodi
V tem sklopu vaje boste ocenili čas HTTP prenosa pri predpostavki, da imamo 1 HTML dokument s 4 slikami. Pri tem bomo izračun poenostavili s sklepom, da je vseh 5 datotek enake velikosti. Čas prenosa ene datoteke naj bo 0.75 RTT, čas trajanja enega RTT pa 120 ms. Pri nepersistentni povezavi s paralelnimi povezavami imejmo 3 paralelne povezave. S spodnjimi enačbami ocenite čas HTTP prenosa v milisekundah za vsako vrsto povezave. Izračun za vsako vrsto povezave je vreden 10 točk.

 

Nepersistentna povezava

vaja1_nepersistentna_povezava

 

Nepersistentna povezava s paralelnimi povezavami

vaja1_nepersistentna_povezava_paralelno

 

Persistentna povezava brez cevovodov

vaja1_persistentna_povezava

 

Persistentna povezava s cevovodi

vaja1_persistentna_povezava_cevovodi