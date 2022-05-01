#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <bits/stdc++.h>
#include <iomanip> 

using namespace std;

const char* sc0 =
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"     __|__            \n";

const char* sc1 =
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc2 =
"                      \n"
"                      \n"
"                      \n"
"                      \n"
"       |              \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc3 =
"       .              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc4 =
"       ._ _ _ _ _     \n"
"       | /            \n"
"       |/             \n"
"       |              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc5 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |              \n"
"       |              \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc6 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |        |     \n"
"       |        |     \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc7 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |     \\__|     \n"
"       |        |     \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc8 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |     \\__|__/  \n"
"       |        |     \n"
"       |              \n"
"       |              \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc9 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |     \\__|__/  \n"
"       |        |     \n"
"       |       /      \n"
"       |      /       \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc10 =
"       ._ _ _ _ _     \n"
"       | /      |     \n"
"       |/       0     \n"
"       |     \\__|__/  \n"
"       |        |     \n"
"       |       / \\    \n"
"       |      /   \\   \n"
"      / \\             \n"
"     /   \\            \n";

const char* sc[11] = {sc0, sc1, sc2, sc3, sc4, sc5, sc6, sc7, sc8, sc9, sc10};

struct igralec{
	string ime;
	string geslo;
	string napacneCrke;
	int vpisna_st;
	int napacniPoskusi = 0;
	double cas;
};

int random(int min, int max){
	static bool first = true;
	if(first){  
		srand(time(NULL));
    	first = false;
	}
	return min + rand() % ((max + 1) - min);
}

void vnos(igralec igralci[], string gesla[]){
	for(int i=0;i<5;i++){
		cout << "Ime: ";
		cin >> igralci[i].ime;
		
		cout << "Vpisna stevilka: ";
		cin >> igralci[i].vpisna_st;
		
		igralci[i].geslo = gesla[random(0, 100)];
		
		cout<<igralci[i].geslo<<endl;
	}
}

void sortIgralce(igralec igralci[]){
	igralec temp;
	for(int i = 0; i<5; i++) {
   		for(int j = i+1; j<5; j++){
   			if(igralci[j].napacniPoskusi == igralci[i].napacniPoskusi){
   				if(igralci[j].cas < igralci[i].cas){
   					temp = igralci[i];
      				igralci[i] = igralci[j];
      				igralci[j] = temp;
				   }
			}else if(igralci[j].napacniPoskusi < igralci[i].napacniPoskusi){
      			temp = igralci[i];
      			igralci[i] = igralci[j];
      			igralci[j] = temp;
      		}
   		}
	}
}

bool checkKonec(string geslo){
	for(int i=0;i<geslo.length();i++){
		if(geslo[i] != '0'){
			return false;
		}
	}
	return true;
}

void check(char crka, string &polje, igralec &igralci, string &geslo){
	bool nasel=false;
	
	for(int i=0;i<geslo.length();i++){
		if(crka==geslo[i]){
			polje[i]=crka;
			geslo[i]='0';
			nasel=true;
		}
	}
	
	if(nasel==false){
		igralci.napacniPoskusi++;
	}
}

void igra(igralec igralci[]){
	bool konec;
	string polje;
	string geslo;
	char crka;
	time_t start;
	
	for(int i=0;i<5;i++){
		konec = false;
		
		polje = igralci[i].geslo;
		geslo = igralci[i].geslo;
		
		for(int k=0;geslo[k]!='\0';k++){
			polje[k] = '_';
		}
		
		start = time(0);
		
		cout << "Nova igra: " << igralci[i].ime << endl;
		
		while(igralci[i].napacniPoskusi < 10 && !konec){
			cout << "\nStevilo napacnih poskusov: " << igralci[i].napacniPoskusi << endl;
			
			cout << sc[igralci[i].napacniPoskusi] << endl;
			
			cout << polje << endl;
			
			cout << "Izberi crko: ";
			cin >> crka;
			check(crka, polje, igralci[i], geslo);
			
			konec = checkKonec(geslo);
		}
		
		igralci[i].cas = difftime(time(0), start);
		
		if(konec){
			cout << endl << polje << endl;
			cout << "Zmaga" << endl;
			cout << "Cas: " << igralci[i].cas << endl;
		}
		
		if(igralci[i].napacniPoskusi == 10){
			cout << endl << sc[10] << endl;
			cout << "Poraz" << endl;
			cout << "Cas: " << igralci[i].cas << endl;
		}	
	}
	
	sortIgralce(igralci);
	
	cout << "Najboljsi igralec: " << igralci[0].ime << endl;
	
	cout << "Tekmovalec \t Geslo \t \t Stevilo ugibanj \t Cas" <<endl;
	for(int i=0;i<5;i++){
		cout << setw(17) << left << igralci[i].ime << setw(16) << left << "\""+igralci[i].geslo+"\"" << setw(24) << left << igralci[i].napacniPoskusi << igralci[i].cas<< "s" << endl;
	}
}

int main(int argc, char** argv) {
	igralec igralci[5];
	string gesla[100] = {"appearance", "video", "menu", "sir", "storage", "attention", "satisfaction", "tradition", "science", "member", "excitement", "sector", "engine", "week", "user", "accident", "painting", "cabinet", "literature", "truth", "responsibility", "marriage", "funeral", "efficiency", "success", "instance", "topic", "reflection", "month", "surgery", "estate", "union", "construction", "insect", "conclusion", "throat", "speech", "gate", "college", "possibility", "army", "art", "nature", "philosophy", "independence", "data", "employee", "medicine", "virus", "method", "video", "affair", "memory", "currency", "media", "inflation", "people", "analysis", "reception", "success", "woman", "sector", "message", "attention", "exam", "assistant", "control", "tennis", "population", "hotel", "recognition", "event", "recipe", "topic", "hat", "manager", "orange", "speaker", "storage", "advice", "song", "bonus", "volume", "goal", "writer", "quantity", "analyst", "shopping", "language", "thing", "honey", "membership", "week", "meaning", "candidate", "girl", "ad", "story", "recommendation", "wife"};
	
	vnos(igralci, gesla);
	
	igra(igralci);
	return 0;
}
