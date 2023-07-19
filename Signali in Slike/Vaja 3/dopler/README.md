Dopplerjev pojav

Gotovo veste, kaj se zgodi, če se vam približuje avtomobil z vklopljeno sireno. V fazi približevanja avtomobila zaznavamo sireno pri višji frekvenci, ko pa se avtomobil oddaljuje zaznavamo nižjo frekvenco. Temu pojavu pravimo Dopplerjev pojav. Enak efekt dobimo, če se gibljemo mi in je izvor zvoka pri miru. Dopplerjev pojav je splošen in ga zaznamo tudi pri elektromagnetnem valovanju. Z njegovo pomočjo, na primer, ocenjujejo hitrost oddaljevanja galaksij (blue/red shift) in merijo hitrosti avtomobilov (radar).

V tej nalogi implementirajte efekt približevanja in oddaljevanja zvočnega izvora v poenostavljenih okoliščinah.

Pripravite modul dopler, ki ima definirano (vsebuje) naslednjo funkcijo:

def dopler_efekt_mono(vzorec : np.ndarray, vektor_fvz : int, oddaljenost : float, hitrost : float) -> np.ndarray:
    pass

    funkcija prejme 4 parametre
        vzorec - vsebuje zvok, nad katerim želimo izvesti Dopplerjev pojav
        vektor_fvz - vzorčevalno frekvenco v hercih, ki opisuje vzorčevalno frekvenco vzorca in generiranega signala
        oddaljenost - v metrih, opiše koliko daleč se nahaja izvor zvoka na začetku in kako daleč stran konča
        hitrost - v metrih na sekundo, ki opiše, kako hitro se izvor zvoka premika proti nam
    funkcija vrne tabelo (tipa numpy ndarray oblike (x, 1))
    vrednosti ustvarjenih vzorcev naj bodo med -1 in 1
    funkcija naj vrne tabelo z ustvarjenim Dopplerjevim efektom nad podan zvok
        dolžina ustvarjenega efekta naj bo enaka času, ki bi izvor zvoka potreboval, da bi iz začetne oddaljenosti prišel do nas, nas prehitel in se od nas oddaljil za enako dolžino
    (38 točk)

Vaša naloga je sledeča. Iz podanega vzorca zvočnega posneta želimo generirati daljši posnetek, ki bi ga lahko posneli, če bi se nam približeval izvor zvoka (zvočnik), ki bi znova in znova na glas predvajal podan kratek vzorec. Pri tem upoštevajte naslednje poenostavitve:

    izvor se približuje s konstantno hitrostjo
    generirati pričnemo, ko je izvor na podani oddaljenosti od snemalca
    generirati končamo, ko je izvor na podani oddaljenosti stran od snemalca
    izvor pelje skozi snemalca (doseže razdaljo 0)
    na razdalji 0 je glasnost zvoka nespremenjena

Nalogo predvidoma rešite v naslednjih korakih:

    generiran signal lahko pripravite v dveh delih: ko se izvor približuje in ko se oddaljuje
    izračunajte dolžino signala v fazi približevanja in v fazi oddaljevanja, potrebovali boste število vzorcev
    ustrezno prevzorčite podan vzorec
        v fazi približevanja se frekvence v vzorcu povečajo, vzorcev mora biti manj
        v fazi oddaljevanja se frekvence pomanjšajo, vzorcev mora biti več
        vzorčenje spremenite tako, da upoštevate gibanje izvora zvoka (Introduction to the Doppler effect, Doppler effect formula for observed frequency in Doppler effect formula when source is moving away)
        splošno enačbo za izračun frekvence zvoka, ki ga oddaja premikajoči se izvor najdete na spletni strani Doppler effect
    prevzorčene vzorce večkrat zlepite skupaj, da dosežete potrebno dolžino
    zlepite skupaj generiran signal oddaljevanja in približevanja
    pripravite tabelo razdalj
        za vsak generiran vzorec izračunate kako daleč je izvor od mikrofona
    iz tabele razdalj izračunajte relativno glasnost zvoka na tej razdalji
        glasnosti bi naj padala s kvadratom razdalje med izvorom in poslušalcem (Why do sounds get softer)
        pazite, kaj se zgodi z glasnostjo pri razdalji 0
        prilagodite izračun tako, da bo predvajan rezultat lepo slišen

Oddaja mora vsebovati python modul dopler.