#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include <array.h>
#include <cli.h>
#include <tui.h>

/**
 * @brief The main function of the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char **argv) {
    // Initialize variables
    randArray array;
    bool randomiseRepeat = FALSE;
    uint8_t choice = 0;

    array.start = FALSE;

    // Check if the program is run with the correct arguments
    if(strcmp(argv[0], argv[argc - 1]) == OK) {
        initscr();
        array.start = TRUE;
    }
    else {
        cli(argv, &array);
        return 0;
    }

    // Main program loop
    while(TRUE) {
        if(!randomiseRepeat) {
            getSize(&array);
            getType(&array);
        }
        createArray(&array);
        setOutput(&array);
        free(array.genChar);

        // Get user input
        choice = getch();

        // Process user input
        if(choice == 's') randomiseRepeat = FALSE;
        else if(choice == 'r') randomiseRepeat = TRUE;
        else break;
    }
    endwin();

    return 0;
}