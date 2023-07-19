	
Filtriranje signalov

Demonstrirajte znanja filtrov s filtriranjem podanega signala.

Pripravite skripto Python, ki ima definirano (vsebuje) naslednjo funkcijo:

def odstrani_kvadratni_signal(s : np.ndarray, f : float, fvz : int) -> np.ndarray:
    pass
funkcija prejme 3 parametre
s je signal, tabela oblike (n, 1)
f je osnovna frekvenca kvadratnega signala, ki ga želimo odstraniti
fvz je vzorčevalna frekvenca signala s
funkcija vrne filtriran signal oblike (n, 1)
(20 točk)
filtriranje osnovne frekvence (3 točke)
linearna faza (2 točki)
filtriranje ustreznih harmonikov (10 točk)
dobra pasovna širina filtriranih odsekov (5 točk)
Funkcija naj pripravi ustrezne filtre s katerimi bo iz signala odstranila kvadratni signal.

Kvadratni signal je sestavljen iz večih sinusoid: najpomembnejša je ta z osnovno frekvenco f, vsebuje pa tudi višje harmonike. Za kvadratni signal so to lihi večkratniki osnovne frekvence: 3f, 5f, ... vse do vzorčevalne frekvence fvz.

Za filtriranje pripravite banko filtrov - seznam filtrov, skozi katerega enega za drugim spustite signal. Prvi filter odstrani osnovno frekvenco, drugi filter odstrani prvi harmonik, ...

Vsak filter naj bo pripravljen tako, da odstrani majhen pas frekvenc okrog izbrane frekvence (pasovno zaporno filtriranje). Za ustrezno pasovno širino si lahko vnaprej analizirate kvadratni signal z FFT.

Pri filtriranju poskrbite, da bo faza skupnega filtra linearna (ne želimo popačiti drugih elementov signala).

Pripravite še odsek kode, ki omogoča pognati skripto za demonstracijo delovanja:

if __name__ == '__main__':
    pass
naj pripravi testne signale
sami izberite primerno vzorčevalno frekvenco in dolžino signalov tako, da bo oblika jasno vidna v prikazu
kvadratni signal z osnovno frekvenco 10 Hz
žagast signal z osnovno frekvenco 15 Hz
vhodni signal - seštevek kvadratnega in žagastega signala
uporabi pripravljeno funkcijo, da iz vhodnega signala odstrani kvadratni signal (tako dobimo filtriran signal)
z matplotlib prikaže vse signale (kvadratni, žagast, vhodni in filtriran signal)
žagast signal in filtriran signal naj bosta prikazana na skupnem diagramu
jasno označite diagrame in osi
kateri signal je kateri
kakšne so osi in kakšne so prikazane enote
(16 točk)
