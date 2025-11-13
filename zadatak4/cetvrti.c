/*
4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Poly* Position;
typedef struct _Poly {
    int coefficient;
    int exponent;
    Position next;
}Poly;

int readPolyFromFile(char filename[], Position poly1, Position poly2);
int addToList(Position poly, Position newElement);
Position createElement(int coefficient, int exponent);
int sumPoly(Position poly1, Position poly2, Position sumResult);
int multiplyPoly(Position poly1, Position poly2, Position multiplyResult);
int printList(Position poly);

int main() {

    Poly poly1 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly poly2 = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly multiply = {.coefficient = 0, .exponent = 0, .next = NULL};
    Poly sum = {.coefficient = 0, .exponent = 0, .next = NULL};
    char filename[50];

    printf("Unesite ime dokumenta iz kojeg citamo polinome: ");
    scanf(" %[^\n]", filename);

    readPolyFromFile(filename, &poly1, &poly2);

    multiplyPoly(&poly1, &poly2, &multiply);

    printf("\nPolinom 1: ");
    printList(&poly1);
    printf("\nPolinom 2: ");
    printList(&poly2);

    sumPoly(&poly1, &poly2, &sum);

    printf("\n-------Mnozenje--------\n");
    printList(&multiply);
    printf("\n-------Zbrajanje-------\n");
    printList(&sum);
    printf("\n");

    return EXIT_SUCCESS;
}

int readPolyFromFile(char filename[], Position poly1, Position poly2) 
{
    FILE* fp = NULL;
    int coefficient = 0;
    int exponent = 0;
    int numberOfBytes = 0;
    char* line = NULL;
    char staticLine[1024] = {0};
    Position newElement = NULL;

    fp = fopen(filename, "r");

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

    fgets(staticLine, 1024, fp);
    line = staticLine;

    while(strlen(line) > 0) 
    {
        sscanf(line, "%d %d %n", &coefficient, &exponent, &numberOfBytes);

        if(coefficient != 0) 
        {
            newElement = createElement(coefficient, exponent);
            addToList(poly1, newElement);
        }
        line += numberOfBytes;
    }

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
    fclose(fp);

    return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent) 
{
    Position newElement = NULL;
    newElement = (Position)malloc(sizeof(Poly));

    if(!newElement) 
    {
        printf("Memorija za novi element se ne moze alocirati!\n");
        return NULL;
    }

    newElement->coefficient = coefficient;
    newElement->exponent = exponent;
    newElement->next = NULL;
    
    return newElement;
}

int addToList(Position poly, Position newElement) {

    if(poly->next == NULL)
        poly->next = newElement;
    else 
    {
        while(poly->next != NULL && poly->next->exponent > newElement->exponent)
            poly = poly->next;

        if(poly->next != NULL && poly->next->exponent == newElement->exponent)
        {
            poly->next->coefficient += newElement->coefficient;  
            free(newElement);
        }
        else
        {
            newElement->next = poly->next;
            poly->next = newElement;
        }
    }

    return EXIT_SUCCESS;
}

int printList(Position poly) 
{
    while (poly->next != NULL) 
    {
        poly = poly->next;
       
        if(poly->next == NULL) 
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

int multiplyPoly(Position poly1, Position poly2, Position multiplyResult) 
{
    Position newElement = NULL;
    Position privremena = poly2;

    while(poly1->next != NULL) 
    { 
        poly1 = poly1->next;
        poly2 = privremena;

        while(poly2->next != NULL) 
        {
            poly2 = poly2->next;
            newElement = createElement(poly1->coefficient * poly2->coefficient, poly1->exponent + poly2->exponent);
            addToList(multiplyResult, newElement);
        }
    }

    return EXIT_SUCCESS;
}

 int sumPoly(Position poly1, Position poly2, Position sumResult)
 {  
    Position temp;
    temp = poly1;
     
    while(temp->next)
    {
        addToList(sumResult, createElement(temp->next->coefficient, temp->next->exponent));
        temp = temp->next;
    }
     
    temp = poly2;
     
    while(temp->next)
    {
        addToList(sumResult, createElement(temp->next->coefficient, temp->next->exponent));
        temp = temp->next;
    }
     
    return EXIT_SUCCESS;
 }
