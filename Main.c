#include "Header.h"
#include "Util.h"
#include "List.h"


int main(int argc, char **argv) 
{
	int noOfFiles;
	int size;
	int i;
	FILE *fileName;
	struct HashTable hashTable;

	/*
	Se verifica daca apelul este executat corespunzator: numarul de 
	parametri este >= 2, iar al doilea parametru este numar. 
	*/
	DIE(argc < NO_OF_DEFAULT_ARGC, "Numar incorect de parametri !\n");
	DIE(isNumber(argv[1]) == FALSE, "Primul parametru nu este numar !\n");

	size = atoi(argv[1]);
	noOfFiles = argc - NO_OF_DEFAULT_ARGC;

	hashTable = createHashTable (size);

	/*
	Daca numarul de fisiere este egal cu zero, se va face citirea
	de la stdin. Altfel, se va face din fisierele primite in linie
	de comanda.
	*/
	if(noOfFiles == 0)
		processLine(&hashTable, stdin);
	else{
		for(i = 0; i < noOfFiles; ++i){
			fileName = fopen(argv[i + NO_OF_DEFAULT_ARGC], "r");
			DIE(fileName == NULL, "Nu s-a putut deschide fisierul"
				"de intrare\n");
			processLine(&hashTable, fileName);
			fclose(fileName);
		}
	}
	deleteHashTable(hashTable);
	return 0;
}
