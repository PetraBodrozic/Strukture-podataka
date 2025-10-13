/*1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
 zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
 studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
 prezime, apsolutni i relativni broj bodova.
 Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
 relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ime[15];
    char prezime[15];
    int apsolutniBrojBodova;
    float relativniBrojBodova;
} Student;

int prebrojiRedoveUDatoteci(char* nazivDatoteke);
Student* ucitajStudente(char* nazivDatoteke, int brojRedaka);
int ispisiStudente(Student* nizStudenata, int brojRedaka);

int main() {
    char* nazivDatoteke = "Vjezba1/studenti.txt";
    int brojRedaka = 0;
    Student* studenti = NULL;
    int status = 0;

    brojRedaka = prebrojiRedoveUDatoteci(nazivDatoteke);
    if (brojRedaka <= 0) {
        printf("Greška.\n");
        return 1;
    }
    studenti = ucitajStudente(nazivDatoteke, brojRedaka);

    status = ispisiStudente(studenti, brojRedaka);
    free(studenti);
    return status;
}
int prebrojiRedoveUDatoteci(char* nazivDatoteke) {
    FILE* fp = fopen(nazivDatoteke, "r");
    int brojac = 0;
    char string[100];

    while (fgets(string, 100, fp)) {
        brojac++;
    }
    fclose(fp);
    return brojac;
}
Student* ucitajStudente(char* nazivDatoteke, int brojRedaka) {
    FILE* fp = fopen(nazivDatoteke, "r");

    Student* studenti = (Student*)malloc(brojRedaka * sizeof(Student));
    if (!studenti) {
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < brojRedaka; i++) {
        fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].apsolutniBrojBodova);
        studenti[i].relativniBrojBodova = ((float)studenti[i].apsolutniBrojBodova / 100) * 100;
    }
    fclose(fp);
    return studenti;
}
int ispisiStudente(Student* nizStudenata, int brojRedaka) {
    printf("\nIme\t\tPrezime\t\tBodovi\tRelativno (%%)\n");
    for (int i = 0; i < brojRedaka; i++) {
        printf("%s\t\t%s\t\t%d\t%.2f%%\n", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].apsolutniBrojBodova, nizStudenata[i].relativniBrojBodova);
    }
    return 0;
}