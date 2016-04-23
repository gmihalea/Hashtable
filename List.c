#include "Header.h"
#include "Util.h"

/**
* Functie care adauga un cuvant intr-o lista.
*/
void addWordToList(struct Node **headList, char *new_word)
{
	struct Node *p;

	if(*headList == NULL){

		*headList = (struct Node*)malloc(sizeof(struct Node));
		DIE(*headList == NULL, "Nu s-a putut aloca memorie !\n");

		(*headList)-> value = (char*)malloc(strlen(new_word) + 1);
		DIE((*headList)-> value == NULL, "Nu s-a alocat memorie !\n");

		memcpy((*headList)-> value, new_word, strlen(new_word) + 1);
		(*headList)->next = NULL;
	}
	else{

		for(p = *headList;;p = p->next){
			/*
			Daca cuvantul exista deja in lista, va fi ignorat.
			*/
			if(strcmp(new_word, p->value) == 0)
				break;

			if(p->next == NULL){

				p->next = (struct Node*)malloc(
					sizeof(struct Node));
				DIE(p->next == NULL, "Eroare alocare"
					"memorie !\n");

				p->next->value = (char*)malloc(
					strlen(new_word) + 1);
				DIE(p->next->value == NULL, "Eroare alocare"
					"memeorie !\n");
				memcpy(p->next->value, new_word,
					strlen(new_word) + 1);
				p->next->next = NULL;
				break;
			}
		}
	}
}

/**
* Functie care cauta un cuvant intr-o lista.
*/
int searchWordInList(struct Node **headList, char *wordToFind)
{

	struct Node *p;
	if(*headList == NULL){
		return FALSE;
	}
	else{
		for(p = *headList; p != NULL; p = p->next){
			if(strcmp(wordToFind, p->value) == 0)
				return TRUE;
		}
	}
	return FALSE;
}

/**
* Functie care sterge un cuvant dintr-o lista.
*/
void removeWordFromList(struct Node **headList, char *wordToRemove)
{
	struct Node *p;
	struct Node *q;

	if(*headList == NULL)
		return;

	if(strcmp(wordToRemove, (*headList)->value) == 0){
		struct Node* temp;
		temp = *headList;
		*headList = (*headList)->next;
		free(temp);
	}
	else{
		for(p = *headList, q = p->next;
			q != NULL;
			p = p->next, q = q->next){
			if(strcmp(wordToRemove, q->value) == 0){
				p->next = q->next;
				free(q);
				break;
			}
		}
	}
}

/**
* Functie care elibereaza o lista.
*/
void clearList(struct Node **headList)
{
	struct Node *p;
	struct Node *q;

	if(*headList == NULL)
		return;

	p = *headList;

	while(p){
		q = p;
		p = p->next;
		free(q);
	}
}

/**
* Functie care afiseza o lista.
*/
void print(struct Node *headList)
{
	while(headList){
		printf("%s ", headList->value);
		headList = headList->next;
	}
	printf("\n");
}

/**
* Functie care printeaza bucketul de la un anumit index.
*/
void printList(struct Node **buckets, int index)
{
	print(buckets[index]);
}

/**
* Functie care printeaza o lista intr-un fisier.
*/
void printListInFile(struct Node **buckets, int index, char *fileName)
{
	FILE *fd;

	fd = fopen(fileName, "a");
	DIE(fd == NULL, "Nu s-a putut deschide fisierul !\n");

	while(buckets[index]){
		fprintf(fd, "%s ", (buckets[index])->value);
		buckets[index] = (buckets[index])->next;
	}
	fprintf(fd, "\n");

	fclose(fd);
}

/**
* Functie care afiseaza toate bucket-urile unei tabele.
*/
void printBuckets(struct Node **buckets, int size)
{
	int i;
	for(i = 0; i < size; ++i)
		printList(buckets, i);
}

/**
* Printeaza toate Bucket-urile intr-un fisier.
*/
void printBucketsInFile(struct Node **buckets, char *fileName, int size)
{
	FILE *fd;
	int i;
	fd = fopen(fileName, "a");
	DIE(fd == NULL, "Eroare deschidere fisier !\n");

	for(i = 0; i < size; ++i){
		while(buckets[i]){
			fprintf(fd, "%s ", (buckets[i])->value);
			buckets[i] = (buckets[i])->next;
		}
		fprintf(fd, "\n");
	}
	fclose(fd);
}
