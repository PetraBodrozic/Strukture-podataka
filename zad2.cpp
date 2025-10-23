#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicija strukture osobe
// Svaka osoba ima ime, prezime i datum roðenja (dan, mjesec, godina)
// te pokazivaè na sljedeæu osobu u listi
typedef struct Person {
    char name[20];
    char surname[20];
    int day, month, year;
    struct Person* next;
} Person;

// Deklaracije funkcija koje se koriste u programu
Person* add_in_front(Person*);               // dodaje novi element na poèetak liste
Person* delete_from_list(Person*, char*);    // briše element po prezimenu
Person* add_to_end(Person*);                 // dodaje novi element na kraj liste
Person* create();                            // kreira novi èvor (osobu)
int find_in_list(Person*, char*);            // pronalazi osobu po prezimenu
int print_list(Person*);                     // ispisuje cijelu listu

int main() {
    int choice;
    int status = 0;
    char sur[20];
    Person* head = NULL;  // pokazivaè na prvi element liste (inicijalno prazan)

    do {
        // Izbornik
        printf("Izaberite funkciju (6 za izlaz):\n");
        printf("1 - Dodaj na pocetak\n");
        printf("2 - Dodaj na kraj\n");
        printf("3 - Izbrisi iz liste\n");
        printf("4 - Pronadi\n");
        printf("5 - Ispisi listu\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Dodavanje novog elementa na poèetak
            head = add_in_front(head);
            break;

        case 2:
            // Dodavanje novog elementa na kraj
            head = add_to_end(head);
            break;

        case 3:
            // Brisanje osobe prema prezimenu
            printf("Unesite prezime za izbrisati: ");
            scanf("%19s", sur);
            head = delete_from_list(head, sur);
            break;

        case 4:
            // Pretraga osobe prema prezimenu
            printf("Unesite prezime za pronaci: ");
            scanf("%19s", sur);
            if (find_in_list(head, sur) == 1) {
                printf("Greska! Nema takve osobe!\n");
            }
            break;

        case 5:
            // Ispis liste
            status = print_list(head);
            break;

        case 6:
            // Izlaz iz programa
            break;

        default:
            printf("Niste unijeli pravilan broj!\n");
            break;
        }
    } while (choice != 6);

    // Oslobaðanje zauzete memorije
    Person* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

// Funkcija za unos nove osobe
Person* create() {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        printf("Greska u alociranju memorije!\n");
        return NULL;
    }

    printf("Unesite ime: ");
    scanf("%19s", new_person->name);
    printf("Unesite prezime: ");
    scanf("%19s", new_person->surname);
    printf("Unesite datum rodenja (dd mm yyyy): ");
    scanf("%d %d %d", &new_person->day, &new_person->month, &new_person->year);

    new_person->next = NULL; // novi èvor još nije povezan u listu
    return new_person;
}

// Dodavanje osobe na poèetak liste
Person* add_in_front(Person* head) {
    Person* person_to_add = create();
    if (person_to_add == NULL) {
        printf("Greska u stvaranju osobe!\n");
        return head;
    }

    person_to_add->next = head;  // novi èvor pokazuje na stari prvi
    return person_to_add;        // vraæa se novi pokazivaè na poèetak
}

// Dodavanje osobe na kraj liste
Person* add_to_end(Person* head) {
    Person* person_to_add = create();
    if (person_to_add == NULL) {
        printf("Greska u stvaranju osobe!\n");
        return head;
    }

    // Ako je lista prazna
    if (head == NULL) {
        return person_to_add;
    }

    // Inaèe idemo do kraja liste
    Person* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = person_to_add;  // dodaj novi èvor na kraj
    return head;
}

// Ispis cijele liste
int print_list(Person* head) {
    if (head == NULL) {
        printf("Greska! Nema ljudi za ispisati!\n");
        return 1;
    }

    Person* temp = head;
    printf("%-20s %-20s %-20s\n", "IME", "PREZIME", "DATUM RODENJA");
    printf("-----------------------------------------------------------------------\n");

    // Ispis svakog elementa dok ne doðemo do kraja
    while (temp != NULL) {
        printf("%-20s %-20s %02d.%02d.%04d\n",
            temp->name, temp->surname, temp->day, temp->month, temp->year);
        temp = temp->next;
    }

    return 0;
}

// Brisanje osobe prema prezimenu
Person* delete_from_list(Person* head, char* surname) {
    Person* temp = head;
    Person* previous = NULL;

    // Tražimo osobu s danim prezimenom
    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        previous = temp;
        temp = temp->next;
    }

    // Ako osoba nije pronaðena
    if (temp == NULL) {
        printf("Greska! Ne postoji osoba s tim prezimenom!\n");
        return head;
    }

    // Ako se briše prvi element
    if (previous == NULL) {
        head = temp->next;
    }
    else {
        previous->next = temp->next;
    }

    free(temp);  // oslobaða memoriju obrisanog èvora
    return head;
}

// Pretraga osobe po prezimenu
int find_in_list(Person* head, char* surname) {
    if (head == NULL) {
        return 1; // lista prazna
    }

    Person* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) {
            printf("Pronadena osoba: %s %s, rodena %02d.%02d.%04d\n",
                temp->name, temp->surname, temp->day, temp->month, temp->year);
            return 0;
        }
        temp = temp->next;
    }
    return 1; // osoba nije pronaðena
}
