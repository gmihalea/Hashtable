#include "Util.h"

/**
 * Functie de hash bazata pe djb2 a lui Dan Bernstein
 * http://www.cse.yorku.ca/~oz/hash.html
 * @return valoarea de dispersie (cheia)
 */
unsigned int hash(const char *str, unsigned int hash_length)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return (hash % hash_length);
}

/**
* Functie care verifica daca un sir este numar.
*/
int isNumber(char *word)
{
	int i;
	for(i = 0; i < strlen(word); ++i)
		if(!isdigit(word[i]))
			return FALSE;
	return TRUE;
}
