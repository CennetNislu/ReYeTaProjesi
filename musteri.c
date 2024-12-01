#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "musteri.h"

#define MAX_YEMEK_SAYISI 50
#define MAX_USERS 100
#define MAX_KULLANICI_UZUNLUK 50
#define MAX_SIFRE_UZUNLUK 50
#define MAX_YEMEK_ADI 50
#define FILENAME "kullanicilar.txt"
#define SIPARIS_DOSYA "siparisler.txt"
#define YEMEK_DOSYA "yemeklistesi.txt"
#define MUTFAK_DOSYA "mutfak.txt"
#define MAX_SIPARIS_SAYISI 100



void musteriGiris(){
    struct kullanici kullanicilar[MAX_USERS];
    struct musSiparis siparis_listesi[MAX_SIPARIS_SAYISI];
    int siparis_sayisi=0;
    int kullaniciSayisi = 0;
    int yemekSayisi = 0;
    struct Yemek yemekler[MAX_YEMEK_SAYISI];

    FILE *file = fopen(FILENAME, "a+");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    // Dosyadan kullanýcý bilgilerini oku
    while (fscanf(file, "%49s %49s", kullanicilar[kullaniciSayisi].kullaniciAdi, kullanicilar[kullaniciSayisi].sifre) == 2) {
        kullaniciSayisi++;
        if (kullaniciSayisi >= MAX_USERS) {
            break;
        }
    }

    fclose(file);

    YemekListesiOku(yemekler, &yemekSayisi);
    musSiparis_yukle(siparis_listesi , &siparis_sayisi);

    int secim = musteriMenu1();
    while (secim != 0) {
        struct kullanici *aktifKullanici = NULL;
        switch (secim) {
            case 1:
                kaydol(kullanicilar, &kullaniciSayisi);
                break;
            case 2:
                aktifKullanici = girisYap(kullanicilar, kullaniciSayisi);
                if (aktifKullanici != NULL) {
                    int secim2 = siparisMenu();
                    while (secim2 != 0) {
                        switch (secim2) {
                            case 1:
                                siparisVer(aktifKullanici, yemekler, yemekSayisi, siparis_listesi, &siparis_sayisi);
                                break;
                            case 2:
                                siparisDurumu(aktifKullanici);
                                break;
                            case 3:
                                oncekiSiparisler(aktifKullanici, siparis_listesi, siparis_sayisi);
                                break;
                            case 4:
                                mevcutYemekListele(yemekler, yemekSayisi);
                                break;
                            default:
                                printf("Gecersiz secim!! Lutfen tekrar deneyiniz.\n");
                                break;
                        }
                        secim2 = siparisMenu();
                    }
                }
                break;
            case 3:
                kullaniciListele(kullanicilar, kullaniciSayisi);
                break;
            default:
                printf("Oyle bir secim bulunmamaktadir!\n");
                break;
        }
        secim = musteriMenu1();
    }
}

int musteriMenu1() {
    int secim;
    printf("\n\tMUSTERI GIRIS EKRANI \n\n");
    printf("\t1- Kayit Ol\n");
    printf("\t2- Giris Yap \n");
    printf("\t3- Kullanici Listele  \n");
    printf("\t0- Ana Menuye don \n");
    printf("\n\tSeciminiz  :  ");
    scanf("%d", &secim);
    system("cls");
    return secim;
}

void kaydol(struct kullanici *kullanicilar, int *kullaniciSayisi) {
    char kullaniciAdi[MAX_KULLANICI_UZUNLUK];
    char sifre[MAX_SIFRE_UZUNLUK];

    printf("Kullanici Adi: ");
    scanf("%49s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%49s", sifre);
    system("cls");

    for (int i = 0; i < *kullaniciSayisi; i++) {
        if (strcmp(kullanicilar[i].kullaniciAdi, kullaniciAdi) == 0) {
            printf("Bu kullanici adi zaten alinmis!\n");
            return;
        }
    }

    if (*kullaniciSayisi < MAX_USERS) {
        strcpy(kullanicilar[*kullaniciSayisi].kullaniciAdi, kullaniciAdi);
        strcpy(kullanicilar[*kullaniciSayisi].sifre, sifre);
        (*kullaniciSayisi)++;
        printf("Kayit basarili!\n");

        dosyayaEkle(kullanicilar, *kullaniciSayisi);

    } else {
        printf("Maksimum kullanici sayisina ulasildi!\n");
    }
}

struct kullanici* girisYap(struct kullanici *kullanicilar, int kullaniciSayisi) {
    char kullaniciAdi[MAX_KULLANICI_UZUNLUK];
    char sifre[MAX_SIFRE_UZUNLUK];

    printf("Kullanici Adi: ");
    scanf("%49s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%49s", sifre);
    system("cls");

    for (int i = 0; i < kullaniciSayisi; i++) {
        if (strcmp(kullanicilar[i].kullaniciAdi, kullaniciAdi) == 0 && strcmp(kullanicilar[i].sifre, sifre) == 0) {
            printf("Giris Yapildi! Siparis menusunune geciliyor...\n");
            return &kullanicilar[i];
        }
    }

    printf("Giris basarisiz. Kullanici adi ya da sifre yanlis!\n");
    return NULL;
}

void kullaniciListele(struct kullanici *kullanicilar, int kullaniciSayisi) {
    printf("Kullanicilar:\n");
    for (int i = 0; i < kullaniciSayisi; i++) {
        printf("Kullanici Adi: %s\n", kullanicilar[i].kullaniciAdi);
    }
    printf("\n");
}

void dosyayaEkle(struct kullanici *kullanicilar, int kullaniciSayisi) {
    FILE *dosya = fopen(FILENAME, "w");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < kullaniciSayisi; i++) {
        fprintf(dosya, "%s %s\n", kullanicilar[i].kullaniciAdi, kullanicilar[i].sifre);
    }

    fclose(dosya);
}

// Yemek Listeleri

void YemekListesiOku(struct Yemek *yemekler, int *yemekSayisi) {
    FILE *file = fopen(YEMEK_DOSYA, "r");
    if (file == NULL) {
        printf("Yemek listesi dosyasi acilamadi!\n");
        return ;
    }
    *yemekSayisi = 0;

    while (fscanf(file, "%d %49s %f %d %d",&yemekler[*yemekSayisi].ID,
                                            yemekler[*yemekSayisi].ad,
                                            &yemekler[*yemekSayisi].fiyat,
                                            &yemekler[*yemekSayisi].hazirlanmaSuresi,
                                            &yemekler[*yemekSayisi].mevcut) == 5) {

        (*yemekSayisi)++;

        if (*yemekSayisi >= MAX_YEMEK_SAYISI) {
            break;
        }
    }

    fclose(file);
}

void mevcutYemekListele(struct Yemek *yemekler, int yemekSayisi) {
    printf("Mevcut Yemekler:\n");
    printf(" ----------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-15s | %-20s |\n", "Yemek No", "Yemek Adi", "Fiyat", "Hazirlanma Suresi");
    printf(" ----------------------------------------------------------------------------\n");
    for (int i = 0; i < yemekSayisi; i++) {
        if (yemekler[i].mevcut == 1) {
            printf("| %-10d | %-20s | %-15.2f | %-20d |\n", i + 1, yemekler[i].ad, yemekler[i].fiyat, yemekler[i].hazirlanmaSuresi);
        }
    }
    printf(" -----------------------------------------------------------------------------\n");
}



int siparisMenu() {
    int secim;
    printf("\n\tSIPARIS MENU \n\n");
    printf("\t1- Siparis Ver\n");
    printf("\t2- Siparis Durumu Goruntule\n");
    printf("\t3- Onceki Siparisleri Goruntule \n");
    printf("\t4- Yemek Listele\n");
    printf("\t0- Ana Menuye don \n");
    printf("\n\tSeciminiz  :  ");
    scanf("%d", &secim);
    system("cls");
    return secim;
}


void musSiparis_yukle(struct musSiparis *siparis_listesi, int *siparis_sayisi){

    FILE *file=fopen(SIPARIS_DOSYA,"r");

    if(file==NULL){
        perror("Dosya acilamadi.\n");
        exit(1);
    }

    *siparis_sayisi=0;
    while(fscanf(file, "%d %s %s %.2f %d %s", &siparis_listesi[*siparis_sayisi].siparisId,
                                              siparis_listesi[*siparis_sayisi].kullaniciAdi,
                                              siparis_listesi[*siparis_sayisi].yemekAdi,
                                              &siparis_listesi[*siparis_sayisi].fiyat,
                                              &siparis_listesi[*siparis_sayisi].hazirlanmaSuresi,
                                              siparis_listesi[*siparis_sayisi].onayRed)==6){
        (*siparis_sayisi)++;
    }
    fclose(file);
}

void musSiparis_kaydet(struct musSiparis *yeniSiparis){
    FILE *file=fopen(SIPARIS_DOSYA,"a");
    if (file==NULL){
        perror("Dosya acilamadi.\n");
        exit(1);
    }
    fprintf(file, "%d %s %s %.2f %d %s\n",   yeniSiparis->siparisId,
                                             yeniSiparis->kullaniciAdi,
                                             yeniSiparis->yemekAdi,
                                             yeniSiparis->fiyat,
                                             yeniSiparis->hazirlanmaSuresi,
                                             yeniSiparis->onayRed);
    fclose(file);
}


void siparisVer(struct kullanici *aktifKullanici, struct Yemek *yemekler, int yemekSayisi,struct musSiparis *siparis_listesi, int *siparis_sayisi){

    int yemekNo;
    mevcutYemekListele(yemekler,yemekSayisi);
    printf("Siparis vermek istediginiz yemegin numarasini giriniz: ");
    scanf("%d", &yemekNo);
    yemekNo--;

    int yeniId = siparis_id_uret(siparis_listesi);

    if (yemekNo>=0 && yemekNo<yemekSayisi && yemekler[yemekNo].mevcut){
        struct musSiparis yeniSiparis;
        yeniSiparis.siparisId = yeniId;//rand deðiþtirilcek
        strcpy(yeniSiparis.kullaniciAdi,aktifKullanici->kullaniciAdi);
        strcpy(yeniSiparis.yemekAdi, yemekler[yemekNo].ad);
        yeniSiparis.fiyat=yemekler[yemekNo].fiyat;
        yeniSiparis.hazirlanmaSuresi=yemekler[yemekNo].hazirlanmaSuresi;
        strcpy(yeniSiparis.onayRed,"Beklemede");


        siparis_listesi[*siparis_sayisi]=yeniSiparis;
        (*siparis_sayisi)++;

        musSiparis_kaydet(&yeniSiparis);

        printf("Siparisiniz alinmistir.\n");

    }
    else
        printf("Gecersiz yemek numarasi girdiniz. Tekrar deneyiniz.\n");

}

void siparisDurumu(struct kullanici *aktifKullanici) {
    FILE *file = fopen(SIPARIS_DOSYA, "r");
    if (!file) {
        printf("Siparis dosyasi acilamadi.\n");
        return;
    }

    struct musSiparis siparis;
    struct musSiparis siparisler[MAX_SIPARIS_SAYISI];
    int siparis_sayisi = 0;
    int siparisVarMi = 0;

    // Dosyadaki tüm sipariþleri oku
    while (fscanf(file, "%d %s %s %f %d %s",  &siparis.siparisId,
                                              siparis.kullaniciAdi,
                                              siparis.yemekAdi,
                                              &siparis.fiyat,
                                              &siparis.hazirlanmaSuresi,
                                              siparis.onayRed) == 6) {
        siparisler[siparis_sayisi++] = siparis;
    }

    fclose(file);

    // Aktif kullanýcýnýn beklemede olan sipariþlerini yazdýr
    printf("Aktif siparisleriniz: \n");
    printf(" -------------------------------------------------------------------------------\n");
    printf("| %-10s | %-15s | %-10s | %-20s | %-10s |\n",
           "Siparis ID", "Yemek Adi", "Fiyat", "Hazirlanma Suresi", "Durum");
    printf(" -------------------------------------------------------------------------------\n");

    for (int i = 0; i < siparis_sayisi; i++) {
        if (strcmp(siparisler[i].kullaniciAdi, aktifKullanici->kullaniciAdi) == 0 &&
            strcmp(siparisler[i].onayRed, "Beklemede") == 0) {
            printf("| %-10d | %-15s | %-10.2f | %-20d | %-10s |\n",siparisler[i].siparisId,
                                                                   siparisler[i].yemekAdi,
                                                                   siparisler[i].fiyat,
                                                                   siparisler[i].hazirlanmaSuresi,
                                                                   siparisler[i].onayRed);
            siparisVarMi = 1;
        }
    }

    printf(" -------------------------------------------------------------------------------\n");

    if (!siparisVarMi)
        printf("Aktif siparisiniz bulunmamaktadir.\n");
}




void oncekiSiparisler(struct kullanici *aktifKullanici, struct musSiparis *siparis_listesi, int siparis_sayisi) {
    struct musSiparis siparisler[MAX_SIPARIS_SAYISI];
    int toplamSiparisSayisi = 0;

    // MUTFAK_DOSYA dosyasýný oku
    FILE *file = fopen(MUTFAK_DOSYA, "r");
    if (!file) {
        printf("Mutfak dosyasi acilamadi.\n");
        return;
    }

    // Dosyadaki tüm sipariþleri oku
    while (fscanf(file, "%d %s %s %f %d %s",  &siparisler[toplamSiparisSayisi].siparisId,
                                              siparisler[toplamSiparisSayisi].kullaniciAdi,
                                              siparisler[toplamSiparisSayisi].yemekAdi,
                                              &siparisler[toplamSiparisSayisi].fiyat,
                                              &siparisler[toplamSiparisSayisi].hazirlanmaSuresi,
                                              siparisler[toplamSiparisSayisi].onayRed) == 6) {
        toplamSiparisSayisi++;
    }

    fclose(file);

    // REDONAY_DOSYA dosyasýný oku
    file = fopen("redOnay.txt", "r");
    if (!file) {
        printf("Red/Onay dosyasi acilamadi.\n");
        return;
    }

    // Dosyadaki tüm sipariþleri oku
    while (fscanf(file, "%d %s %s %f %d %s",  &siparisler[toplamSiparisSayisi].siparisId,
                                              siparisler[toplamSiparisSayisi].kullaniciAdi,
                                              siparisler[toplamSiparisSayisi].yemekAdi,
                                              &siparisler[toplamSiparisSayisi].fiyat,
                                              &siparisler[toplamSiparisSayisi].hazirlanmaSuresi,
                                              siparisler[toplamSiparisSayisi].onayRed) == 6) {
        toplamSiparisSayisi++;
    }

    fclose(file);

    // Aktif kullanýcýnýn tamamlanmýþ (hazýrlanmýþ veya reddedilmiþ) sipariþlerini yazdýr
    int siparisVarMi = 0;
    printf("Onceki siparisleriniz: \n");
    printf(" -------------------------------------------------------------------------------\n");
    printf("| %-10s | %-15s | %-10s | %-20s | %-10s |\n",
           "Siparis ID", "Yemek Adi", "Fiyat", "Hazirlanma Suresi", "Durum");
    printf(" -------------------------------------------------------------------------------\n");

    for (int i = 0; i < toplamSiparisSayisi; i++) {
        if (strcmp(siparisler[i].kullaniciAdi, aktifKullanici->kullaniciAdi) == 0 &&
            (strcmp(siparisler[i].onayRed, "Hazirlandi") == 0 || strcmp(siparisler[i].onayRed, "Reddedildi") == 0)) {
            printf("| %-10d | %-15s | %-10.2f | %-20d | %-10s |\n",siparisler[i].siparisId,
                                                                   siparisler[i].yemekAdi,
                                                                   siparisler[i].fiyat,
                                                                   siparisler[i].hazirlanmaSuresi,
                                                                   siparisler[i].onayRed);
            siparisVarMi = 1;
        }
    }

    printf(" -------------------------------------------------------------------------------\n");

    if (!siparisVarMi)
        printf("Hazirlanan veya reddedilen siparisiniz bulunmamaktadir.\n");
}


int siparis_id_uret(struct musSiparis *siparis_listesi) {
    int id;
    int benzer_mi;
    do {
        id = rand() % 100 + 1;
        benzer_mi = 1;
        for (int i = 0; i < yemekSayisi; i++) {
            if (siparis_listesi[i].siparisId == id) {
                benzer_mi = 0;
                break;
            }
        }
    } while (!benzer_mi);
    return id;
}

