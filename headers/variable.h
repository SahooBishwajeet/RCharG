#ifndef VARIABLE_H
#define VARIABLE_H

/*
* Structure for the random array
* start: the starting character
* length: the length of the array
* type: the type of the array (lowercase, uppercase, numbers, symbols)
* genChar: the generated character
* genArr: the generated array, kind of like storing the valid characters
*/
typedef struct {
    char start;
    unsigned int length;
    unsigned short int type;
    char *genChar;
    char *genArr; 
} randArray;

#endif // VARIABLE_H