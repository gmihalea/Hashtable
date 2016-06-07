# Hashtable
Multi-platform Hashtable implementation

Operations accepted:
* add [word]
* remove [word]
* find [word] [output_file]
* clear
* print_bucket [index_bucket] [output_file]
* print [output_file]
* resize double
* resize halve

Observations:
* The implementation works for both platforms Linux (GNUmakefile) and Windows (Makefile)
* The values from hashtable are words [A_Za-z]+
* The hash function used in the entire program is by Dan Bernstein (http://www.cse.yorku.ca/~oz/hash.html)

