/*
4. Napisati program za zbrajanje i množenje polinoma. 
Koeficijenti i eksponenti se čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura koja predstavlja jedan član polinoma
typedef struct _Poly* Position;
typedef struct _Poly {
    int coefficient;   // koeficijent uz x^n
    int exponent;      // eksponent (stupanj)
    Position next;     // pokazivač na sljedeći član liste
} Poly;

// Deklaracije funkcija
int readPolyFromFile(char filename[], Position poly1, Position poly2);
int addToList(Position poly, Position newElement);
Position createElement(int coefficient, int exponent);
int sumPoly(Position poly1, Position poly2, Position sumResult);
int multiplyPoly(Position poly1, Position poly2, Position multiplyResult);
int printList(Position poly);

int main() {

    // Svaki polinom se predstavlja pomoću "praznog" početnog čvora (head)
    Poly poly1 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly poly2 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly multiply = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly sum = {.coefficient = 0, .exponent = 0, .next = NULL};
    char filename[50];

    printf("Unesite ime dokumenta iz kojeg citamo polinome: ");
    scanf(" %[^\n]", filename); // čitanje cijelog imena datoteke (uključujući razmake)

    // Učitavanje polinoma iz datoteke
    readPolyFromFile(filename, &poly1, &poly2);

    // Računanje umnoška polinoma
    multiplyPoly(&poly1, &poly2, &multiply);

    // Ispis oba učitana polinoma
    printf("\nPolinom 1: ");
    printList(&poly1);
    printf("\nPolinom 2: ");
    printList(&poly2);

    // Računanje sume polinoma
    sumPoly(&poly1, &poly2, &sum);

    printf("\n-------Mnozenje--------\n");
    printList(&multiply);
    printf("\n-------Zbrajanje-------\n");
    printList(&sum);
    printf("\n");

    return EXIT_SUCCESS;
}

/*
    čita dva polinoma iz datoteke. 
    Svaki redak u datoteci sadrži parove (koeficijent, eksponent).
*/
int readPolyFromFile(char filename[], Position poly1, Position poly2) 
{
    FILE* fp = NULL;
    int coefficient = 0;
    int exponent = 0;
    int numberOfBytes = 0; // broj znakova pročitanih u jednom koraku
    char* line = NULL;
    char staticLine[1024] = {0};
    Position newElement = NULL;

    fp = fopen(filename, "r"); // otvaranje datoteke za čitanje

    if(!fp) 
    {
        printf("Dokument se ne moze otvoriti!\n");
        return EXIT_FAILURE;
    }

    line = (char*)malloc(1024 * sizeof(char));
    if(!line) 
    {
        printf("Memorija za redak se ne moze alocirati!\n");
        return EXIT_FAILURE;
    }

    // Čitanje prvog reda (prvi polinom)
    fgets(staticLine, 1024, fp);
    line = staticLine;

    // Dok ima sadržaja u retku
    while(strlen(line) > 0) 
    {
        // Čita jedan par "koeficijent eksponent"
        // %n pamti broj pročitanih znakova
        sscanf(line, "%d %d %n", &coefficient, &exponent, &numberOfBytes);

        if(coefficient != 0)  // ako je koeficijent različit od 0, dodaj član u listu
        {
            newElement = createElement(coefficient, exponent);
            addToList(poly1, newElement);
        }

        // Pomicanje pokazivača za broj pročitanih bajtova
        line += numberOfBytes;
    }

    // Čitanje drugog reda (drugi polinom) 
    fgets(staticLine, 1024, fp);
    line = staticLine;

    while(strlen(line) > 0) 
    {
        sscanf(line, "%d %d %n", &coefficient, &exponent, &numberOfBytes);
        
        if(coefficient != 0)
        {
            newElement = createElement(coefficient, exponent);
            addToList(poly2, newElement);
        }
        line += numberOfBytes;
    }

    fclose(fp); // zatvaranje datoteke

    return EXIT_SUCCESS;
}

/*
     stvara novi čvor (član polinoma)
*/
Position createElement(int coefficient, int exponent) 
{
    Position newElement = NULL;
    newElement = (Position)malloc(sizeof(Poly));

    if(!newElement) 
    {
        printf("Memorija za novi element se ne moze alocirati!\n");
        return NULL;
    }

    // Postavljanje vrijednosti
    newElement->coefficient = coefficient;
    newElement->exponent = exponent;
    newElement->next = NULL;
    
    return newElement;
}

/*

    dodaje novi element u polinom (sortirano po eksponentu, silazno).
    Ako postoji član s istim eksponentom, sabira se s postojećim.
*/
int addToList(Position poly, Position newElement) {

    // Ako je lista prazna – novi element ide prvi
    if(poly->next == NULL)
        poly->next = newElement;
    else 
    {
        // Tražimo mjesto gdje novi element treba ući
        while(poly->next != NULL && poly->next->exponent > newElement->exponent)
            poly = poly->next;

        // Ako već postoji isti eksponent – zbroji koeficijente
        if(poly->next != NULL && poly->next->exponent == newElement->exponent)
        {
            poly->next->coefficient += newElement->coefficient;  
            free(newElement); // novi element se ne koristi, pa se briše
        }
        else
        {
            // Umetni novi element u listu
            newElement->next = poly->next;
            poly->next = newElement;
        }
    }

    return EXIT_SUCCESS;
}

/*
    ispisuje polinom u obliku (npr. 3x^4 + 2x^2 + 1)
*/
int printList(Position poly) 
{
    while (poly->next != NULL) 
    {
        poly = poly->next;
       
        if(poly->next == NULL) // zadnji element
        {
            if(poly->exponent == 0)
                printf("%d", poly->coefficient);
            else
                printf("%dx^%d", poly->coefficient, poly->exponent);
        }
        else if(poly->exponent == 0)
            printf("%d + ", poly->coefficient);
        else
            printf("%dx^%d + ", poly->coefficient, poly->exponent);
    }

    return EXIT_SUCCESS;
}

/*
    
množi dva polinoma. 
Svaki član iz prvog množi sa svakim iz drugog, 
a rezultat se dodaje u novu listu (sabiru se članovi istih eksponenata).
*/
int multiplyPoly(Position poly1, Position poly2, Position multiplyResult) 
{
    Position newElement = NULL;
    Position privremena = poly2; // čuvamo početak drugog polinoma

    while(poly1->next != NULL) 
    { 
        poly1 = poly1->next;
        poly2 = privremena;

        while(poly2->next != NULL) 
        {
            poly2 = poly2->next;
            // novi član: (a*x^m) * (b*x^n) = (a*b)*x^(m+n)
            newElement = createElement(poly1->coefficient * poly2->coefficient, poly1->exponent + poly2->exponent);
            addToList(multiplyResult, newElement);
        }
    }

    return EXIT_SUCCESS;
}

/*
    zbraja dva polinoma.
    Oba polinoma se jednostavno "kopiraju" u novu listu pomoću addToList,
    koja automatski sabira članove s istim eksponentima.
*/
int sumPoly(Position poly1, Position poly2, Position sumResult)
{  
    Position temp;
    temp = poly1;
     
    // Dodavanje članova prvog polinoma u rezultat
    while(temp->next)
    {
        addToList(sumResult, createElement(temp->next->coefficient, temp->next->exponent));
        temp = temp->next;
    }
     
    temp = poly2;
     
    // Dodavanje članova drugog polinoma u rezultat
    while(temp->next)
    {
        addToList(sumResult, createElement(temp->next->coefficient, temp->next->exponent));
        temp = temp->next;
    }
     
    return EXIT_SUCCESS;
}
