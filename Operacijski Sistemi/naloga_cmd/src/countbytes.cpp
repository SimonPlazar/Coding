#include <stdio.h>
#include <getopt.h>
#include <string>
#include <cstring>
#include <iostream>
#include "bits/stdc++.h"

using namespace std;

bool cmp(char ch, char chh) { return int(ch) <= int(chh); }
 
string sortString(string S)
{
    sort(S.begin(), S.end(), cmp);
 
    return S;
}

int main(int argc, char** argv){
	int c;

	string FLAG_SELECT_OPT = "";
	bool FLAG_SELECT = false;
	bool FLAG_LETTERS = false;
	bool FLAG_NUMBERS = false;
	bool FLAG_HEX = false;
	
	if(const char* env_p = std::getenv("SELECT")){
        FLAG_SELECT = true;
        FLAG_SELECT_OPT = env_p;
	}
	
    static struct option long_options[] = {
    /*   NAME       ARGUMENT        FLAG  SHORTNAME (required_argument, optional_argument, no_argument) */
        {"help",    no_argument, 	NULL, 'h'},
        {"letters", no_argument,    NULL, 'l'},
        {"numbers", no_argument, 	NULL, 'n'},
        {"hex", 	no_argument,    NULL, 'x'},
        {"select",  required_argument, 	NULL, 's'},
        {NULL,      0,              NULL, 0}
    };
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "hxs:ln", 
				long_options, &option_index)) != -1) {
        switch (c) {
        case 0:
            printf ("option %s", long_options[option_index].name);
            if (optarg) {
                printf (" with arg %s", optarg);
            }
            printf ("\n");
            break;
        case 'h':
			printf ("./countbytes [-h | --help] [-l | --letters] [-n | --numbers] [-x | --hex] [-s <> | --select=<>] \n");
            return 0;
            break;
        case 'x':
            FLAG_HEX = true;
            break;
        case 's':
            FLAG_SELECT_OPT = optarg;
            FLAG_SELECT = true;
            break;
        case 'l':
            FLAG_LETTERS = true;
            break;
        case 'n':
            FLAG_NUMBERS = true;
            break;
        }
    }
    
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc) {
            printf ("%s ", argv[optind++]);
        }
        printf ("\n");
    }
    
    int arr[256];
    char chr;
	for(int i = 0;i<256;i++) arr[i]=0;
    
    while(EOF != (chr = getchar())){
		if(chr == (char)10) continue;
		arr[(int)chr]++;
	}
	
	if(FLAG_SELECT){ //filter select
		FLAG_SELECT_OPT = sortString(FLAG_SELECT_OPT);
		for(int i = 0;i < FLAG_SELECT_OPT.size();i++){
			if (FLAG_HEX)
				printf("%#x: %d \n", (int)FLAG_SELECT_OPT[i], arr[(int)FLAG_SELECT_OPT[i]]);
			else
				printf("%c: %d \n", FLAG_SELECT_OPT[i], arr[(int)FLAG_SELECT_OPT[i]]);
		}
	}else if(FLAG_LETTERS || FLAG_NUMBERS){ //filter numbers and letters
		for(int i = 0;i < 256;i++){
			if(arr[i] != 0){
				if((FLAG_LETTERS && isalpha((char)i)) || (FLAG_NUMBERS && isdigit((char)i))){
					if(FLAG_HEX){
						printf("%#x: %d \n", i, arr[i]);
					}else{
						printf("%c: %d \n", char(i), arr[i]);
					}
				}
			}
		}
	}else{ //no filtering
		for(int i = 0;i < 256;i++){
			if(arr[i] != 0){
				if(FLAG_HEX){
					printf("%#x: %d \n", i, arr[i]);
				}else{
					printf("%c: %d \n", char(i), arr[i]);
				}
			}
		}
	}
	
	return 0;
}
