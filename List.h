#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int addWordToList(struct Node **headList, char *new_word);
void removeWordFromList(struct Node **headList, char *wordToRemove);
void clearList(struct Node **headList);
int searchWordInList(struct Node **headList, char *wordToFind);
void print(struct Node *headList);
void printList(struct Node **headList, int index);
void printListInFile(struct Node **headList, int index, char *fileName);
void printBucketsInFile(struct Node **buckets, char *fileName, int size);
void printBuckets(struct Node **buckets, int size);
