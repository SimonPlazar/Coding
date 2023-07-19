# RV04: ASM_print

V zbirnem jeziku napišite program, ki izpiše vaše ime, priimek in vpisno številko.

Enak program implementirajte še v jeziku C/C++ in opišite generirane instrukcije (s komentarji v zbirniški kodi, npr. za 5 glavnih kosov), ki jih dobite z uporabo ukaza:
gcc -S program.cpp

POGOSTA VPRAŠANJA (FAQ):
Namigi: Če uporabljate operacijski sistem Windows dodajte okolijski spremenljivki PATH pot do programa NASM. Primer:
set  PATH=%PATH%;"C:\NASM"
Če uporabljate Debianovo distribucijo operacijskega sistema, je potrebno progame samo namestiti. Primer:
sudo apt-get install nasm gcc sasm
Za uporabnike Mac OS X operacijskega sistema pa uporabite http://macappstore.org/nasm/ 32-bitna arhitektura in printf: pazite - printf in scanf med izvajanjem spreminjata registra eax in ecx. 64-bitna arhitektura in printf: https://www.csee.umbc.edu/portal/help/nasm/sample_64.shtml#hello_64.asm 64-bitna arhitektura in prevajanje: če je potrebno, uporabite "gcc -fPIC -fno-pie". Pri vajah lahko uporabljate tudi SASM (Windows: https://sourceforge.net/projects/sasm/, Linux: http://download.opensuse.org/repositories/home:/Dman95/xUbuntu_16.10/amd64/sasm_3.9.0_amd64.deb).
Če želite uporabljati SASM tudi pri tej nalogi in skupaj z učnimi gradivi za nalogo N04, poglejte učno gradivo za npr. nalogo N06 za nastavitve glede uporabe vnosa/izpisa. Poudarek - v učnem gradivu je uporabljen Linux in Windows uporablja drugačne okraske imen funkcij.

Mac M1/M2: 
https://smist08.wordpress.com/2021/01/08/apple-m1-assembly-language-hello-world/

Seznam ukazov: https://github.com/CAS-Atlantic/AArch64-Encoding

macOS 12.0 Makefile:

HelloWorld: HelloWorld.o
	ld -macosx_version_min 12.0.0 -o HelloWorld HelloWorld.o -lSystem -syslibroot `xcrun -sdk macosx --show-sdk-path` -e _start -arch arm64 
HelloWorld.o: HelloWorld.s
	as -o HelloWorld.o HelloWorld.s

Win64: https://estudij.um.si/pluginfile.php/127722/mod_assign/introattachment/0/win64.png?forcedownload=1
win64.png win64.png10. november 2022, 16.21

Vrstni red registrov pri klicu funkcij za arhitekturo x86-64: http://6.s081.scripts.mit.edu/sp18/x86-64-architecture-guide.html

V: Zakaj nastavimo RAX na 0 pri scanf? O: zaradi možnosti C++ klica s spremenljivim številom argumentov (varargs; vir: povezava), ki jih preveri implementacija klica te funkcije v C++.