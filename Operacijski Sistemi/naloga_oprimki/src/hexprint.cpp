#include <stdio.h>
#include <getopt.h>
#include <string>
#include <cstring>
#include <iostream>
#include "bits/stdc++.h"
#include <sstream>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

inline bool exists_test(const std::string& name) {
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}

bool isNumber(string& str)
{
    for (char const &c : str) {
       
        if (std::isdigit(c) == 0)
          return false;
    }
    return true;
}

int main(int argc, char** argv){
	int c;
	
	string tmp;
	int FD_IN = 0;
	int FD_OUT = 1;
	string F_IN = "";
	string F_OUT = "";
	bool FLAG_I_F = false;
	bool FLAG_O_F = false;
	
    while ((c = getopt(argc, argv, ":hi:I:o:O:")) != -1) {
        switch (c) {
        case 'h':
			printf ("./hexprint [-h] [-i] [-I] [-o] [-O]\n");
            return 0;
            break;
        case 'i':
			F_IN = optarg;
			FLAG_I_F = true;
            break;
        case 'I':
			tmp = optarg;
			
			if(isNumber(tmp))
				FD_IN = atoi(tmp.c_str());
			else{
				cerr<<"error FD_IN"<<endl;	
				return 1;
			}
            break;
        case 'o':
            F_OUT = optarg;
            FLAG_O_F = true;
            break;
        case 'O':
			tmp = optarg;
			
            if(isNumber(tmp))
				FD_OUT = atoi(optarg);
			else{
				cerr<<"error FD_OUT"<<endl;	
				return 1;
			}
            break;
        case '?':
			printf("napacno stikalo: %c\n", optopt);
			cerr<<"napacno stikalo\n";
			return 1;
        default:
            printf("manjka argument: %c\n", optopt);
            cerr<<"manjka argument:\n";
            return 1;
        }
    }
    
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc) {
            printf ("%s ", argv[optind++]);
        }
        printf ("\n");
        return 1;
    }
    
    if((FD_IN < 0) | (FD_OUT < 0)) {
		cerr<<"neveljaven fd!"<<endl;
		return 1;
	}
    
    char chr;
    string output;
    
    //~ while(EOF != (chr = getchar())){
		//~ if(chr == (char)10) continue;
		
		//~ printf("%#X\n", (int)chr);

	//~ }
	
	//INPUT:
	//file in
	if(FLAG_I_F){
		
		FD_IN = open(F_IN.c_str(), O_RDWR);
		if(FD_IN == -1){
			cerr<<"error datoteka ne obstaja"<<endl;	
			return 1;
		}
		
		std::ostringstream ss;
		
		while(1){
		
			int r = read(FD_IN, &chr, 1);
			if(r == -1){
				cerr<<"error pri branju"<<endl;	
				close(FD_IN);
				return 1;
			}
			if(r == 0) break;
			
			ss << "0x";
			ss << std::uppercase << std::hex << (int)chr;
			ss << "\n";
		}
		
		output = ss.str();
		
		int err = close(FD_IN);
		if(err == -1){
			cerr<<"napaka pri zapiranju"<<endl;	
			return 1;
		}
		
	}else{
	//fd in
		std::ostringstream ss;
		
		while(1){
		
			int r = read(FD_IN, &chr, 1);
			if(r == -1){
				cerr<<"error pri branju"<<endl;	
				return 1;
			}
			if(r == 0) break;
			
			ss << "0x";
			ss << std::uppercase << std::hex << (int)chr;
			ss << "\n";
		}
		output = ss.str();
	}
	
	//OUTPUT
	//file out
	if(FLAG_O_F){
		if(!exists_test(F_OUT)){
			FD_OUT = open(F_OUT.c_str(), O_RDWR | O_CREAT);
			if(FD_OUT == -1){
				cerr<<"error datoteko ni mozno odpret"<<endl;
				return 1;
			}
		}else{
			cerr<<"error datoteka obstaja"<<endl;	
			return 1;
		}
		
		int w = write(FD_OUT, output.c_str(), output.size());
		if(w == -1){
			cerr<<"error pri pisanju"<<endl;	
			close(FD_OUT);
			return 1;
		}
		
		fchmod(FD_OUT, S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IXOTH);
		
		int err = close(FD_OUT);
		if(err == -1){
			cerr<<"napaka pri zapiranju"<<endl;	
			return 1;
		}
	}else{
	//fd out
		int w = write(FD_OUT, output.c_str(), output.size());
		if(w == -1){
			cerr<<"error pri pisanju"<<endl;	
			return 1;
		}
	}
	
	
	return 0;
}
