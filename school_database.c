#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



struct Ders{
	int DersKodu;
	char DersAdi[30];
	int Kredi;
	int Kontenjan;
	int KayitliSayisi;
	int OgretimID;
};


struct OgretimUyesi{
	int ID;
	char AD[20];
	char SOYAD[20];
	char UNVAN[20];
};


struct Ogrenci{
	int OgrNum;
	char AD[20];
	char SOYAD[20];
	int DersSayisi;
	int Kredi;
};

struct OgrenciDers{
	int ID;
	int OgrNo;
	int DersKodu;
	char tarih[25];
	int KayitDurumu;
};

void ogrenci2txt(struct Ogrenci* liste);
void ogrenciEkle(struct Ogrenci* array, struct Ogrenci ogr);
void OgrenciSil(struct Ogrenci *liste, char *dosya, int OgrNumber, struct Ders *dersListe, struct OgrenciDers *kayitListe);
void OgrenciGuncelle(struct Ogrenci *liste, char *dosya, int OgrNumber);
void loadOgrenciler(struct Ogrenci *liste, char* dosya);

void ogretim2txt(struct OgretimUyesi* liste);
void ogretimEkle(struct OgretimUyesi* liste, struct OgretimUyesi ogr);
void OgretimSil(struct OgretimUyesi *liste, char *dosya, int OgrID,struct OgrenciDers *kayitListe, struct Ogrenci* ogrListe, struct Ders *dersListe);
void OgretimGuncelle(struct OgretimUyesi *liste, char *dosya, int OgrID);
void loadOgretimUyesi(struct OgretimUyesi *liste, char* dosya);

void ders2txt(struct Ders* liste);
void dersEkle(struct Ders* liste, struct Ders drs, struct OgretimUyesi* hocaliste);
void dersSil(struct Ders *liste, char *dosya, int kod, struct OgrenciDers *kayitliste, struct Ogrenci *ogrliste);
void dersGuncelle(struct Ders *liste, char *dosya, int kod, struct Ogrenci *ogrListe, struct OgrenciDers *kayitListe);
void loadDers(struct Ders *liste, char* dosya);

void loadKayitlar(struct OgrenciDers *liste, char* dosya);
int kayitEkle(struct Ogrenci *ogrListe, struct Ders *dersListe, struct OgrenciDers *kayitListe, int krediSiniri, int maxDers, int OgrNum, int DersKod, char *tarih);
int kayitSil(struct Ogrenci *ogrListe, struct Ders *dersListe, struct OgrenciDers *kayitListe, int OgrNum, int DersKod);

void hoca2ders(struct Ders *dersListe, int hocaID);
void ders2ogrenci(struct OgrenciDers *kayitListe, struct Ogrenci *ogrenciListe, int dersKodu);
void ogrenci2ders(struct OgrenciDers *kayitListe, struct Ders *dersListe, int ogrenciNo);
int hocaders2file(int hocaID, int dersKodu, struct Ders *dersListe, struct Ogrenci *ogrenciListe, struct OgretimUyesi *hocaListe, struct OgrenciDers *kayitListe);



int main(){
	
	struct Ders *Dersler = (struct Ders*)calloc(sizeof(struct Ders),250);
	struct OgretimUyesi *OgretimUyeleri = (struct OgretimUyesi*)calloc(sizeof(struct OgretimUyesi),250);
	struct Ogrenci *Ogrenciler = (struct Ogrenci*)calloc(sizeof(struct Ogrenci),250);
	struct OgrenciDers *Kayitlar = (struct OgrenciDers*)calloc(sizeof(struct OgrenciDers), 1000);
	
	loadOgrenciler(Ogrenciler, "ogrenciler.txt");
	loadOgretimUyesi(OgretimUyeleri, "ogretimuyeleri.txt");
	loadDers(Dersler, "dersler.txt");
	loadKayitlar(Kayitlar, "derskayit.txt");
	
	
	while (1){
		printf("\n\n");
		printf("1. Ogrenci Ekle\n");
		printf("2. Ogrenci Sil\n");
		printf("3. Ogrenci Guncelle\n");
		printf("4. Ogretim Uyesi Ekle\n");
		printf("5. Ogretim Uyesi Sil\n");
		printf("6. Ogretim Uyesi Guncelle\n");
		printf("7. Ders Ekle\n");
		printf("8. Ders Sil\n");
		printf("9. Ders Guncelle\n");
		printf("10. Ogrenci Ders Kayit Ekle\n");
		printf("11. Ogrenci Ders Kayit Sil\n");
		printf("12. Ogretim Uyesinin Verdigi Dersleri Goruntule\n");
		printf("13. Ders Koduna Gore Kayitli Ogrencileri Goruntule\n");
		printf("14. Ogrenci Numarasina Gore Alinan Dersleri Goruntule\n");
		printf("15. Hocanin Dersini Alanlari Dosyaya Yazdir\n");
		printf("99. Exit");
		
		
		int number;
		printf("\nIslemi Seciniz: ");
		scanf("%d", &number);
		getchar();
		printf("\n");
		if (number == 1){
			struct Ogrenci ogr;
			printf("\tOgrenci Numarasi:");
			scanf("%d", &ogr.OgrNum);
			getchar();
			printf("\n\tOgrenci Adi: ");
			scanf("%[^\n]s", ogr.AD);
			getchar();
			printf("\n\tOgrenci Soyadi: ");
			scanf("%s", ogr.SOYAD);
			getchar();
			
			ogr.DersSayisi = 0;
			ogr.Kredi = 0;
	
			ogrenciEkle(Ogrenciler, ogr);
		}
		else if (number == 2){
			int num;
			printf("\t Silinecek Ogrenci Numarasi:");
			scanf("%d", &num);
			getchar();
			
			OgrenciSil(Ogrenciler, "ogrenciler.txt", num, Dersler, Kayitlar);
		}
		else if (number == 3){
			int num;
			printf("\t Guncellenecek Ogrenci Numarasi:");
			scanf("%d", &num);
			getchar();
			OgrenciGuncelle(Ogrenciler, "ogrenciler.txt", num);
		}
		else if (number == 4){
			struct OgretimUyesi ogr;
			printf("\tOgretim Uyesi ID:");
			scanf("%d", &ogr.ID);
			getchar();
			printf("\n\tOgretim Uyesi Adi: ");
			scanf("%[^\n]s", ogr.AD);
			getchar();
			printf("\n\tOgretim Uyesi Soyadi: ");
			scanf("%s", ogr.SOYAD);
			getchar();
			printf("\n\tOgretim Uyesi Unvani: ");
			scanf("%s", ogr.UNVAN);
			getchar();

			ogretimEkle(OgretimUyeleri, ogr);
		}
		else if (number == 5){
			int num;
			printf("\t Silinecek Ogretim Uyesi ID:");
			scanf("%d", &num);
			getchar();
			OgretimSil(OgretimUyeleri, "ogretimuyeleri.txt", num, Kayitlar, Ogrenciler, Dersler);
		}
		else if (number == 6){
			int num;
			printf("\t Guncellenecek Ogretim Uyesi ID:");
			scanf("%d", &num);
			getchar();
			OgretimGuncelle(OgretimUyeleri, "ogretimuyeleri.txt", num);	
		}
		else if (number == 7){
			struct Ders drs;
			printf("\tDers Kodu:");
			scanf("%d", &drs.DersKodu);
			getchar();
			printf("\n\tDers Adi: ");
			scanf("%[^\n]s", drs.DersAdi);
			getchar();
			printf("\tDers Kredisi:");
			scanf("%d", &drs.Kredi);
			getchar();
			printf("\tDers Kontenjani:");
			scanf("%d", &drs.Kontenjan);
			getchar();
			printf("\tDersi Veren Ogretim Uyesinin ID Numarasi:");
			scanf("%d", &drs.OgretimID);
			getchar();
			
			drs.KayitliSayisi = 0;
			
			dersEkle(Dersler, drs, OgretimUyeleri);
		}
		else if (number == 8){
			int num;
			printf("\t Silinecek Ders Kodu:");
			scanf("%d", &num);
			getchar();
			
			dersSil(Dersler, "dersler.txt", num, Kayitlar, Ogrenciler);
		}
		else if (number == 9){
			int num;
			printf("\t Guncellenecek Ders Kodu:");
			scanf("%d", &num);
			getchar();
			dersGuncelle(Dersler, "dersler.txt", num, Ogrenciler, Kayitlar);	
		}
		else if (number == 10){
			int krediSiniri;
			int maxDers;
			char tarih[20];
			
			printf("\t Ogrenci Kredi Siniri:");
			scanf("%d", &krediSiniri);
			getchar();
			printf("\t Ogrenci Alabilecegi Ders Siniri:");
			scanf("%d", &maxDers);
			getchar();
			printf("\t Tarih (Ornek 11.11.2020):");
			scanf("%s", tarih);
			getchar();
			
			int OgrNum;
			int DersKod;
			printf("\n\t Ogrenci Numarasi:");
			scanf("%d", &OgrNum);
			getchar();
			printf("\n\t Ders Kodu:");
			scanf("%d", &DersKod);
			getchar();
			
			if (kayitEkle(Ogrenciler, Dersler, Kayitlar, krediSiniri, maxDers, OgrNum, DersKod, tarih)){
				printf("\n\tDers Basariyla Alindi");
			}
		}
		else if (number == 11){
			int OgrNum;
			int DersKod;
			printf("\n\t Ogrenci Numarasi:");
			scanf("%d", &OgrNum);
			getchar();
			printf("\n\t Ders Kodu:");
			scanf("%d", &DersKod);
			getchar();
			
			kayitSil(Ogrenciler, Dersler, Kayitlar, OgrNum, DersKod);
		}
		else if (number == 12){
			int hocaID;
			printf("\n\t Ogretim Uyesi ID:");
			scanf("%d", &hocaID);
			getchar();
			
			hoca2ders(Dersler, hocaID);
						
		}
		else if (number == 13){
			int dersKodu;
			printf("\n\t Ders Kodu:");
			scanf("%d", &dersKodu);
			getchar();
			
			ders2ogrenci(Kayitlar, Ogrenciler, dersKodu);			
		}
		else if (number == 14){
			int ogrenciNum;
			printf("\n\t Ogrenci Numarasi:");
			scanf("%d", &ogrenciNum);
			getchar();
			
			ogrenci2ders(Kayitlar, Dersler, ogrenciNum);	
		}
		else if (number == 15){
			int hocaID;
			int dersKodu;
			
			printf("\n\t Ogretim Uyesi ID:");
			scanf("%d", &hocaID);
			getchar();
			printf("\n\t Ders Kodu:");
			scanf("%d", &dersKodu);
			getchar();
			
			hocaders2file(hocaID, dersKodu, Dersler, Ogrenciler, OgretimUyeleri, Kayitlar);
		}
		else if (number == 99){
			break;
		}
	}
	
	free(Dersler);
	free(Ogrenciler);
	free(Kayitlar);
	free(OgretimUyeleri);
	
	return 0;
}

	

void ogrenci2txt(struct Ogrenci* liste){
	FILE *fp = fopen("ogrenciler.txt", "w");
	int i = 0;
	while (liste[i].OgrNum != 0){
		fprintf(fp, "%d-%s-%s-%d-%d\n", liste[i].OgrNum, liste[i].AD, liste[i].SOYAD, liste[i].DersSayisi, liste[i].Kredi);
		i++;
	}
	fclose(fp);
}

void ogretim2txt(struct OgretimUyesi* liste){
	FILE *fp = fopen("ogretimuyeleri.txt", "w");
	int i = 0;
	while (liste[i].ID != 0){
		fprintf(fp, "%d-%s-%s-%s\n", liste[i].ID, liste[i].AD, liste[i].SOYAD, liste[i].UNVAN);
		i++;
	}
	fclose(fp);
}

void ders2txt(struct Ders* liste){
	FILE *fp = fopen("dersler.txt", "w");
	int i = 0;
	while (liste[i].DersKodu != 0){
		fprintf(fp, "%d-%s-%d-%d-%d-%d\n", liste[i].DersKodu, liste[i].DersAdi, liste[i].Kredi, liste[i].Kontenjan, liste[i].KayitliSayisi, liste[i].OgretimID);
		i++;
	}
	fclose(fp);
}

void kayit2txt(struct OgrenciDers* liste){
	FILE *fp = fopen("derskayit.txt", "w");
	int i = 0;
	while (liste[i].DersKodu != 0){
		fprintf(fp, "%d-%d-%d-%s-%d\n", liste[i].ID, liste[i].OgrNo, liste[i].DersKodu, liste[i].tarih, liste[i].KayitDurumu);
		i++;
	}
	fclose(fp);
}

	
	
void ogrenciEkle(struct Ogrenci* array, struct Ogrenci ogr){
	int i = 0;
	
	while (array[i].OgrNum != 0 && array[i].OgrNum != ogr.OgrNum){
		i++;
	}
	if (array[i].OgrNum == 0){
		array[i] = ogr;
		FILE *fp = fopen("ogrenciler.txt", "a");
		fprintf(fp, "%d-%s-%s-%d-%d\n", ogr.OgrNum, ogr.AD, ogr.SOYAD, ogr.DersSayisi, ogr.Kredi);
		fclose(fp);
	}
	else{
		printf("\n\tOgrenci Zaten Listede!!");
	}
}


void ogretimEkle(struct OgretimUyesi* liste, struct OgretimUyesi ogr){
	int i = 0;
	
	while (liste[i].ID != 0 && liste[i].ID != ogr.ID){
		i++;
	}
	if (liste[i].ID == 0){
		liste[i] = ogr;
		FILE *fp = fopen("ogretimuyeleri.txt", "a");
		fprintf(fp, "%d-%s-%s-%s\n", liste[i].ID, liste[i].AD, liste[i].SOYAD, liste[i].UNVAN);
		fclose(fp);
	}
	else{
		printf("\n\tOgretim Uyesi Zaten Listede!!");
	}	
}


void dersEkle(struct Ders* liste, struct Ders drs, struct OgretimUyesi* hocaliste){
	int i = 0;
	int j = 0;
	while (liste[i].DersKodu != 0 && liste[i].DersKodu != drs.DersKodu){
		i++;
	}
	if (liste[i].DersKodu == 0){
		while (hocaliste[j].ID != drs.OgretimID && hocaliste[j].ID != 0){
			j++;
		}
		if (hocaliste[j].ID == 0){
			printf("\n\tVerilen ID Numarasi ile Kayitli Hic Bir Ogretim Uyesi Bulunamadigindan Ders Eklenemedi!!!");
		}
		else{
			liste[i] = drs;
			FILE *fp = fopen("dersler.txt", "a");
			fprintf(fp, "%d-%s-%d-%d-%d-%d\n", liste[i].DersKodu, liste[i].DersAdi, liste[i].Kredi, liste[i].Kontenjan, liste[i].KayitliSayisi, liste[i].OgretimID);
			fclose(fp);
		}
	}
	
	else{
		printf("\n\tDers Zaten Listede!!");
	}	
}



void OgrenciSil(struct Ogrenci *liste, char *dosya, int OgrNumber, struct Ders *dersListe, struct OgrenciDers *kayitListe){
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (liste[i].OgrNum != 0 && liste[i].OgrNum != OgrNumber){
		i++;
	}
	if (liste[i].OgrNum == OgrNumber){
		while (liste[i].OgrNum != 0){
			liste[i].OgrNum = liste[i+1].OgrNum;
			strcpy(liste[i].AD, liste[i+1].AD);
			strcpy(liste[i].SOYAD, liste[i+1].SOYAD);
			liste[i].DersSayisi = liste[i+1].DersSayisi;
			liste[i].Kredi = liste[i+1].Kredi;
			i++;
		}
		ogrenci2txt(liste);
		
		while (kayitListe[j].ID != 0){
			if (kayitListe[j].OgrNo == OgrNumber && kayitListe[j].KayitDurumu == 1){
				kayitListe[j].KayitDurumu = 0;
				while (dersListe[k].DersKodu != 0){
					if (dersListe[k].DersKodu == kayitListe[j].DersKodu){
						dersListe[k].KayitliSayisi -= 1;
						break;
					}
					k++;
				}
				k = 0;
			}
			j++;
		}
    kayit2txt(kayitListe);
    ders2txt(dersListe);
		
	}
	else{
		printf("\tSilinecek Ogrenci Bulunamadi!!");
	}
}


void OgretimSil(struct OgretimUyesi *liste, char *dosya, int OgrID,struct OgrenciDers *kayitListe, struct Ogrenci* ogrListe, struct Ders *dersListe){
	int i = 0;
	int j = 0;
	while (liste[i].ID != 0 && liste[i].ID != OgrID){
		i++;
	}
	if (liste[i].ID == OgrID){
    int hocaid = liste[i].ID;
		while (liste[i].ID != 0){
			liste[i].ID = liste[i+1].ID;
			strcpy(liste[i].AD, liste[i+1].AD);
			strcpy(liste[i].SOYAD, liste[i+1].SOYAD);
			strcpy(liste[i].UNVAN, liste[i+1].UNVAN);
			i++;
		}
		ogretim2txt(liste);
		
		while (dersListe[j].DersKodu != 0){
			if (dersListe[j].OgretimID == hocaid){
				dersSil(dersListe, "dersler.txt", dersListe[j].DersKodu, kayitListe, ogrListe);
			}
	        else{
	        	j++;
	        }
		}
	}
	else{
		printf("\tSilinecek Ogretim Uyesi Bulunamadi!!");
	}
}

void dersSil(struct Ders *liste, char *dosya, int kod, struct OgrenciDers *kayitliste, struct Ogrenci *ogrliste){
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (liste[i].DersKodu != 0 && liste[i].DersKodu != kod){
		i++;
	}
	if (liste[i].DersKodu == kod){
		int kredi = liste[i].Kredi;
		
		while (liste[i].DersKodu != 0){
			liste[i].DersKodu = liste[i+1].DersKodu;
			strcpy(liste[i].DersAdi, liste[i+1].DersAdi);
			liste[i].Kredi = liste[i+1].Kredi;
			liste[i].Kontenjan = liste[i+1].Kontenjan;
			liste[i].KayitliSayisi = liste[i+1].KayitliSayisi;
			liste[i].OgretimID = liste[i+1].OgretimID;
			i++;
		}
		ders2txt(liste);
		
		while (kayitliste[j].ID != 0){
			if (kayitliste[j].DersKodu == kod && kayitliste[j].KayitDurumu == 1){
				kayitliste[j].KayitDurumu = 0;
				
				while (ogrliste[k].OgrNum != kayitliste[j].OgrNo){
					k++;
				}
				ogrliste[k].Kredi -= kredi;
				ogrliste[k].DersSayisi -= 1;
				k = 0;
			}
			j++;
		}
		ogrenci2txt(ogrliste);
		kayit2txt(kayitliste);
	}
	else{
		printf("\tSilinecek Ders Bulunamadi!!");
	}
}

void OgrenciGuncelle(struct Ogrenci *liste, char *dosya, int OgrNumber){
	
	int i = 0;
	while (liste[i].OgrNum != 0 && liste[i].OgrNum != OgrNumber){
		i++;
	}
	if (liste[i].OgrNum == OgrNumber){
		printf("\tYeni Ad: ");
		scanf("%[^\n]s", liste[i].AD); 
		getchar();
		printf("\tYeni Soyad: ");
		scanf("%s", liste[i].SOYAD);
		getchar();
		
		ogrenci2txt(liste);
	}
	else{
		printf("\tOgrenci Bulunamadi!");
	}
}


void dersGuncelle(struct Ders *liste, char *dosya, int kod, struct Ogrenci *ogrListe, struct OgrenciDers *kayitListe){
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (liste[i].DersKodu != 0 && liste[i].DersKodu != kod){
		i++;
	}
	if (liste[i].DersKodu == kod){
		printf("\n\tYeni Ders Adi ");
		scanf("%[^\n]s", liste[i].DersAdi);
		getchar();
		
		int eskiKredi = liste[i].Kredi;
		printf("\n\tYeni Kredi: ");
		scanf("%d", &liste[i].Kredi);
		getchar();
		if (eskiKredi != liste[i].Kredi){
			int fark = liste[i].Kredi - eskiKredi;
			while (kayitListe[j].ID != 0){
				if (kayitListe[j].DersKodu == kod){
					while (ogrListe[k].OgrNum != 0){
						if (ogrListe[k].OgrNum == kayitListe[j].OgrNo){
							ogrListe[k].Kredi += fark;
						}
						k++;
					}
					k = 0;
				}
				j++;
			}
			ogrenci2txt(ogrListe);
		}
		
		
		printf("\n\tYeni Kontenjan: ");
		scanf("%d", &liste[i].Kontenjan);
		getchar();
		
		ders2txt(liste);
	}
	else{
		printf("\tDers Bulunamadi!");
	}
}


void OgretimGuncelle(struct OgretimUyesi *liste, char *dosya, int OgrID){
	
	int i = 0;
	while (liste[i].ID != 0 && liste[i].ID != OgrID){
		i++;
	}
	if (liste[i].ID == OgrID){
		printf("\n\tYeni Ad: ");
		scanf("%[^\n]s", liste[i].AD);
		getchar();
		printf("\n\tYeni Soyad: ");
		scanf("%s", liste[i].SOYAD);
		getchar();
		printf("\n\tYeni Unvan: ");
		scanf("%[^\n]s", liste[i].UNVAN);
		getchar();
		
		ogretim2txt(liste);
	}
	else{
		printf("\tOgretim Uyesi Bulunamadi!");
	}
}


void loadOgrenciler(struct Ogrenci *liste, char* dosya){
	FILE *fp = fopen(dosya, "r+");
	int i = 0;
	
	char *buffer = (char *)malloc(sizeof(char)*250);
	const char del[2] = "-";
	char *part;

	while (fgets(buffer, 250, fp)){
		
		part = strtok(buffer, del);
		liste[i].OgrNum = atoi(part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].AD, part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].SOYAD, part);
		
		part = strtok(NULL, del);
		liste[i].DersSayisi = atoi(part);
		
		part = strtok(NULL, del);
		liste[i].Kredi = atoi(part);
		
		i++;
	}
	free(buffer);
	fclose(fp);
}

	
void loadOgretimUyesi(struct OgretimUyesi *liste, char* dosya){
	FILE *fp = fopen(dosya, "r+");
	int i = 0;
	
	char *buffer = (char *)malloc(sizeof(char)*250);
	const char del[2] = "-";
	char *part;

	while (fgets(buffer, 250, fp)){
		
		part = strtok(buffer, del);
		liste[i].ID = atoi(part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].AD, part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].SOYAD, part);

		part = strtok(NULL, del);
		part[strlen(part)-1] = '\0';
		strcpy(liste[i].UNVAN, part);
		
		i++;
	}
	free(buffer);
	fclose(fp);
}


void loadDers(struct Ders *liste, char* dosya){
	FILE *fp = fopen(dosya, "r+");
	int i = 0;
	
	char *buffer = (char *)malloc(sizeof(char)*250);
	const char del[2] = "-";
	char *part;

	while (fgets(buffer, 250, fp)){
		
		part = strtok(buffer, del);
		liste[i].DersKodu = atoi(part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].DersAdi, part);
		
		part = strtok(NULL, del);
		liste[i].Kredi = atoi(part);
		
		part = strtok(NULL, del);
		liste[i].Kontenjan = atoi(part);
		
		part = strtok(NULL, del);
		liste[i].KayitliSayisi = atoi(part);
		
		part = strtok(NULL, del);
		liste[i].OgretimID = atoi(part);

		i++;
	}
	
	free(buffer);
	fclose(fp);
}

void loadKayitlar(struct OgrenciDers *liste, char* dosya){
	FILE *fp = fopen(dosya, "r+");
	int i = 0;
	
	char *buffer = (char *)malloc(sizeof(char)*250);
	const char del[2] = "-";
	char *part;

	while (fgets(buffer, 250, fp)){
		
		part = strtok(buffer, del);
		liste[i].ID = atoi(part);

		part = strtok(NULL, del);
		liste[i].OgrNo = atoi(part);
		
		part = strtok(NULL, del);
		liste[i].DersKodu = atoi(part);
		
		part = strtok(NULL, del);
		strcpy(liste[i].tarih, part);
		
		part = strtok(NULL, del);
		liste[i].KayitDurumu = atoi(part);

		i++;
	}
	
	free(buffer);
	fclose(fp);
}

int kayitEkle(struct Ogrenci *ogrListe, struct Ders *dersListe, struct OgrenciDers *kayitListe, int krediSiniri, int maxDers, int OgrNum, int DersKod, char *tarih){
	
	int k = 0;
	struct OgrenciDers yeniKayit;
	int sadeceGuncelle = 0;
	
	while (kayitListe[k].ID != 0){
		if (kayitListe[k].OgrNo == OgrNum && kayitListe[k].DersKodu == DersKod && kayitListe[k].KayitDurumu == 1){
			printf("Ogrenci bu dersi zaten aliyor!!");
			return 0;
		}
		else if (kayitListe[k].OgrNo == OgrNum && kayitListe[k].DersKodu == DersKod && kayitListe[k].KayitDurumu == 0){
			sadeceGuncelle = 1;
			break;
		}
		k++;
	}
	if (k == 0){
		yeniKayit.ID = 1;
	}
	else{
		yeniKayit.ID = kayitListe[k-1].ID +1;
	}
	
	
	
	int i = 0;
	int j = 0;
	
	while (dersListe[i].DersKodu != 0 && dersListe[i].DersKodu != DersKod){
		i++;
	}
	if (dersListe[i].DersKodu == 0){
		printf("\tKodu verilen ders bulunamadigindan islem iptal edildi!!");
		return 0;
	}
	else{
		if (dersListe[i].Kontenjan <= dersListe[i].KayitliSayisi){
			printf("\tDersin kontenjani dolu oldugundan ders alinamadi!!!");
			return 0;
		}
	}
	
	while (ogrListe[j].OgrNum != 0 && ogrListe[j].OgrNum != OgrNum){
		j++;
	}
	if (ogrListe[j].OgrNum == 0){
		printf("\tNumarasi verilen ogrenci bulunamadigindan islem iptal edildi!!");
		return 0;
	}
	else{
		if (ogrListe[j].Kredi + dersListe[i].Kredi > krediSiniri){
			printf("\tOgrencinin bu dersi alabilmek icin yeterli kredi hakki bulunmamaktadir!!!");
			return 0;	
		}
		if (ogrListe[j].DersSayisi + 1 > maxDers){
			printf("\tOgrencinin bu dersi alabilmek icin yeterli ders alma hakki bulunmamaktadir!!!");
			return 0;	
		}
	}
	
	dersListe[i].KayitliSayisi++;
	ogrListe[j].Kredi += dersListe[i].Kredi;
	ogrListe[j].DersSayisi++;
	

	if (sadeceGuncelle == 0){
		yeniKayit.DersKodu = dersListe[i].DersKodu;
		yeniKayit.OgrNo = ogrListe[j].OgrNum;
		strcpy(yeniKayit.tarih, tarih);
		yeniKayit.KayitDurumu = 1;
		
		kayitListe[k] = yeniKayit;
	}
	else{
		kayitListe[k].KayitDurumu = 1;
		strcpy(kayitListe[k].tarih, tarih);
	}
	
	kayit2txt(kayitListe);
	ogrenci2txt(ogrListe);
	ders2txt(dersListe);
	return 1;
}

int kayitSil(struct Ogrenci *ogrListe, struct Ders *dersListe, struct OgrenciDers *kayitListe, int OgrNum, int DersKod){
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (kayitListe[i].ID != 0){
		if (kayitListe[i].OgrNo == OgrNum && kayitListe[i].DersKodu == DersKod){
			break;
		}
		i++;
	}
	if (kayitListe[i].ID != 0){
		if (kayitListe[i].KayitDurumu == 0){
			printf("\n\tOgrenci Bu Dersi Almamaktadir!!");
			return 0;
		}
		else{
			kayitListe[i].KayitDurumu = 0;
			while (dersListe[k].DersKodu != DersKod){
				k++;
			}
			while (ogrListe[j].OgrNum != OgrNum){
				j++;
			}
			dersListe[k].KayitliSayisi -= 1;
			ogrListe[j].DersSayisi -= 1;
			ogrListe[j].Kredi -= dersListe[k].Kredi;
			
			ogrenci2txt(ogrListe);
			ders2txt(dersListe);
			kayit2txt(kayitListe);
			
			return 1;
		}
	}
	else{
		printf("\n\tOgrenci Bu Dersi Almamaktadir!!");
		return 0;
	}
}


void hoca2ders(struct Ders *dersListe, int hocaID){
	int i = 0;
	
	printf("\n\tOgretim Uyesinin verdigi dersler: ");
	while (dersListe[i].DersKodu != 0){
		if (dersListe[i].OgretimID == hocaID){
			printf("\n\tDers Adi: %s	Ders Kodu: %d", dersListe[i].DersAdi, dersListe[i].DersKodu);
		}
		i++;
	}
}

void ders2ogrenci(struct OgrenciDers *kayitListe, struct Ogrenci *ogrenciListe, int dersKodu){
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	
	int *ogrenciListesi = (int *) malloc(sizeof(int) * 250);
	
	while (kayitListe[i].ID != 0){
		if (kayitListe[i].DersKodu == dersKodu && kayitListe[i].KayitDurumu == 1){
			ogrenciListesi[j] = kayitListe[i].OgrNo;
			j++;
		}
		i++;
	}
	
	for (k = 0; k < j; k++){
		while (ogrenciListe[t].OgrNum != ogrenciListesi[k]){
			t++;
		}
		printf("\t\t\nOgrenci Adi: %s 	Ogrenci Soyadi: %s 		Ogrenci Numarasi: %d", ogrenciListe[t].AD, ogrenciListe[t].SOYAD, ogrenciListe[t].OgrNum);
		t = 0;
	}
	free(ogrenciListesi);
}


void ogrenci2ders(struct OgrenciDers *kayitListe, struct Ders *dersListe, int ogrenciNo){
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	
	int *dersListesi = (int *) malloc(sizeof(int) * 250);
	
	while (kayitListe[i].ID != 0){
		if (kayitListe[i].OgrNo == ogrenciNo && kayitListe[i].KayitDurumu == 1){
			dersListesi[j] = kayitListe[i].DersKodu;
			j++;
		}
		i++;
	}
	
	for (k = 0; k < j; k++){
		while (dersListe[t].DersKodu != dersListesi[k]){
			t++;
		}
		printf("\t\t\nDers Adi: %s 	Ders Kodu: %d", dersListe[t].DersAdi, dersListe[t].DersKodu);
		t = 0;
	}
	free(dersListesi);	
}


int hocaders2file(int hocaID, int dersKodu, struct Ders *dersListe, struct Ogrenci *ogrenciListe, struct OgretimUyesi *hocaListe, struct OgrenciDers *kayitListe){
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	
	while (hocaListe[i].ID != 0){
		if (hocaListe[i].ID == hocaID){
			break;
		}
		i++;
	}
	if (hocaListe[i].ID == 0){
		printf("\n\tIDsi verilen ogretim uyesi bulunamadi!!");
		return 0;
	}
	
	while (dersListe[j].DersKodu != 0){
		if (dersListe[j].DersKodu == dersKodu && dersListe[j].OgretimID == hocaID){
			break;
		}
		j++;
	}
	if (dersListe[j].DersKodu == 0){
		printf("\n\tIDsi verilen ogretim uyesi bu koda sahip bir ders vermemektedir!!");
		return 0;
	}
	
	int *derstekiogrenciler = (int *)malloc(sizeof(int)*250);
	
	while (kayitListe[k].ID != 0){
		if (kayitListe[k].DersKodu == dersKodu && kayitListe[k].KayitDurumu == 1){
			derstekiogrenciler[t] = kayitListe[k].OgrNo;
			t++;
		}
		k++;
	}
	
	char *filename = (char *)malloc(sizeof(char)*50);
	
	sprintf(filename, "%d_SINIFLISTESI.txt", dersKodu);
	
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == NULL){
		printf("Dosya Acilamadi!!");
		exit(1);
	}
	
	int it;
	int m = 0;
	for (it = 0; it < t; it++){
		while (ogrenciListe[m].OgrNum != derstekiogrenciler[it]){
			m++;
		}
		fprintf(fp, "Ogrenci Adi: %s	Ogrenci Soyadi: %s	Ogrenci Numarasi: %d\n", ogrenciListe[m].AD, ogrenciListe[m].SOYAD, ogrenciListe[m].OgrNum);
		m = 0;
	}
	
	fclose(fp);
	
	free(derstekiogrenciler);
	free(filename);
	return 1;
}






















