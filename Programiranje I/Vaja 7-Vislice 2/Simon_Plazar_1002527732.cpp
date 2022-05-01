#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <bits/stdc++.h>
#include <iomanip> 
#include <fstream>

using namespace std;

struct igralec;
void sortIgralce(int num, igralec plyr[]);

int stevilo = 10;

int random(int min, int max){
	static bool first = true;
	if(first){  
		srand(time(NULL));
    	first = false;
	}
	return min + rand() % ((max + 1) - min);
}

struct igralec{
	string ime;
	string geslo;
	string napacneCrke;
	int vpisna_st;
	int napacniPoskusi;
	double cas;
}player[10];

struct node
{
    igralec data;
    node *next;
};

class linked_list{
private:
    node *head,*tail;
public:
    linked_list(){
        head = NULL;
        tail = NULL;
    }
    
    node* getHead(){
        return head;
    }
    
    string getHeadName(){
    	node *head;
        return head->data.ime;
    }

    void add_node(igralec n){
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if(head == NULL){
            head = tmp;
            tail = tmp;
        }else{
            tail->next = tmp;
            tail = tail->next;
        }
    }
	
	void display(node *head){
       	node *tmp;
        tmp = head;
        if(tmp == NULL)cout<<"null list"<<endl;
        while (tmp != NULL){
        	cout << setw(17) << left << tmp->data.ime << setw(16) << left << "\"" + tmp->data.geslo + "\"" << setw(24) << left << tmp->data.napacniPoskusi << tmp->data.cas<< "s" << endl;
            tmp = tmp->next;
        }
    }
    
    int Length(node *head){
    	int i=0;
		node *tmp;
        tmp = head;
        while (tmp != NULL){
            tmp = tmp->next;
            i++;
        }
        return i;
	}
    
    void deleteLastNode(node *head){
    	node *tmp = head;
    	while (tmp->next->next != NULL){
    		tmp = tmp->next;
    	}
    	delete tmp->next;
    	tmp->next = NULL;
	}
    
    void sortList(node *head){
		int len = Length(head);
		int i = 0;
    	igralec igr;
    	igralec list[len];
    	node *tmp = head;
    	
    	while (tmp != NULL){
            list[i] = tmp->data;
            tmp = tmp->next;
            i++;
        }
        
		sortIgralce(len, list);
		i = 0;
		tmp = getHead();

		while (tmp != NULL){
            tmp->data = list[i];
            tmp = tmp->next;
            i++;
        }
        deleteLastNode(getHead());
	}
	
	void statistika(node *head){
		ofstream myfile("statistika.txt");
		
		myfile << "Najboljsi igralec: " + head->data.ime << endl;
	
		myfile << "Tekmovalec \t Geslo \t \t Stevilo ugibanj \t Cas" <<endl;
	
		node *tmp = head;
        if(tmp == NULL)cout<<"null list"<<endl;
        while (tmp != NULL){
        	myfile << setw(17) << left << tmp->data.ime << setw(16) << left << "\"" + tmp->data.geslo + "\"" << setw(24) << left << tmp->data.napacniPoskusi << tmp->data.cas<< "s" << endl;
            tmp = tmp->next;
        }   
        
        myfile.close();
	}
    
}list_igralcev;

string rndBeseda(int st){
	string line;
    int a = 0;
    int x = random(0, 9)+10*(st-2);
	
	ifstream myfile;
	myfile.open("besede.txt");

    while (getline(myfile, line)){
        if (a == x){
            return line;
        }
        a++;
    }
	
	myfile.close();
}

void sc(int st){
	string line;
    int n = 9;//st vrstic ki jih bere
    int a = 0;//counter
    int x = 9*(st);//zacetna vrstica
	
	ifstream myfile;
	myfile.open("file.txt");

    while (getline(myfile, line)){
        if (a < (n+x) && a >= x){
            cout << line << endl;
        }
        a++;
    }
	
	myfile.close();
}

void vnos(){
	int dolzina;
	for(int i=0;i<stevilo;i++){
		dolzina = 0;
		
		player[i].napacniPoskusi = 0;
		
		cout << "Ime: ";
		cin >> player[i].ime;
		
		cout << "Vpisna stevilka: ";
		cin >> player[i].vpisna_st;
		
		cout << "Dolzina gesla (2-11): ";
		cin >> dolzina;
		
		while(dolzina < 2 || dolzina > 11){
			if(dolzina > 11) cout << "Predolgo!" << endl;
			if(dolzina < 2) cout << "Prekratko!" << endl;
			cout << "Dolzina gesla (2-11): ";
			cin >> dolzina;
		}
		
		player[i].geslo = rndBeseda(dolzina);
		
		cout<<player[i].geslo<<endl;
	}
}

void sortIgralce(int num, igralec igralci[]){
	igralec temp;
	for(int i = 0; i<num; i++) {
   		for(int j = i+1; j<num; j++){
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

void igra(){
	igralec tempIgr;
	bool konec;
	string polje;
	string geslo;
	char crka;
	time_t start;
	
	for(int i=0;i<stevilo;i++){
		konec = false;
		
		polje = player[i].geslo;
		geslo = player[i].geslo;
		
		for(int k=0;geslo[k]!='\0';k++){
			polje[k] = '_';
		}
		
		start = time(0);
		
		cout << "Nova igra: " << player[i].ime << endl;
		
		while(player[i].napacniPoskusi < 10 && !konec){
			cout << "\nStevilo napacnih poskusov: " << player[i].napacniPoskusi << endl;
			
			sc(player[i].napacniPoskusi);
			
			cout << polje << endl;
			
			cout << "Izberi crko: ";
			cin >> crka;
			check(crka, polje, player[i], geslo);
			
			konec = checkKonec(geslo);
		}
		
		player[i].cas = difftime(time(0), start);
		
		if(konec){
			cout << endl << polje << endl;
			cout << "Zmaga" << endl;
			cout << "Cas: " << player[i].cas << endl;
		}
		
		if(player[i].napacniPoskusi == 10){
			cout << endl;
			sc[10];
			cout << endl;
			cout << "Poraz" << endl;
			cout << "Cas: " << player[i].cas << endl;
		}	
		
		tempIgr = player[i];
		list_igralcev.add_node(player[i]);
		
		if(list_igralcev.Length(list_igralcev.getHead()) > 5){
			list_igralcev.sortList(list_igralcev.getHead());
		}
	}
	list_igralcev.statistika(list_igralcev.getHead());
}

int main(int argc, char** argv) {

	vnos();	

	igra();
	
	return 0;
}
