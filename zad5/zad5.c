/*
5. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack* Position;
struct Stack {
	int element;      // vrijednost spremljena u stog
	Position next;    // pokazivač na sljedeći element
};

// Prototipovi funkcija
int readPostfixFromFile(Position head);
int push(Position head, int element);
int pop(Position head, int* element);

int main()
{
	struct Stack Head;  // Stvaramo glavu
	Head.next = NULL;   // Stog je u početku prazan

	// Čitanje i računanje postfix izraza
	if (readPostfixFromFile(&Head) == EXIT_FAILURE)
		return EXIT_FAILURE;

	// Ispis rezultata 
	if (Head.next != NULL)
		printf("\nRezultat je %d\n", Head.next->element);
	else
		printf("\nGreska: stog je prazan.\n");

	// Pražnjenje stoga nakon završetka
	int poppedElement;
	while (pop(&Head, &poppedElement) == EXIT_SUCCESS);

	return EXIT_SUCCESS;
}

// Čitanje postfix izraza iz datoteke i izvođenje operacija
int readPostfixFromFile(Position head)
{
	FILE* filePointer = fopen("postfix.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return EXIT_FAILURE;
	}

	char token[10];
	int x, y;

	// Čitamo riječ po riječ sve dok ih ima
	while (fscanf(filePointer, "%s", token) == 1)
	{
		// Ako je riječ operator, pop + operacija + push
		if (strcmp(token, "+") == 0)
		{
			if (pop(head, &x) == EXIT_FAILURE || pop(head, &y) == EXIT_FAILURE) return EXIT_FAILURE;
			push(head, y + x);
		}
		else if (strcmp(token, "-") == 0)
		{
			if (pop(head, &x) == EXIT_FAILURE || pop(head, &y) == EXIT_FAILURE) return EXIT_FAILURE;
			push(head, y - x);
		}
		else if (strcmp(token, "*") == 0)
		{
			if (pop(head, &x) == EXIT_FAILURE || pop(head, &y) == EXIT_FAILURE) return EXIT_FAILURE;
			push(head, y * x);
		}
		else if (strcmp(token, "/") == 0)
		{
			if (pop(head, &x) == EXIT_FAILURE || pop(head, &y) == EXIT_FAILURE) return EXIT_FAILURE;
			if (x == 0)
			{
				printf("Greska: dijeljenje sa 0!\n");
				return EXIT_FAILURE;
			}
			push(head, y / x);
		}
		// Inače je operand → pretvori u broj i spremi na stog
		else
		{
			push(head, atoi(token));
		}
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

// Funkcija za spremanje vrijednosti na stog (na vrh)
int push(Position head, int element)
{
	Position newNode = (Position)malloc(sizeof(struct Stack));
	if (!newNode)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return EXIT_FAILURE;
	}

	newNode->element = element;
	newNode->next = head->next;
	head->next = newNode;

	return EXIT_SUCCESS;
}

// Funkcija za skidanje vrijednosti sa stoga (sa vrha)
int pop(Position head, int* element)
{
	if (head->next == NULL)
	{
		// Stog je prazan → greška
		return EXIT_FAILURE;
	}

	Position temp = head->next;    // čvor koji skidamo
	*element = temp->element;       // vraćamo njegovu vrijednost
	head->next = temp->next;        // vrh stoga prelazi na sljedeći čvor
	free(temp);                     // brisanje starog vrha

	return EXIT_SUCCESS;            // uspjeh
}
