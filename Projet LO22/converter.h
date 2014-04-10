#ifndef CONVERTER_INCLUDED
#define CONVERTER_INCLUDED

#include <stdlib.h>
#include <string.h>

/* This define the buffer size */
#define BUFFER_SIZE 200

/*
 * Insert the string source at the beggining of the string dest
 * source - source string, will not be modify
 * dest - destination string
 */
void insertAtStart(const char* source, char* dest);

/*
 * Return the index of the first occurence of the string str2
 * in the string str1
 * str1 - A string
 * str2 - An other string
 */
int getFirstOccurenceInString(const char* str1, const char* str2);

/*
 * Return a string which contain the n first element of the string str
 * return a new allocated string
 * str - the string we want to cut
 * n - the number of character we want to cut
 */
char* cutStringFromStart(const char* str, int n);

/*
 * Remove the white space at the beggining and at the end of the string s
 * need to save s for further free
 * s - string to trim
 */
void trim(char* s);

/*
 * Return the index of toCompare founded in arr,
 * return 0 if nothing is found
 * arr - an array of string
 * arraySize - the size of arr
 * toCompare - string we want to find
 */
int contains(char* arr[], int arraySize, char* toCompare);

/*
 * return 10^(3*i) for i=1, 2 and 3
 * i - the power we want must belong to { 1, 2, 3 } for proper work
 */
unsigned int getPowerWithI(int i);

/*
 * Translate a string into an integer using french grammar
 * part of letter2int function, translate number from 0 to 999
 * chaineNombre - string to translate
 */
int letter2intPacket(char* chaineNombre);

/*
 * Translate a string into an integer using french grammar
 * translate number from 0 to INT_MAX
 * chaineNombre - string to translate
 */
unsigned int letter2int(char* chaineNombre);

/*
 * Translate a positif number into a string using french grammar
 * translate number from 0 to INT_MAX
 * value - value to translate
 */
char* int2letter(unsigned int value);

#endif // CONVERTER_INCLUDED
