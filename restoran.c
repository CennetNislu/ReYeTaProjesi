#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restoran.h"
#define MAX_YEMEK_SAYISI 50
#define MAX_SIPARIS_SAYISI 50
#define SIPARIS_DOSYA "siparisler.txt"
#define YEMEK_DOSYA "yemeklistesi.txt"
#define MUTFAK_DOSYA "mutfak.txt"

struct Siparis siparis_listesi[MAX_SIPARIS_SAYISI];
struct yemek yemek_listesi[MAX_YEMEK_SAYISI];
int yemek_sayisi = 0;
int siparis_sayisi = 0;

void restoranGiris() {
    yemek_listesini_yukle();
    siparisleri_yukle();

    int secim = restoranMenu();
    while (secim != 0) {
        switch (secim) {
            case 1: yemek_ekle();
                break;
            case 2: yemek_guncelle();
                break;
            case 3: yemek_sil();
                break;
            case 4: yemek_listesi_goruntule();
                break;
            case 5: siparisleri_goruntule();
                break;
            case 6: yeni_siparis_onay_red();
                break;
            default:
                printf("Oyle bir secim bulunmamaktadir.\n");
                break;
        }
        secim = restoranMenu();
    }
}

int restoranMenu() {
    int secim;
    printf("\n\tRESTORAN EKRANI\n\n");
    printf("\t1-Yemek Ekle:\n");
    printf("\t2-Yemek Guncelle:\n");
    printf("\t3-Yemek Sil:\n");
    printf("\t4-Yemek Listesi Goruntule:\n");
    printf("\t5-Siparisleri Goruntule:\n");
    printf("\t6-Siparis Onay/Red:\n");
    printf("\t0-Ana Menuye Don:\n");

    printf("\n\tSeciminiz: ");
    scanf("%d", &secim);
    system("cls");
    return secim;
}

void yemek_listesini_yukle() {
    FILE *dosya = fopen(YEMEK_DOSYA, "r");
    if (dosya == NULL) {
        printf("Hata: yemek listesinin bulundugu dosya acilamadi.\n");
        exit(1);
    }
    yemek_sayisi = 0;
    while (fscanf(dosya, "%d %49s %f %d %d", &yemek_listesi[yemek_sayisi].ID,
                  yemek_listesi[yemek_sayisi].ad,
                  &yemek_listesi[yemek_sayisi].fiyat,
                  &yemek_listesi[yemek_sayisi].hazirlanma_suresi,
                  &yemek_listesi[yemek_sayisi].mevcut) == 5) {
        yemek_sayisi++;
    }
    fclose(dosya);
}

void yemek_listesini_kaydet() {
    FILE *dosya = fopen(YEMEK_DOSYA, "w");
    if (dosya == NULL) {
        printf("Hata: yemek listesinin bulundugu dosya acilamadi.\n");
        exit(1);
    }
    for (int i = 0; i < yemek_sayisi; i++) {
        fprintf(dosya, "%d %s %.2f %d %d\n", yemek_listesi[i].ID,
                yemek_listesi[i].ad,
                yemek_listesi[i].fiyat,
                yemek_listesi[i].hazirlanma_suresi,
                yemek_listesi[i].mevcut);
    }
    fclose(dosya);
}

void yemek_listesi_goruntule() {
    printf(" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("| %-10s | %-15s | %-10s | %-17s | %-15s |\n", "Yemek No", "Yemek Adi", "Fiyat", "Hazirlanma Suresi", "Mevcutluk Durumu");
    printf(" ----------------------------------------------------------------------------------\n");
    for (int i = 0; i < yemek_sayisi; i++) {
        printf("| %-10d | %-15s | %-10.2f | %-17d | %-15s |\n", yemek_listesi[i].ID,
               yemek_listesi[i].ad,
               yemek_listesi[i].fiyat,
               yemek_listesi[i].hazirlanma_suresi,
               yemek_listesi[i].mevcut ? "Mevcut" : "Mevcut Degil");
    }
    printf(" ---------------------------------------------------------------------------------\n");
}


void yemek_ekle() {
    if (yemek_sayisi >= MAX_YEMEK_SAYISI) {
        printf("Hata: Yemek eklenecek yer kalmadi.\n");
        return;
    }
    int yeni_id = yemek_id_uret();
    yemek_listesi[yemek_sayisi].ID = yeni_id;

    printf("Yemek Adi: ");
    scanf(" %[^\n]", yemek_listesi[yemek_sayisi].ad);
    printf("Fiyat: ");
    scanf("%f", &yemek_listesi[yemek_sayisi].fiyat);
    printf("Hazirlanma Suresi: ");
    scanf("%d", &yemek_listesi[yemek_sayisi].hazirlanma_suresi);
    printf("Mevcutluk Durumu (1: Mevcut, 0: Mevcut Degil): ");
    scanf("%d", &yemek_listesi[yemek_sayisi].mevcut);

    yemek_sayisi++;
    yemek_listesini_kaydet();

    printf("%d numarali %s yemegi eklendi.\n", yeni_id, yemek_listesi[yemek_sayisi - 1].ad);
}

int yemek_id_uret() {
    int id;
    int benzer_mi;
    do {
        id = rand() % 100 + 1;
        benzer_mi = 1;
        for (int i = 0; i < yemek_sayisi; i++) {
            if (yemek_listesi[i].ID == id) {
                benzer_mi = 0;
                break;
            }
        }
    } while (!benzer_mi);
    return id;
}

void yemek_guncelle() {
    int aranan_id;
    printf("Guncellenecek Yemek ID: ");
    scanf("%d",&aranan_id);

    int index=-1;
    for (int i=0;i<yemek_sayisi;i++){
        if(yemek_listesi[i].ID == aranan_id){
            index=i;
            break;
        }
    }

    if (index!=-1){

        printf("Yemek Bilgileri:\n");
        printf("1. Ad: %s\n", yemek_listesi[index].ad);
        printf("2. Fiyat: %.2f\n", yemek_listesi[index].fiyat);
        printf("3. Hazirlanma Suresi: %d\n", yemek_listesi[index].hazirlanma_suresi);
        printf("4. Mevcutluk Durumu: %s\n", yemek_listesi[index].mevcut ? "Mevcut" : "Mevcut Degil");

        printf("Hangi bilgiyi guncellemek istiyorsunuz?\n");
        printf("1. Ad\n");
        printf("2. Fiyat\n");
        printf("3. Hazirlanma Suresi\n");
        printf("4. Mevcutluk Durumu\n");

        int secim3;
        scanf("%d",&secim3);

        switch(secim3)
        {
            case 1:
                printf("Yeni Yemek Adi: ");
                scanf(" %[^\n]",yemek_listesi[index].ad);
                break;
            case 2:
                printf("Yeni Fiyat: ");
                scanf("%f",&yemek_listesi[index].fiyat);
                break;
            case 3:
                printf("Yeni Hazirlanma Suresi: ");
                scanf("%d",&yemek_listesi[index].hazirlanma_suresi);
                break;
            case 4:
                printf("Yeni Mevcutluk Durumu (1: Mevcut, 0: Mevcut Degil):");
                scanf("%d",&yemek_listesi[index].mevcut);
                break;
            default:
                printf("Hatali secim!!\n");
                return;
        }
        yemek_listesini_kaydet();
        printf("Yemek bilgileri guncellendi.\n");

    }
    else
        printf("Hata: Aranan yemek bulunamadi!!\n");

}

void yemek_sil() {
    int aranan_id;
    printf("Silinecek Yemek ID: ");
    scanf("%d", &aranan_id);

    int index = -1;
    for (int i = 0; i < yemek_sayisi; i++) {
        if (yemek_listesi[i].ID == aranan_id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < yemek_sayisi - 1; i++) {
            yemek_listesi[i] = yemek_listesi[i + 1];
        }
        yemek_sayisi--;
        yemek_listesini_kaydet();
        printf("%d numarali yemek silindi.\n", aranan_id);
    } else {
        printf("Hata: Silinecek yemek bulunamadi.\n");
    }
}

void siparisleri_yukle() {
    FILE *dosya = fopen(SIPARIS_DOSYA, "r");
    if (dosya == NULL) {
        printf("Hata: siparis listesinin bulundugu dosya acilamadi.\n");
        exit(1);
    }
    siparis_sayisi = 0;
    while (fscanf(dosya, "%d %49s %49s %.2f %d %19s", &siparis_listesi[siparis_sayisi].siparisID,
                                                      siparis_listesi[siparis_sayisi].kullanici_adi,
                                                      siparis_listesi[siparis_sayisi].yemek_adi,
                                                      &siparis_listesi[siparis_sayisi].fiyat,
                                                      &siparis_listesi[siparis_sayisi].hazirlanma_suresi,
                                                      siparis_listesi[siparis_sayisi].durum) == 6) {
        siparis_sayisi++;
    }
    fclose(dosya);
}

void siparisleri_kaydet() {
    FILE *dosya = fopen(SIPARIS_DOSYA, "w");
    if (dosya == NULL) {
        printf("Hata: siparis listesinin bulundugu dosya acilamadi.\n");
        exit(1);
    }
    for (int i = 0; i < siparis_sayisi; i++) {
        fprintf(dosya, "%d %s %s %.2f %d %s\n", siparis_listesi[i].siparisID,
                                                siparis_listesi[i].kullanici_adi,
                                                siparis_listesi[i].yemek_adi,
                                                siparis_listesi[i].fiyat,
                                                siparis_listesi[i].hazirlanma_suresi,
                                                siparis_listesi[i].durum);
    }
    fclose(dosya);
}

void siparisleri_goruntule() {
    FILE *dosya = fopen(SIPARIS_DOSYA, "r");
    if (dosya == NULL) {
        printf("Hata: siparis listesinin bulundugu dosya acilamadi.\n");
        return;
    }

    siparis_sayisi = 0;
    char satir[1024];
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        if (strlen(satir) > 0 && satir[strlen(satir) - 1] == '\n') {
            satir[strlen(satir) - 1] = '\0'; // Son satýr karakterini kaldýr
        }
        char *token = strtok(satir, " ");
        if (token != NULL) {
            siparis_listesi[siparis_sayisi].siparisID = atoi(token);
            token = strtok(NULL, " ");
            strcpy(siparis_listesi[siparis_sayisi].kullanici_adi, token);
            token = strtok(NULL, " ");
            strcpy(siparis_listesi[siparis_sayisi].yemek_adi, token);
            token = strtok(NULL, " ");
            siparis_listesi[siparis_sayisi].fiyat = atof(token);
            token = strtok(NULL, " ");
            siparis_listesi[siparis_sayisi].hazirlanma_suresi = atoi(token);
            token = strtok(NULL, " ");
            strcpy(siparis_listesi[siparis_sayisi].durum, token);
            siparis_sayisi++;
        }
    }
    fclose(dosya);

    // Sipariþleri ekrana yazdýrma
    printf(" ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("| %-10s | %-15s | %-10s | %-10s | %-17s | %-10s |\n", "Siparis No", "Kullanici Adi", "Yemek Adi", "Fiyat", "Hazirlanma Suresi", "Durum");
    printf(" -----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < siparis_sayisi; i++) {
        printf("| %-10d | %-15s | %-10s | %-10.2f | %-17d | %-10s |\n", siparis_listesi[i].siparisID,
                                                                        siparis_listesi[i].kullanici_adi,
                                                                        siparis_listesi[i].yemek_adi,
                                                                        siparis_listesi[i].fiyat,
                                                                        siparis_listesi[i].hazirlanma_suresi,
                                                                        siparis_listesi[i].durum);
    }
    printf(" -----------------------------------------------------------------------------------------\n");
}

void yeni_siparis_onay_red() {
    siparisleri_goruntule();
    int aranan_id;
    printf("Onaylanacak/Reddedilecek Siparis ID: ");
    scanf("%d", &aranan_id);
    int index = -1;
    for (int i = 0; i < siparis_sayisi; i++) {
        if (siparis_listesi[i].siparisID == aranan_id) {
            index = i;
            break;
        }
    }
    int islem;
    if (index != -1) {
        printf("1 - Onayla\n0 - Reddet\nSeciminiz: ");
        scanf("%d", &islem);
        FILE *redOnay_dosya = fopen("redOnay.txt", "a");
        if (redOnay_dosya == NULL) {
            printf("Hata: redOnay dosyasi acilamadi.\n");
            return;
        }

        if (islem == 1) {
            strcpy(siparis_listesi[index].durum, "Onaylandi");

            FILE *mutfak_dosya = fopen(MUTFAK_DOSYA, "a");
            if (mutfak_dosya == NULL) {
                printf("Hata: mutfak dosyasi acilamadi.\n");
                fclose(redOnay_dosya);
                return;
            }
            fprintf(mutfak_dosya, "%d %s %s %.2f %d %s\n",  siparis_listesi[index].siparisID,
                                                            siparis_listesi[index].kullanici_adi,
                                                            siparis_listesi[index].yemek_adi,
                                                            siparis_listesi[index].fiyat,
                                                            siparis_listesi[index].hazirlanma_suresi,
                                                            siparis_listesi[index].durum);
            fclose(mutfak_dosya);
        } else if (islem == 0) {
            strcpy(siparis_listesi[index].durum, "Reddedildi");
        }

        // Onaylanan veya reddedilen sipariþi redOnay.txt dosyasýna aktar
        fprintf(redOnay_dosya, "%d %s %s %.2f %d %s\n", siparis_listesi[index].siparisID,
                                                        siparis_listesi[index].kullanici_adi,
                                                        siparis_listesi[index].yemek_adi,
                                                        siparis_listesi[index].fiyat,
                                                        siparis_listesi[index].hazirlanma_suresi,
                                                        siparis_listesi[index].durum);
        fclose(redOnay_dosya);

        // Sipariþi siparis_listesi dizisinden çýkar
        for (int i = index; i < siparis_sayisi - 1; i++) {
            siparis_listesi[i] = siparis_listesi[i + 1];
        }
        siparis_sayisi--;

        // Güncellenmiþ sipariþ listesini kaydetme
        FILE *dosya = fopen(SIPARIS_DOSYA, "w");
        if (dosya == NULL) {
            printf("Hata: siparis listesinin bulundugu dosya acilamadi.\n");
            return;
        }
        for (int i = 0; i < siparis_sayisi; i++) {
            fprintf(dosya, "%d %s %s %.2f %d %s\n", siparis_listesi[i].siparisID,
                                                    siparis_listesi[i].kullanici_adi,
                                                    siparis_listesi[i].yemek_adi,
                                                    siparis_listesi[i].fiyat,
                                                    siparis_listesi[i].hazirlanma_suresi,
                                                    siparis_listesi[i].durum);
        }
        fclose(dosya);

        printf("%d numarali siparis %s olarak guncellendi ve %s dosyasina aktarildi.\n",
               aranan_id, (islem == 1) ? "Onaylandi ve mutfaga gonderildi" : "Reddedildi",
               "redOnay.txt");
    } else {
        printf("Hata: Guncellenecek siparis bulunamadi.\n");
    }
}


// Sipariþleri mutfaða gönderme fonksiyonu
void siparisleri_mutfaga_gonder() {
    FILE *dosya = fopen("mutfak.txt", "w");
    if (dosya == NULL) {
        printf("Hata: mutfak.txt dosyasi acilamadi.\n");
        exit(1);
    }
    for (int i = 0; i < siparis_sayisi; i++) { // Burada global siparis_sayisi kullanýlmalý
        if (strcmp(siparis_listesi[i].durum, "Onaylandi") == 0) {
            fprintf(dosya, "%s\n", siparis_listesi[i].yemek_adi);
        }
    }
    fclose(dosya);
}

