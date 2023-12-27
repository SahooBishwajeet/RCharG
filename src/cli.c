#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <array.h>
#include <cli.h>

/**
 * Converts a string to an integer.
 *
 * This function takes a string as input and converts it to an integer.
 * It supports both positive and negative numbers.
 *
 * @param string The string to be converted.
 * @return The converted integer value.
 */
int customAtoI(char *string) {
    uint8_t count = 0, result = 0;
    char sign = 1;  // sign == 1 ? positive : negative;

    if(string[0] == '-') count++, sign = -1;
    while (string[count] >= '0' && string[count] <= '9') {
        result = (result * 10) + (string[count] - '0');
        count++;
    }

    return result * sign;
}

/**
 * @brief Executes the command line interface (CLI) based on the provided arguments.
 * 
 * @param argv The array of command line arguments.
 * @param ptr A pointer to the randArray structure.
 */
void cli(char **argv, randArray *ptr) {
    char *str = argv[3];

    if(strcmp("--help", argv[1]) == 0) {
        printf("Usages: rcharg, rcharg --help, rcharg --gen [size] [type]\n\n"
            "Commands:\n"
            "help      prints informations about rcharg\n"
            "gen       generates characters using the size and type\n\n"
            "Instructions:\n"
            "Size = A positive number from 1 up to 6000\n"
            "Type = One or more options [LowerCase, UpperCase, Number, Symbol] from 1 up to 4, in any order\n");
    }
    else if(strcmp("--gen", argv[1]) == 0) {
        ptr->length = customAtoI(argv[2]);

        strcpy(str, argv[3]);
        charOptions(str, ptr);
        createArray(ptr);

        printf("%s\n", ptr->genChar);

        free(ptr->genChar);
    }
    else printf("Unknown Usage, Use \"--help\" Argument\n");
}