#include <stdlib.h>
#include <ncurses.h>

#include <array.h>
#include <rand.h>

#define LOWER_CASE 1 << 0 // 1 in decimal
#define UPPER_CASE 1 << 1 // 2 in decimal
#define NUMBERS 1 << 2 // 4 in decimal
#define SYMBOLS 1 << 3 // 8 in decimal

#define ALPHABETS_RANGE 26 // Range of Alphabets
#define NUMBERS_RANGE 10 // Range of Number
#define SYMBOLS_RANGE 30 // Range of Symbols

/**
 * @brief Sets the character options for generating random arrays.
 * 
 * This function takes a string of options and sets the corresponding flags in the randArray structure.
 * The options can include:
 * - '1' for lower case letters
 * - '2' for upper case letters
 * - '3' for numbers
 * - '4' for symbols
 * 
 * If an unknown option is encountered, it will be printed as an error message.
 * 
 * @param option The string of options.
 * @param ptr A pointer to the randArray structure.
 */
void charOptions(const char *option, randArray *ptr) {
    ptr->type = 0;

    for(uint8_t i = 0; option[i]; i++) {
        switch(option[i]) {
            case '1':
                ptr->type |= LOWER_CASE;
                break;
            case '2':
                ptr->type |= UPPER_CASE;
                break;
            case '3':
                ptr->type |= NUMBERS;
                break;
            case '4':
                ptr->type |= SYMBOLS;
                break;
            default:
                // Check if the option is not EOT (ASCII)
                if (option[i] != '\04') {
                    // If program is running in Terminal Mode, print the error message in the terminal window
                    if (ptr->start == TRUE) {
                        printw("Unknown option %c!\n", option[i]);

                        refresh();      // Refresh the terminal window
                        napms(800);     // Sleep for 800 milliseconds
                    } 
                    else {
                        printf("Unknown option %c!\n", option[i]);
                    }
                }
        }
    }
}

/**
 * @brief Creates a random array based on the specified options.
 * 
 * This function generates a random array by selecting characters from different ranges based on the options specified in the `ptr` parameter.
 * The range of characters to be used for generating the random array is determined by summing the ranges of the selected options.
 * The generated array is stored in the `genArr` member of the `ptr` structure.
 * The generated character array is stored in the `genChar` member of the `ptr` structure.
 * 
 * @param ptr Pointer to the `randArray` structure.
 */
void createArray(randArray *ptr) {
    uint16_t iter1 = 0, iter2 = 0;  // Iterators (iter1 for the for loop, iter2 for the array)
    uint8_t range = 0;
    char *chars = 0;

    // Store the range of characters to be used for generating the random array
    // If multiple options are selected, the range is the sum of the ranges of the selected options
    if(ptr->type & LOWER_CASE) range += ALPHABETS_RANGE;
    if(ptr->type & UPPER_CASE) range += ALPHABETS_RANGE;
    if(ptr->type & NUMBERS) range += NUMBERS_RANGE;
    if(ptr->type & SYMBOLS) range += SYMBOLS_RANGE;

    // Allocate memory for the array
    ptr->genArr = malloc(range + 1);

    // Generate the random array (To be used for generating the random character array)
    if(ptr->type & LOWER_CASE){
        chars = "abcdefghijklmnopqrstuvwxyz";
        for(iter1 = 0; iter1 < ALPHABETS_RANGE; iter2++, iter1++) ptr->genArr[iter2] = chars[iter1];
    }
    if(ptr->type & UPPER_CASE){
        chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(iter1 = 0; iter1 < ALPHABETS_RANGE; iter2++, iter1++) ptr->genArr[iter2] = chars[iter1];
    }
    if(ptr->type & NUMBERS){
        chars = "0123456789";
        for(iter1 = 0; iter1 < NUMBERS_RANGE; iter2++, iter1++) ptr->genArr[iter2] = chars[iter1];
    }
    if(ptr->type & SYMBOLS){
        chars = "()[]{}#:;^,.?!|&_`~@$%/=+-*'<>";
        for(iter1 = 0; iter1 < SYMBOLS_RANGE; iter2++, iter1++) ptr->genArr[iter2] = chars[iter1];
    }

    ptr->genArr[iter2] = '\0'; // End with NULL CHARACTER
    ptr->genChar = malloc(ptr->length + 1); // Allocate memory for the generated character array

    // Generate the random array (To be outputted)
    for(iter1 = 0; iter1 < ptr->length; iter1++)
        ptr->genChar[iter1] = ptr->genArr[getNextRand(range)];
    
    ptr->genChar[iter1] = '\0'; // End with NULL CHARACTER

    free(ptr->genArr); // Free the memory allocated for the array
}
