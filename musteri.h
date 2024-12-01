#ifndef _MUSTERI_H
#define _MUSTERI_H

#define MAX_USERS 100
#define MAX_KULLANICI_UZUNLUK 50
#define MAX_SIFRE_UZUNLUK 50
#define MAX_YEMEKLER 100
#define MAX_YEMEK_ADI 50
#define MAX_YEMEK_SAYISI 50

struct kullanici {
	char kullaniciAdi[MAX_KULLANICI_UZUNLUK ];
	char sifre[MAX_SIFRE_UZUNLUK];
} ;

typedef struct kullanici kullanicilar[MAX_USERS];

typedef struct Yemek{
    int ID;
    char ad[MAX_YEMEK_ADI];
    float fiyat;
    int hazirlanmaSuresi;
    int mevcut;
} ;

typedef struct musSiparis{

    int siparisId;
    char kullaniciAdi[MAX_KULLANICI_UZUNLUK];
    char yemekAdi[MAX_YEMEK_ADI];
    float fiyat;
    int hazirlanmaSuresi;
    char onayRed[20];
};

int yemekSayisi;

int musteriMenu1();
void musteriGiris();
void kaydol(struct kullanici *kullanicilar, int *kullaniciSayisi);
struct kullanici* girisYap(struct kullanici *kullanicilar, int kullaniciSayisi);
void kullaniciListele(struct kullanici *kullanicilar, int kullaniciSayisi);
void dosyayaEkle(struct kullanici *kullanicilar, int kullaniciSayisi);

void YemekListesiOku(struct Yemek *yemekler, int *yemekSayisi);
void mevcutYemekListele(struct Yemek *yemekler, int yemekSayisi);

int siparisMenu();
void siparisVer(struct kullanici *aktifKullanici, struct Yemek *yemekler, int yemekSayisi,struct  musSiparis *siparis_listesi, int *siparis_sayisi);
void siparisDurumu(struct kullanici *aktifKullanici);
void oncekiSiparisler(struct kullanici *aktifKullanici, struct musSiparis *siparis_listesi, int siparis_sayisi);
void musSiparis_yukle(struct musSiparis *siparis_listesi, int *siparis_sayisi);
void musSiparis_kaydet(struct musSiparis *yeniSiparis);
int siparis_id_uret(struct musSiparis *siparis_listesi);



#endif // _MUSTERI_H

