/*
3. Prethodnom zadatku dodati funkcije:
A. dinamièki dodaje novi element iza odreðenog elementa,
B. dinamièki dodaje novi element ispred odreðenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. èita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50   // maksimalna duljina stringa za ime/prezime

// Definicija strukture i typedef
typedef struct person* Position;
struct person {
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    int birthYear;
    Position next;   // pokazivaè na sljedeæi element u listi
};

// Deklaracije svih funkcija
int insertAtFront(Position head);
int printList(Position head);
int insertAtEnd(Position head);
int findPerson(Position head);
int deletePerson(Position head);
int addAfter(Position head);
int addBefore(Position head);
int sort(Position head);
int write(Position head);
int readFromFile(Position head);

// ------------------- MAIN FUNKCIJA -------------------
int main()
{
    struct person head;     // "prazni" poèetni èvor — ne sadrži podatke, samo poèetak liste
    head.next = NULL;
    int number;

    while (1)
    {
        // Ispis izbornika
        printf("Unesite broj(0-10):\n"
            " 1 - Dodaj novi element na pocetak liste\n"
            " 2 - Ispis liste\n"
            " 3 - Dodaj novi element na kraj liste\n"
            " 4 - Pronadi element po prezimenu\n"
            " 5 - Obrisi element iz liste\n"
            " 6 - Dodaj novi element iza odredenog elementa\n"
            " 7 - Dodaj novi element ispred odredenog elementa\n"
            " 8 - Sortiraj listu po prezimenima\n"
            " 9 - Upisi listu u datoteku\n"
            " 10 - Procitaj listu iz datoteke\n"
            " 0 - Izlaz iz programa\n");

        scanf(" %d", &number);

        // Odabir akcije ovisno o unosu korisnika
        if (number == 1)
            insertAtFront(&head);
        else if (number == 2)
            printList(head.next);
        else if (number == 3)
            insertAtEnd(&head);
        else if (number == 4)
            findPerson(head.next);
        else if (number == 5)
            deletePerson(&head);
        else if (number == 6)
            addAfter(&head);
        else if (number == 7)
            addBefore(&head);
        else if (number == 8)
            sort(&head);
        else if (number == 9)
            write(head.next);
        else if (number == 10)
            readFromFile(&head);
        else if (number == 0)
            break;
        else
            printf("Greska, pogresan unos znamenke!\n");
    }

    return EXIT_SUCCESS;
}

// ------------------- FUNKCIJE -------------------

// 1. Dodavanje na poèetak liste
int insertAtFront(Position head)
{
    Position newPerson = (Position)malloc(sizeof(struct person)); // alokacija memorije

    if (!newPerson) {
        printf("Neuspjesna alokacija memorije!\n");
        return EXIT_FAILURE;
    }

    // unos podataka
    printf("Unesite ime osobe: ");
    scanf("%s", newPerson->name);
    printf("Unesite prezime osobe: ");
    scanf("%s", newPerson->surname);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &newPerson->birthYear);

    // umetanje èvora odmah iza head-a
    newPerson->next = head->next;
    head->next = newPerson;

    return EXIT_SUCCESS;
}

// 2. Ispis cijele liste
int printList(Position head)
{
    while (head != NULL) {
        printf("%s %s %d \n", head->name, head->surname, head->birthYear);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// 3. Dodavanje na kraj liste
int insertAtEnd(Position head)
{
    // Pomakni se na zadnji element
    while (head->next != NULL)
        head = head->next;

    Position newPerson = (Position)malloc(sizeof(struct person));
    if (!newPerson) {
        printf("Neuspjesna alokacija memorije!\n");
        return EXIT_FAILURE;
    }

    printf("Unesite ime osobe: ");
    scanf("%s", newPerson->name);
    printf("Unesite prezime osobe: ");
    scanf("%s", newPerson->surname);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &newPerson->birthYear);

    newPerson->next = NULL;  // jer ide na kraj liste
    head->next = newPerson;

    return EXIT_SUCCESS;
}

// 4. Pronalaženje osobe po prezimenu
int findPerson(Position head)
{
    char surname[MAX_LENGTH] = { 0 };

    printf("\nUnesi prezime: ");
    scanf(" %s", surname);

    while (head != NULL && strcmp(surname, head->surname) != 0)
        head = head->next;

    if (head != NULL)
        printf("\nOsoba pronadena -> ime: %s, prezime: %s, godina rodenja: %d\n",
            head->name, head->surname, head->birthYear);
    else
        printf("\nOsoba ne postoji!\n");

    return EXIT_SUCCESS;
}

// 5. Brisanje osobe iz liste po prezimenu
int deletePerson(Position head)
{
    Position previous = head;
    Position current = head->next;
    char deleteSurname[MAX_LENGTH];

    printf("Unesite prezime osobe koju zelite izbrisati: ");
    scanf("%s", deleteSurname);

    while (current != NULL && strcmp(deleteSurname, current->surname) != 0) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        previous->next = current->next;
        free(current);
        printf("Osoba obrisana.\n");
    }
    else {
        printf("Osoba s tim prezimenom nije pronadena.\n");
    }

    return EXIT_SUCCESS;
}

// 6. Dodavanje nove osobe iza odreðene osobe
int addAfter(Position head)
{
    Position newPerson = (Position)malloc(sizeof(struct person));
    if (!newPerson) {
        printf("Greska u alokaciji memorije!\n");
        return EXIT_FAILURE;
    }

    // unos novih podataka
    printf("Unesi ime osobe: ");
    scanf(" %s", newPerson->name);
    printf("Unesi prezime osobe: ");
    scanf(" %s", newPerson->surname);
    printf("Unesi godinu rodenja osobe: ");
    scanf(" %d", &newPerson->birthYear);

    char afterSurname[MAX_LENGTH];
    printf("Unesi prezime osobe iza koje zelite dodati novu osobu: ");
    scanf(" %s", afterSurname);

    // traženje osobe
    while (head->next != NULL && strcmp(afterSurname, head->surname) != 0)
        head = head->next;

    if (strcmp(afterSurname, head->surname) == 0) {
        newPerson->next = head->next;
        head->next = newPerson;
        printf("Osoba unesena.\n");
    }
    else {
        printf("Greska - nema osobe s tim prezimenom!\n");
        free(newPerson);
    }

    return EXIT_SUCCESS;
}

// 7. Dodavanje nove osobe ispred odreðene osobe
int addBefore(Position head)
{
    Position newPerson = (Position)malloc(sizeof(struct person));
    if (!newPerson) {
        printf("Greska u alokaciji memorije!\n");
        return EXIT_FAILURE;
    }

    printf("Unesi ime osobe: ");
    scanf(" %s", newPerson->name);
    printf("Unesi prezime osobe: ");
    scanf(" %s", newPerson->surname);
    printf("Unesi godinu rodenja osobe: ");
    scanf(" %d", &newPerson->birthYear);

    char beforeSurname[MAX_LENGTH];
    printf("Unesi prezime osobe ispred koje zelite dodati novu osobu: ");
    scanf(" %s", beforeSurname);

    // tražimo èvor koji pokazuje na èvor koji ima željeno prezime
    while (head->next != NULL && strcmp(beforeSurname, head->next->surname) != 0)
        head = head->next;

    if (head->next != NULL) {
        newPerson->next = head->next;
        head->next = newPerson;
        printf("Osoba unesena.\n");
    }
    else {
        printf("Greska - nema osobe s tim prezimenom!\n");
        free(newPerson);
    }

    return EXIT_SUCCESS;
}

// 8. Sortiranje liste po prezimenima (bubble sort)
int sort(Position head)
{
    Position current = NULL;
    Position previous = NULL;
    Position temp = NULL;
    Position last = NULL;

    // klasièni bubble sort algoritam
    while (head->next != last) {
        previous = head;
        current = head->next;

        while (current->next != last) {
            if (strcmp(current->surname, current->next->surname) > 0) {
                // zamjena èvorova
                temp = current->next;
                previous->next = temp;
                current->next = temp->next;
                temp->next = current;
                current = temp;
            }
            previous = current;
            current = current->next;
        }
        last = current;
    }

    printf("Lista je sortirana.\n");
    return EXIT_SUCCESS;
}

// 9. Upis liste u tekstualnu datoteku
int write(Position head)
{
    char filename[MAX_LENGTH];
    printf("Unesite ime datoteke u koju zelite upisati listu: ");
    scanf(" %s", filename);

    FILE* filePointer = fopen(filename, "w");
    if (filePointer == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return EXIT_FAILURE;
    }

    // upis svakog èlana liste u datoteku
    while (head != NULL) {
        fprintf(filePointer, "%s %s %d\n", head->name, head->surname, head->birthYear);
        head = head->next;
    }

    fclose(filePointer);
    printf("Lista ispisana u datoteku.\n");
    return EXIT_SUCCESS;
}

// 10. Èitanje liste iz datoteke
int readFromFile(Position head)
{
    char filename[MAX_LENGTH];
    printf("Unesite ime datoteke iz koje zelite ucitati listu: ");
    scanf(" %s", filename);

    FILE* filePointer = fopen(filename, "r");
    if (filePointer == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return EXIT_FAILURE;
    }

    // brišemo staru listu
    head->next = NULL;
    Position P = head;
    Position q = NULL;

    // èitamo dok ima podataka
    while (1) {
        q = (Position)malloc(sizeof(struct person));
        if (q == NULL) {
            printf("Greska u alokaciji memorije!\n");
            fclose(filePointer);
            return EXIT_FAILURE;
        }

        // ako je kraj datoteke, prekidamo
        if (fscanf(filePointer, "%s %s %d", q->name, q->surname, &q->birthYear) != 3) {
            free(q);
            break;
        }

        q->next = NULL;
        P->next = q;
        P = q;
    }

    fclose(filePointer);
    printf("Lista ucitana iz datoteke.\n");
    return EXIT_SUCCESS;
}
