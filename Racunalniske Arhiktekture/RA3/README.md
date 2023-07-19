# RV03: UTF-8

Napišite program (npr. v C++, dovoljena uporaba cin, cout in string brez ostalih knjižnic!), ki bo kodiral in dekodiral znake po standardu Unicode v kodiranju UTF-8.

Univerzalni nabor znakov (UCS - Universal Character Set, ISO/IEC 10646), ki jih UTF-8 kodira, obsega 1114111 znakov, tj. 10FFFF (hex).

Pri tem kodi 0xFF in 0xFE nista dovoljeni in ob dekodiranju takšne kode izpišite opozorilo o napaki.
Ob izpisu kontrolnih znakov izpišite samo njihovo zaporedno kodno številko UCS-4. (Če imate vnos/izpis HEX ali BIN, lahko preskočite to točko.)
Pri dekodiranju opozorite na dekodiranje manjšega števila, kot dovoljuje bajtni nabor (npr. 0xC0, 0x80 je enako 0x00)
Vnos podatkov: pri kodiranju lahko vnesete binarni niz, heksadecimalni ali kar celo desetiško število (integer), izpis pa naj bo število v binarni ali heksadecimalni obliki (koda UTF-8 ni potrebno izpisati v obliki znaka na ekran). Pri dekodiranju vnesite heksadecimalno število ali binarno število, kot rezultat izpišete lahko tudi celo desetiško število. IZBERITE ENEGA OD načinov vnosa/izpisa (HEX ali BIN ali DEC), ni potrebno vseh kombinacij (npr. HEX+BIN).

PRIMER:

Vnesite število za kodiranje: 03 A9
Rezultat kodiranja UTF-8 je: CE A9
Vnesite kod UTF-8 za dekodiranje: CE A9
Rezultat dekodiranja UTF-8 je: 03 A9