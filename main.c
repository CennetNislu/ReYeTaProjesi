#include <stdio.h>
#include "restoran.h"
#include "musteri.h"

int anaMenu();

int main(){
    srand(time(NULL));
    int secim=anaMenu();
    while(secim!=0){
        switch(secim){
            case 1: musteriGiris();
                break;
            case 2: restoranGiris();
                break;
            default: printf("Hatali secim!! \n");
                break;
        }
        secim=anaMenu();
    }
    return 0;
}

int anaMenu(){

    int secim;
    printf("\n\n\t1- MUSTERI GIRIS \n");
	printf("\t2- RESTORAN GIRIS \n" ) ;
	printf("\t0- CIKIS \n") ;
	printf("\n\tSeciminiz  :  ") ; scanf("%d", &secim);
	system("cls");
	return secim;

}
