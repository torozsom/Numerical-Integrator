/**
 * @file controls.c
 * @brief Contains functions for validating integrands and intervals, managing user input,
 *        and handling memory for numerical integration tasks.
 *
 * This file provides functionality to validate mathematical expressions, manage user input,
 * and perform numerical integration tasks. It includes functions for validating integrands,
 * intervals, and partition refinements, as well as memory management for dynamically allocated resources.
 */


#include "controls.h"
#include "debugmalloc.h"


/**
 * Validates the given integrand to ensure it meets the maximum allowed length constraint.
 *
 * @param integrand A constant character pointer representing the mathematical integrand to be validated.
 * @return true if the integrand length is within the allowed limit defined by MAX_INTEGRAND_LENGTH,
 *         false otherwise.
 */
bool validate_integrand(const char *integrand) {
    if (strlen(integrand) > MAX_INTEGRAND_LENGTH) {
        printf("The integrand is too long.\n");
        return false;
    }
    return true;
}


/**
 * Validates a given interval string and extracts the start and end points.
 *
 * This function checks whether the interval string is properly defined and parses
 * the interval into numerical start and end points. If the start and end points
 * are equal, it considers the interval invalid for integration.
 *
 * @param interval The interval string in the format "[start ; end]". It should contain
 *                 numerical values for start and end separated by a semicolon.
 * @param start Pointer to a double where the parsed start value will be stored.
 * @param end Pointer to a double where the parsed end value will be stored.
 * @return Returns true if the interval is valid; otherwise, returns false.
 */
bool validate_interval(const char *interval, double *start, double *end) {
    if (strcmp(interval, "[ ; ]") == 0) {
        printf("The interval is not defined.\n");
        return false;
    }

    sscanf(interval, "[%lf ; %lf]", start, end);

    if (*start == *end) {
        printf("Integrating in a [c; c] interval is defined to be equal to 0.\n");
        return false;
    }

    return true;
}


/**
 * @brief Prompts the user to enter the scale of refinement for a calculation and validates the input.
 *
 * This function asks the user for an integer value representing the number of subintervals within the
 * given interval of integration while ensuring it falls within the defined range [MIN_REFINEMENT, MAX_REFINEMENT].
 * If the input is out of range, an error message is displayed, and the function returns -1.
 * Otherwise, the valid number of subintervals is returned.
 *
 * @return The number of iterations entered by the user, or -1 if the input is invalid.
 */
int get_partition_refinement() {
    int iterations;
    printf("Enter the scale of refinement (x in [%d ; %d]): ", MIN_REFINEMENT, MAX_REFINEMENT);
    scanf("%d", &iterations);

    if (iterations < MIN_REFINEMENT || iterations > MAX_REFINEMENT) {
        printf("Error: The scale of refinement must be between %d and %d.\n", MIN_REFINEMENT, MAX_REFINEMENT);
        return -1;
    }

    return iterations;
}


/**
 * @brief Prints a signed value to the standard output.
 *
 * This function formats the output of a double value, allowing for
 * the possibility of negating the value based on the `minus` flag.
 *
 * @param minus A boolean flag indicating whether to negate the value.
 * @param value The double value to be printed.
 */
void print_signed_value(const bool minus, const double value) {
    printf("%.6f\n", minus ? -value : value);
}


/**
 * Logs the computed integral values to the standard output.
 *
 * This function prints the Riemann sum, lower Darboux sum, upper Darboux sum,
 * the difference between the upper and lower sums, and the average of the two
 * approximations. If the `minus` flag is set, it negates the output values.
 *
 * @param minus A boolean flag indicating whether to negate the output values.
 * @param Riemann_sum The computed Riemann sum of the integral.
 * @param lower_Darboux_sum The computed lower Darboux sum of the integral.
 * @param upper_Darboux_sum The computed upper Darboux sum of the integral.
 */
void log_integral_values(const bool minus, const double Riemann_sum, const double lower_Darboux_sum,
                         const double upper_Darboux_sum) {
    printf("Riemann-sum = ");
    print_signed_value(minus, Riemann_sum);
    printf("Lower Darboux-sum = ");
    print_signed_value(minus, lower_Darboux_sum);
    printf("Upper Darboux-sum = ");
    print_signed_value(minus, upper_Darboux_sum);
    printf("\n");

    const double Darboux_difference = fabs(upper_Darboux_sum - lower_Darboux_sum);
    printf("Difference between Darboux-sums = %.6f\n", Darboux_difference);

    const double average = (upper_Darboux_sum + lower_Darboux_sum) / 2;
    printf("Average of the Darboux-sums = %.6f\n\n", minus ? -average : average);

    const double difference = fabs(average - Riemann_sum);
    printf("Difference between Riemann-sum and average of the Darboux-sums = %.6f\n\n", difference);
}


/**
 * Recursively deallocates memory associated with nodes of a binary tree.
 * This function traverses the binary tree in a post-order manner,
 * freeing memory for each left subtree, right subtree, and finally the parent node.
 *
 * @param node Pointer to the root node of the binary tree to be freed.
 */
void free_tree(Node *node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
        node = nullptr;
    }
}


/**
 * Frees allocated memory for the given resources.
 *
 * @param integrand Pointer to the integrand string to be freed. Can be NULL.
 * @param interval Pointer to the interval string to be freed. Can be NULL.
 * @param expression Pointer to the root node of the parsed expression tree to be freed. Can be NULL.
 */
void free_resources(char *integrand, char *interval, Node *expression) {
    if (integrand)
        free(integrand);
    if (interval)
        free(interval);
    if (expression)
        free_tree(expression);
}


/**
 * Reads the last two lines of a file and stores them in the provided pointers.
 * Memory for the lines is dynamically allocated and must be freed by the caller.
 *
 * @param filename Name of the file to read from.
 * @param last Pointer to a char pointer where the last line of the file will be stored.
 * @param second_last Pointer to a char pointer where the second-to-last line of the file will be stored.
 */
void read_last_two_lines(const char *filename, char **last, char **second_last) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *last_line = nullptr;
    char *second_last_line = nullptr;
    int size = INITIAL_SIZE;

    last_line = (char *) malloc(size * sizeof(char)+1);
    second_last_line = (char *) malloc(size * sizeof(char)+1);

    if (last_line == NULL || second_last_line == NULL) {
        perror("Did not manage to allocate memory");
        return;
    }

    last_line[0] = '\0';
    second_last_line[0] = '\0';

    while (fgets(last_line, size, file) != NULL) {
        if (last_line[strlen(last_line) - 1] == '\n') {
            char *temp = last_line;
            last_line = second_last_line;
            second_last_line = temp;
        } else {
            size *= 2;
            last_line = (char *) realloc(last_line, size * sizeof(char));
            second_last_line = (char *) realloc(second_last_line, size * sizeof(char));

            if (last_line == NULL || second_last_line == NULL) {
                perror("Did not manage to allocate memory");
                return;
            }
        }
    }

    *last = last_line;
    *second_last = second_last_line;

    fclose(file);
}


/**
 * @brief Removes leading and trailing spaces from a given string and compresses the string.
 *        The trimmed string is stored in the same memory location as the input string.
 *
 * @param str The input string from which spaces are to be removed.
 *            After execution, the string will no longer contain leading or trailing spaces.
 */
void remove_spaces(char *str) {
    size_t start = 0;
    size_t end = strlen(str) - 1;

    while (isspace(str[start]))
        start++;

    while (end > start && isspace(str[end]))
        end--;

    size_t i, j;
    for (i = start, j = 0; i <= end; i++, j++)
        str[j] = str[i];
    str[j] = '\0';
}


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
        "\t 2. Integrate the last saved function\n"
        "\t 3. List the functions that have been saved\n"
        "\t Other: Exit\n\n"
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
    char *integrand, *interval;
    read_last_two_lines(filename, &integrand, &interval);
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
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
        printf("%s", buffer);

    fclose(file);
}


/**
 * Integrates the last saved function from a file by reading the integrand and interval,
 * and then performing the integration.
 *
 * @param filename The path to the file containing the last saved integrand and interval.
 */
void integrate_last(const char *filename) {
    char *integrand, *interval;
    read_last_two_lines(filename, &integrand, &interval);
    printf("Function to integrate: %s", integrand);
    printf("Interval: %s\n", interval);
    integrate(integrand, interval);
}