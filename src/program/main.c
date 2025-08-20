/**
 * @file main.c
 * @brief Main entry point for the numerical integration program.
 *
 * This program provides a user interface for performing numerical integration
 * using Reverse Polish Notation. It allows users to input functions and
 * intervals, and it integrates the functions based on the provided inputs.
 *
 * The program also includes functionality to read and display saved functions
 * from a file.
 */


#include "controls.h"
#include "debugmalloc.h"


/**
 * @brief Entry point of the program. Provides a menu interface for numerical
 * integration and file logging functionality.
 *
 * This function interacts with the user by displaying rules and a menu
 * interface. It allows the user to choose between performing numerical
 * integration, viewing saved functions from a file, or exiting the program.
 * User inputs are processed in a loop until an exit condition is met.
 */
int main(const int argc, char* argv[]) {
    print_rules();
    int num;

    do {
        const char* filename = "functions.txt";
        print_menu();
        scanf("%d", &num);
        printf("\n");

        switch (num) {
            case 1:
                numerical_integration(argc, argv, filename);
                break;

            case 2:
                integrate_last(filename);
                break;

            case 3:
                log_file_content(filename);
                break;

            default:
                break;
        }
    } while (num == 1 || num == 2 || num == 3);

    return 0;
}
