#ifndef HEADER_H_
#define HEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define NO_OF_DEFAULT_ARGC 2
#define NOCHARACTERS 20000
#define MAX_NO_OF_PARAMS 2

#define OP_NONE 0
#define OP_ADD 1
#define OP_CLEAR 2
#define OP_REMOVE 3
#define OP_FIND 4
#define OP_RESIZE 5
#define OP_PRINT_BUCKET 6
#define OP_PRINT 7


/**
 * Structura ce reprezinta tipul elementelor unui bucket
 */
struct Node {
	char *value;
	struct Node *next;
};

/*
* Structura ce reprezinta tabela de dispersie
*/
struct HashTable {
	struct Node **bucketList;
	int size;
};


struct HashTable createHashTable(int size);

void addWord(struct HashTable hashTable, char* newWord);
int searchWord(struct HashTable hashTable, char* word);
void removeWord(struct HashTable hashTable, char* word);
void clear(struct HashTable hashTable);
void deleteHashTable(struct HashTable hashTable);
struct HashTable resize(struct HashTable hashTable, char behavior);
void applyOperation(struct HashTable* hashTable, char* line);
void processLine(struct HashTable* hashTable, FILE* file);
void printBucket(struct HashTable hashtable, int index, char* file_name);
void findWord(struct HashTable hashTable, char* word, char* fileName);
void printHashtable(struct HashTable hashtable, char* file_name);
#endif
