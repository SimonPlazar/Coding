#include "mymalloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

struct alok_info{
	size_t velikost_alokacije; 	// velikost alokacije uporabljena pri mmap
	size_t stevilo_odsekov;		// trenutno število odsekov
	void *prazen_odsek;			// kazalec na prazen odsek	
};

struct odsek_info{
	size_t velikost_odseka; // velikost odseka
	void *stran;			// kazalec na začetek alocirane strani
};

int preostanek; // preostali prostor v strani
void *trenutna_stran = NULL; // kazalec na trenutno stran

void *ustvari_stran(size_t size);
void *mymalloc(size_t size);
void myfree(void *ptr);

void *mymalloc(size_t size){
	if (size == 0) return NULL;

	if (trenutna_stran == NULL) {
		void *nova_stran = ustvari_stran(size);
		return nova_stran;
	}else{ // ce zadnja stran ni polna (nadaljuj stran)
		size_t velikost_odseka = size + sizeof(struct odsek_info);
		struct alok_info *alok_info = (struct alok_info *)trenutna_stran;
		if (velikost_odseka <= preostanek){ // ce je dovol prostora
			preostanek -= velikost_odseka;
			
			// shranim velikost odseka na pomnilnik
			struct odsek_info *odsek_info = (struct odsek_info *)(alok_info->prazen_odsek);
			odsek_info->velikost_odseka = velikost_odseka;
			odsek_info->stran = alok_info;
			
			alok_info->stevilo_odsekov++;
			alok_info->prazen_odsek = alok_info->prazen_odsek + velikost_odseka;
			
			void *vrnjena_velikost = alok_info->prazen_odsek - size;
			return vrnjena_velikost;
		}else{
			void *nova_stran = ustvari_stran(size);
			return nova_stran;
		}
	}
}

void myfree(void *ptr){
	if (ptr == NULL) return;

	struct odsek_info *odsek_info = (struct odsek_info *)((char *)ptr - sizeof(struct odsek_info));
	struct alok_info *alok_info = (struct alok_info *)odsek_info->stran;
	alok_info->stevilo_odsekov--;
	
	struct alok_info *alok_info_trenutno = (struct alok_info *)trenutna_stran;
	
	if (alok_info->stevilo_odsekov == 0){ //ce spraznemo odsek
		if(alok_info == alok_info_trenutno){
			if(munmap(trenutna_stran, alok_info_trenutno->velikost_alokacije) == -1){
				fprintf(stderr, "Error unmap!\n");
			}
			trenutna_stran = NULL;
		}else{
			if(munmap(alok_info, alok_info->velikost_alokacije) == -1){
				fprintf(stderr, "Error unmap!\n");
			}
		}		
	}
}

void *ustvari_stran(size_t size){
	size_t velikost_odseka = size + sizeof(struct odsek_info);
	size_t velikost_alokacije = velikost_odseka + sizeof(struct alok_info);
	int velikost_strani = getpagesize();
	int ostanek = velikost_alokacije % velikost_strani;
	
	velikost_alokacije += (velikost_strani - ostanek);
	
	trenutna_stran = mmap(NULL, velikost_alokacije, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	if (trenutna_stran == MAP_FAILED) return NULL; // napaka v map
	
	//shranjevanje struktur v pomninik
	struct alok_info *alok_info = (struct alok_info *)trenutna_stran;
	alok_info->velikost_alokacije = velikost_alokacije;
	alok_info->stevilo_odsekov = 1;
	alok_info->prazen_odsek = trenutna_stran + sizeof(struct alok_info) + sizeof(struct odsek_info) + size;
	
	struct odsek_info *odsek_info = (struct odsek_info *)(trenutna_stran + sizeof(struct alok_info));
	odsek_info->velikost_odseka = velikost_odseka;
	odsek_info->stran = trenutna_stran;
	
	preostanek = velikost_alokacije - velikost_odseka - sizeof(struct alok_info);
	
	void *vrnjen_naslov = (char *)odsek_info + sizeof(struct odsek_info);
	return vrnjen_naslov;
}
