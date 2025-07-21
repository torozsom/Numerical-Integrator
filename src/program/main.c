/**
 * @file main.c
 * @brief Main entry point for the numerical integration program.
 *
 * This program provides a user interface for performing numerical integration
 * using Reverse Polish Notation. It allows users to input functions and intervals,
 * and it integrates the functions based on the provided inputs.
 *
 * The program also includes functionality to read and display saved functions
 * from a file.
 */


#include "debugmalloc.h"
#include "gui.h"
#include "integral.h"
#include "expression_parser.h"


/**
 * @brief Prints the rules and guidelines for using the numerical integration program.
 *
 * This method displays the integral computation rules, including the format and constraints
 * for entering inputs (e.g., using Reverse Polish Notation, entering spaces between operands,
 * keeping input length within 100 characters). These guidelines assist users in properly
 * utilizing the numerical integration program.
 *
 * @note The improper use of operators or operands may cause the program to terminate.
 */
void print_rules() {
    printf("Welcome to my program of numerical integration!\n"
        "------------------------------------------------------------------------"
        "----------------------------------------\n"
        "| The rules of integrating: \n"
        "| \t a. An interface will be of your assistance. \n"
        "| \t b. You will need to enter your functions by pressing buttons. \n"
        "| \t c. Only numbers are to be entered by the keyboard. \n"
        "| \t d. You have to use Reverse Polish Notation! \n"
        "| \t e. You must enter the right amount of operators, otherwise the "
        "program terminates. (Stack Over-/Underflow)\n"
        "| \t f. You must enter spaces between all operands and operators. \n"
        "| \t g. The entry for the integrand must not exceed 100 characters. \n"
        "------------------------------------------------------------------------"
        "----------------------------------------\n\n");
}


/**
 * @brief Displays a menu of available tasks to the user.
 *
 * This function prints a list of tasks that the user can perform, such as
 * numerical integration, listing saved functions, or exiting the program.
 * The user is prompted to select one of the tasks by entering a corresponding number.
 *
 * The menu includes:
 * - Option 1: Perform numerical integration.
 * - Option 2: List the functions that have been saved.
 * - Option 9: Exit the program.
 *
 * It provides clear instructions for interacting with the program's interface.
 */
void print_menu() {
    printf("\nI can do the following tasks for you:\n"
        "\t 1. Numerical integration\n"
        "\t 2. List the functions that have been saved\n"
        "\t 9. Exit\n\n"
        "To execute a task, enter a number chosen from above: ");
}


/**
 * Performs numerical integration by reading configuration from a file and
 * processing the integrand and interval through a graphical user interface.
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of command-line arguments passed to the program.
 * @param filename The path to the file containing the integrand and interval
 *        for integration.
 */
void numerical_integration(int argc, char *argv[], const char *filename) {
    run_gui(&argc, &argv);
    char *integrand;
    char *interval;
    read_file(filename, &integrand, &interval);
    integrate(integrand, interval);
}


/**
 * Reads the content of a file and writes it to the standard output stream.
 *
 * @param filename A pointer to a null-terminated string specifying the path to the file to be read.
 * @return Returns 0 on successful completion. On failure to open the file, it produces an error message via `perror`.
 */
void log_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file.\n");
    } else {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL)
            printf("%s", buffer);
    }

    fclose(file);
}


/**
 * @brief Entry point of the program. Provides a menu interface for numerical integration
 *        and file logging functionality.
 *
 * This function interacts with the user by displaying rules and a menu interface.
 * It allows the user to choose between performing numerical integration, viewing
 * saved functions from a file, or exiting the program. User inputs are processed
 * in a loop until an exit condition is met.
 */
int main(int argc, char *argv[]) {
    print_rules();
    int num;

    do {
        const char *filename = "functions.txt";
        print_menu();
        scanf("%d", &num);
        printf("\n");

        switch (num) {
            case 1:
                numerical_integration(argc, argv, filename);
                break;

            case 2:
                log_file_content(filename);
                break;

            case 9:
                return 0;

            default:
                break;
        }
    } while (num == 1 || num == 2 || num == 9);


    return 0;
}
