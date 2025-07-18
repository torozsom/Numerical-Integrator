/**
 * @file integral.c
 * @brief Implementation of numerical integration functions.
 *
 * This file contains functions to perform numerical integration of mathematical expressions
 * over specified intervals. It includes validation of input, parsing of expressions, and
 * computation of integrals using the supremum method.
 */


#include "integral.h"
#include "debugmalloc.h"


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
 * @brief Prompts the user to enter the number of iterations for a calculation and validates the input.
 *
 * This function asks the user for an integer value representing the number of iterations, ensuring it falls
 * within the defined range [MIN_ITERATIONS, MAX_ITERATIONS]. If the input is out of range, an error message
 * is displayed, and the function returns -1. Otherwise, the valid number of iterations is returned.
 *
 * @return The number of iterations entered by the user, or -1 if the input is invalid.
 */
int get_iteration_count() {
    int iterations;
    printf("Enter the number of iterations (x in [%d ; %d]): ", MIN_ITERATIONS, MAX_ITERATIONS);
    scanf("%d", &iterations);

    if (iterations < MIN_ITERATIONS || iterations > MAX_ITERATIONS) {
        printf("Error: The number of iterations must be between %d and %d.\n", MIN_ITERATIONS, MAX_ITERATIONS);
        return -1;
    }

    return iterations;
}


/**
 * @brief Computes the numerical integral of a given mathematical expression.
 *
 * This function performs numerical integration for a given mathematical
 * expression (`integrand`) over a specified interval (`interval`). It
 * validates the input, interprets the function, and calculates the
 * integral using numerical methods. If the input is invalid or any errors
 * occur during computation, the function will free the associated resources
 * and terminate gracefully.
 *
 * The function allows integration over intervals, and handles cases where the
 * start of the interval is greater than the end by adjusting the interval and
 * returning the negated result as needed.
 *
 * @param integrand A string representing the mathematical function to be
 *                  integrated. The function is expected to be a valid
 *                  mathematical expression.
 * @param interval A string representing the interval over which the integral
 *                 is to be computed, formatted as "[start ; end]".
 */
void integrate(char *integrand, char *interval) {
    remove_spaces(integrand);

    if (!validate_integrand(integrand)) {
        free_resources(integrand, interval, nullptr);
        return;
    }

    double start, end;

    if (!validate_interval(interval, &start, &end)) {
        free_resources(integrand, interval, nullptr);
        return;
    }

    bool minus = false;
    if (start > end) {
        const double temp = start;
        start = end;
        end = temp;
        minus = true;
    }

    const int iterations = get_iteration_count();
    if (iterations == -1) {
        free_resources(integrand, interval, nullptr);
        return;
    }

    const double subinterval_size = (end - start) / iterations;
    constexpr double step = 10e-7;
    double integral = 0;

    Node *expression = parse(integrand);
    if (!expression) {
        perror("Error parsing expression.\n");
        free_resources(integrand, interval, nullptr);
        return;
    }

    for (double x = start; x < end; x += subinterval_size)
        integral += subinterval_size * find_supremum(expression, x, x + subinterval_size, step);


    printf("Integral = %.4f\n\n", minus ? -integral : integral);
    free_resources(integrand, interval, expression);
}


/**
 * Finds the supremum (maximum value) of a mathematical expression within a specified interval.
 *
 * @param expr A pointer to the `Node` representing the mathematical expression to evaluate.
 *             The expression must be parsed and valid before being passed to this function.
 * @param start The starting point of the interval over which the supremum is to be found.
 * @param end The ending point of the interval over which the supremum is to be found.
 *            It is assumed that `end` is greater than or equal to `start`.
 * @param step The step size for incrementing through the interval. Smaller step sizes
 *             provide higher accuracy at the cost of additional computation.
 * @return The supremum value of the expression within the interval `[start, end]`. If the
 *         interval is not valid or the expression cannot be evaluated, the function
 *         exits the program with an error message.
 */
double find_supremum(Node *expr, const double start, const double end, const double step) {
    if (expr == NULL) {
        printf("Error parsing expression.\n");
        exit(1);
    }

    double x = start;
    double supremum = evaluate(expr, x);

    while (x <= end) {
        double value = evaluate(expr, x);
        if (value > supremum)
            supremum = value;
        x += step;
    }

    return supremum;
}
