#include <ncurses.h>
#include <stdlib.h>

#include <array.h>
#include <tui.h>

/**
 * @brief Gets the size of the generated string from the user.
 * 
 * This function prompts the user to enter the length of the generated string.
 * It validates the input and ensures that the length is within a valid range.
 * 
 * @param ptr A pointer to the randArray structure.
 */
void getSize(randArray *ptr) {
    ptr->length = 0;

    while(TRUE) {
        clear();
        printw("Random Character Generator\nEnter The Length Of The Generated String: ");
        refresh();
        scanw("%u", &(ptr->length));

        if(ptr->length > 0 && ptr->length < 32767) break;   // As we have set "uint16_t iter2 = 0;" in "void createArray(randArray *ptr);"
        printw("invalid Value\n");
        refresh();
        napms(500);
    }
}

/**
 * @brief Prompts the user to select an option and stores the selected option in the randArray structure.
 * 
 * This function displays a menu of options to the user and waits for the user to input their selection.
 * The selected option is then stored in the randArray structure pointed to by ptr.
 * The function continues to prompt the user until a valid option is selected.
 * 
 * @param ptr A pointer to the randArray structure where the selected option will be stored.
 */
void getType(randArray *ptr){
    char input[4], *str = input;
    uint8_t count = 0;

    while(TRUE) {
        clear();
        printw("Select Option(s) [In Any Order]:\n (1) LowerCase (a-z)\n (2) UpperCase (A-Z)\n (3) Numbers (0-9)\n (4) Symbols (#-!)\n");
        refresh();
        getnstr(input, sizeof(input));

        for(; count < 5; count++)
            str[count] = input[count];
        charOptions(str, ptr);
        if(ptr->type > 0) break;
    }
}

void setOutput(randArray *ptr){
    clear();
    printw("%i characters generated: %s\n(Size in bits: %i)\n\nWhat To Do Now?\n Randomise [r]\n Start Over [s]\n Exit [Any Key]\n",
        ptr->length, ptr->genChar, ptr->length * 8);
    refresh();
}