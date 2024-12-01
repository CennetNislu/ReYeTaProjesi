#ifndef RESTORAN_H
#define RESTORAN_H
#define MAX_YEMEK_ADI 50
#define MAX_KULLANICI_UZUNLUK 50
#define MAX_YEMEK_SAYISI 50
#define MAX_SIPARIS_SAYISI 50



typedef struct yemek {
    int ID;
    char ad[MAX_YEMEK_ADI];
    float fiyat;
    int hazirlanma_suresi;
    int mevcut;
} ;

typedef struct Siparis{
    int siparisID;
    float fiyat;
    char kullanici_adi[MAX_KULLANICI_UZUNLUK];
    char yemek_adi[MAX_YEMEK_ADI];
    char durum[20]; // Onaylandý, Reddedildi
    int hazirlanma_suresi;
} ;

struct Siparis siparis_listesi[MAX_SIPARIS_SAYISI];
struct yemek yemek_listesi[MAX_YEMEK_SAYISI];

// Fonksiyon prototipleri
void restoranGiris();
int restoranMenu();
void yemek_listesini_yukle();
void yemek_listesini_kaydet();
void yemek_listesi_goruntule();
void yemek_ekle();
void yemek_guncelle();
void yemek_sil();
int yemek_id_uret();

void siparisleri_yukle();
void siparisleri_kaydet();
void siparisleri_goruntule();
void yeni_siparis_onay_red();
void siparisleri_mutfaga_gonder();


#endif

