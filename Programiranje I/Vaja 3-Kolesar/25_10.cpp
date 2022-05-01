#include <iostream>
#include <cmath>
using namespace std;

struct Kolesar{		
	double hitrost,cas_voznje,dolzina_poti,mankajoca_pot;		
	};

double OstanekPoti(double dolzina,double trajanje, double hitrost){
	return (dolzina - trajanje * hitrost);
}

Kolesar Vnos(Kolesar kolesar, double s, double t, int i){
	cout<<"Vnesi hitrost za kolesarja "<<i+1<<" (km/h)! ";
	cin>>kolesar.hitrost;
		
	//cout<<"Vnesi trajanje za kolesarja "<<i+1<<" (h)! ";
	//cin>>kolesar[i].cas_voznje;
	kolesar.cas_voznje=t;		
		
	//cout<<"Vnesi dolzina za kolesarja "<<i+1<<" (km)! ";
	//cin>>kolesar[i].dolzina_poti;	
	kolesar.dolzina_poti=s;
		
	cout<<endl;
		
	kolesar.mankajoca_pot=OstanekPoti(kolesar.dolzina_poti, kolesar.cas_voznje, kolesar.hitrost);
	
	if(kolesar.mankajoca_pot<0){
		kolesar.mankajoca_pot=0;
	}
	
	return kolesar;
}

void IzpisKolesarjev(double celaPot,double Pot, int seq, int st){
	
	int percent= (100-round((Pot/celaPot)*100));
	
	cout<<"Kolesar "<<seq+1<<" ("<<percent<<"%)"<<endl;
	for(int i=0;i<st;i++){
		for(int j=0;j<percent;j++){
			cout<<"*";
		}
		for(int k=0;k<(100-percent);k++){
			cout<<".";
		}
		cout<<endl;
	}
}

int main(int argc, char** argv) {
	
	int st_koles;
	int st_vrstic;
	double t,s;
	
	cout<<"Vpisi stevilo kolesarjev: ";
	cin>>st_koles;
	
	cout<<"Vpisi stevilo vrstic v grafu: ";
	cin>>st_vrstic;
	
	cout<<endl;
	
	cout<<"Vpisi dolzino proge: ";
	cin>>s;
	
	cout<<"Vpisi cas: ";
	cin>>t;
	
	cout<<endl;
	
	Kolesar kolesar[st_koles];
	
	
	
	for(int i=0;i<st_koles;i++){
		kolesar[i]=Vnos(kolesar[i], s, t, i);
	}

	for(int i=0;i<st_koles;i++){
		IzpisKolesarjev(kolesar[i].dolzina_poti,kolesar[i].mankajoca_pot,i,st_vrstic);
	}
	return 0;
}
