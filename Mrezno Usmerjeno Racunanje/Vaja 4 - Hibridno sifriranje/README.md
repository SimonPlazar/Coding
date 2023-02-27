Vaja 4 - Hibridno šifriranje

Izdelajte aplikacijo z grafičnim vmesnikom, ki bo omogočala varen prenos datotek. Varen prenos datotek boste zagotovili z uporabo hibridnega šifriranja (asimetrično in simetrično šifriranje). Izbira algoritmov je poljubna, vendar boste na zagovoru morali utemeljiti izbiro. Aplikacija naj omogoča pošiljanje in prejemanje vsaj treh različnih tipov datotek, ki jih določite sami.

 

Če je aplikacija v vlogi pošiljatelja, naj najprej pošlje svoj javni ključ prejemniku. Zatem naj čaka na javni ključ prejemnika. Po pridobitvi le-tega naj izračuna simetrični ključ iz svojega zasebnega ključa in javnega ključa prejemnika. S simetričnim ključem naj zašifrira izbrano datoteko in jo pošlje prejemniku.

Kadar bo aplikacija v vlogi prejemnika, naj čaka na javni ključ pošiljatelja. Po pridobitvi javnega ključa pošiljatelja, naj pošlje svoj javni ključ. Zatem naj izračuna simetrični ključ s pomočjo svojega zasebnega ključa in javnega ključa pošiljatelja. Nato naj prejme šifrirano datoteko, ki jo dešifrira s pomočjo simetričnega ključa. Datoteko naj shrani v mapo imenovano PREJETO. Komunikacijski protokol zasnujte sami.

 

Pazite na ustrezno rokovanje s podatkovnimi toki na omrežju. Pametno izberite velikosti ključev in šifrirne algoritme.

 

Ocenjevanje
Okenska aplikacija (15 točk)
Komunikacija po omrežju (15 točk)
Varna izmenjava ključa (35 točk)
Šifriranje datotek (35 točk)