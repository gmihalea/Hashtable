#include "Header.h"
#include "Util.h"
#include "List.h"

/**
* Functie care creeaza o tabela de dispersie.
*/
struct HashTable createHashTable(int size)
{
	int i;
	struct HashTable hashTable;

	hashTable.bucketList = (struct Node**)malloc(sizeof(
		struct Node*) * size);

	DIE(hashTable.bucketList == NULL, "Nu s-a putut aloca memorie !\n");

	for(i = 0; i < size; ++i)
		hashTable.bucketList[i] = NULL;
	hashTable.size = size;

	return hashTable;
}

/**
* Functie care adauga un cuvant nou la o tabela de dispersie.
*/

void addWord(struct HashTable hashTable, char *newWord)
{
	addWordToList(&(hashTable.bucketList[hash(
		newWord, hashTable.size)]), newWord);
}

/**
* Functie care sterge un cuvant dintr-o tabela de dispersie.
*/
void removeWord(struct HashTable hashTable, char *word)
{
	removeWordFromList(&(hashTable.bucketList[hash(
		word, hashTable.size)]), word);
}

/**
* Functie care sterge o tabela de dispersie.
*/
void clear(struct HashTable hashTable)
{
	int i;
	for(i = 0; i < hashTable.size; ++i){
		clearList(&(hashTable.bucketList[i]));
		hashTable.bucketList[i] = NULL;
	}
}

/**
* Functie care elibereaza o tabela de dispersie.
*/
void deleteHashTable(struct HashTable hashTable)
{
	int i;
	for(i = 0; i < hashTable.size; ++i)
		clearList(&(hashTable.bucketList[i]));

	free(hashTable.bucketList);
}

/**
* Functie care cauta un cuvant intr-o tabela de dispersie si
* afiseaza True sau False la consola sau in fisier, daca fileName este
* diferit de NULL
*/
void findWord(struct HashTable hashTable, char *word, char *fileName)
{
	int i;
	int found = 0;
	FILE* fd;

	for(i = 0; i < hashTable.size; ++i)
		if(searchWordInList(&(hashTable.bucketList[i]), word) == TRUE)
			found = 1;

	/*
	Daca fileName este null, se va afisa la consola True/False, altfel
	se va afisa in fisier.
	*/
	if(fileName == NULL){

		if(found == 1)
			printf("True\n");
		else
			printf("False\n");
	}
	else{
		fd = fopen(fileName, "a");
		DIE(fd == NULL, "Eroare deschidere fisier !\n");

		if(found == 1)
			fprintf(fd, "True\n");
		else
			fprintf(fd, "False\n");
		fclose(fd);
	}
}

/**
* Functie care redimensioneaza o tabela de dispersie.
* Daca behavior este D, atunci se va dubla.
* Daca behavior este H, atunci se va injumatati.
*/
struct HashTable resize(struct HashTable hashTable, char behavior)
{
	float n;
	int size;
	int i;
	struct HashTable newHashTable;
	struct Node *tempBucket;
	struct Node *currentBucket;

	if(behavior == 'd' || behavior == 'D')
		n = 2;
	if(behavior == 'h' || behavior == 'H')
		n = 0.5;

	/*
	Daca lungimea este (2k + 1), jumatatea va fi k.
	*/
	size = (int)floor(hashTable.size * n);
	newHashTable = createHashTable(size);

	for(i = 0; i < hashTable.size; ++i){
		currentBucket = hashTable.bucketList[i];
		while(currentBucket){
			addWord(newHashTable, currentBucket->value);
			tempBucket = currentBucket;
			currentBucket = currentBucket->next;
			free(tempBucket);
		}
	}
	free(hashTable.bucketList);
	return newHashTable;
}

/**
* Functie care afiseaza o tabela de dispersie la consola sau in fisier, daca 
* fileName este diferit de NULL
*/
void printHashtable(struct HashTable hashtable, char *fileName)
{
	int i;
	for (i = 0; i < hashtable.size; i++)
		printBucket(hashtable, i, fileName);
}

/**
* Functie care afiseaza un anumit bucket din tabela de dispersie.
* Daca fileName == NULL, se va afisa la consola, altfel se va afisa
* in fisier.
*/
void printBucket(struct HashTable hashtable, int index, char *fileName)
{
	int newLine = 0;
	FILE *file;
	struct Node *bucket;
	
	/*
	Selectez bucket-ul de la indexul primit ca parametru.
	*/
	bucket = hashtable.bucketList[index];

	/*
	Daca fileName este null, atunci afisarea se va face la consola,
	altfel se va afisa in fisier.
	*/
	if (fileName == NULL) {
		while (bucket != NULL) {
			printf("%s ", bucket->value);
			bucket = bucket->next;
			newLine = 1;
		}
		/*
		Numai in cazul in care s-a afisat ceva la consola 
		se va trece pe linia urmatoare.
		*/
		if(newLine == 1)
			printf("\n");
	} else {
		file = fopen(fileName, "a");
		DIE(file == NULL, "Nu s-a putut deschide fisierul !\n");

		while (bucket != NULL) {
			fprintf(file, "%s ", bucket->value);
			bucket = bucket->next;
			newLine = 1;
		}
		if(newLine == 1)
			fprintf(file, "\n");
		
		fclose(file);
	}
}

/**
* Functie care citeste o linie dintr-un fisier si o trimite
* mai departe functiei de aplicare a operatiei.
*/
void processLine(struct HashTable *hashTable, FILE *file)
{
	char line[NOCHARACTERS];
	while(fgets(line, sizeof(line), file) != NULL)
		applyOperation(hashTable, line);
}

/**
* Functie care primeste o linie dintr-un fisier, o parseaza si 
* in functie de rezultat aplica o anumita functie deja existenta, 
* de exemplu ADD, REMOVE, etc.
*/
void applyOperation(struct HashTable* hashtable, char *line) {

	char *item = NULL;
	char *nextWord = NULL;
	char behavior;
	int operation = OP_NONE;
	int noOfParameters = 0;
	int result = 0;
	int number;

	item = strtok(line, " \n");
	while(item != NULL) {
		noOfParameters++;

		if (operation == OP_NONE) {
			if (strcmp(item, "add") == 0)
				operation = OP_ADD;
			if (strcmp(item, "remove") == 0)
				operation = OP_REMOVE;
			if (strcmp(item, "find") == 0)
				operation = OP_FIND;
			if (strcmp(item, "print_bucket") == 0)
				operation = OP_PRINT_BUCKET;
			if (strcmp(item, "print") == 0)
				operation = OP_PRINT;
			if (strcmp(item, "resize") == 0)
				operation = OP_RESIZE;
			if (strcmp(item, "clear") == 0)
				operation = OP_CLEAR;
		} else 
			/*
			nextWord va retine ce-a de-a doua parte a comenzii.
			De exemplu pentru comanda: add cuvant, nextWord = cuvant
			*/
			nextWord = item;

		/*
		In cazul in care comanda va avea 3 parametri, ultimul va
		fi retinut in variabila item.
		*/
		item = strtok(NULL, " \n");

		if (noOfParameters == MAX_NO_OF_PARAMS)
			break;
	}

	if (operation == OP_ADD)
		addWord(*hashtable, nextWord);
	if (operation == OP_REMOVE)
		removeWord(*hashtable, nextWord);
	if (operation == OP_FIND)
		findWord(*hashtable, nextWord, item);
	if (operation == OP_PRINT_BUCKET) {
		/*
		In cazul comenzii print_bucket, nextWord va fi indexul
		bucket-ului care trebuie afisat.
		Se verifica daca acesta este numar.
		*/
		result = isNumber(nextWord);
		DIE(result == 0, "Indice bucket invalid !\n");
		number = atoi(nextWord);
		printBucket(*hashtable, number, item);
	}
	if (operation == OP_PRINT)
		printHashtable(*hashtable, nextWord);
	if (operation == OP_CLEAR)
		clear(*hashtable);
	if (operation == OP_RESIZE) {
		/*
		In cazul operatiei resize, nextWord va fi egal cu
		unul dintre cuvintele double/halve.
		Se va verifica care dintre cele doua cuvinte este, si 
		in functie de acesta se va apela functia cu parametru D sau H
		*/
		if(strcmp(nextWord, "double") == 0)
			behavior = 'd';
		if(strcmp(nextWord, "halve") == 0)
			behavior = 'h';

		*hashtable = resize(*hashtable, behavior);
	}
}
