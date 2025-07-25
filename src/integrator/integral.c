/**
 * @file integral.c
 * @brief Functions for calculating Riemann sums and Darboux sums for numerical
 * integration.
 *
 * This file contains functions to compute the Riemann sum, lower Darboux sum,
 * and upper Darboux sum of a mathematical expression over a specified interval.
 * It also includes functions to find the infimum and supremum of the expression
 * within that interval.
 */


#include "integral.h"
#include "debugmalloc.h"


/**
 * Calculates the Riemann sum of a mathematical expression over a specified
 * interval.
 *
 * This function computes the Riemann sum by evaluating the expression at
 * discrete points within the interval defined by `start` and `end`, with a step
 * size of `dx`.
 *
 * @param expression A pointer to the `Node` representing the mathematical
 * expression to evaluate. The expression must be parsed and valid before being
 * passed to this function.
 * @param start The starting point of the interval over which the Riemann sum is
 * to be calculated.
 * @param end The ending point of the interval over which the Riemann sum is to
 * be calculated. It is assumed that `end` is greater than or equal to `start`.
 * @param dx The width of each subinterval for the Riemann sum calculation.
 * @return The computed Riemann sum for the given expression over the specified
 * interval.
 */
double calculate_Riemann_sum(Node* expression, const double start,
                             const double end, const double dx) {
    double Riemann_sum = 0;
    double x = start;

    while (x <= end) {
        Riemann_sum += evaluate(expression, x) * dx;
        x += dx;
    }

    return Riemann_sum;
}


/**
 * Finds the infimum (minimum value) of a mathematical expression within a
 * specified interval.
 *
 * @param expr A pointer to the `Node` representing the mathematical expression
 * to evaluate. The expression must be parsed and valid before being passed to
 * this function.
 * @param start The starting point of the interval over which the infimum is to
 * be found.
 * @param end The ending point of the interval over which the infimum is to be
 * found. It is assumed that `end` is greater than or equal to `start`.
 * @param step The step size for incrementing through the interval. Smaller step
 * sizes provide higher accuracy at the cost of additional computation.
 * @return The infimum value of the expression within the interval `[start,
 * end]`. If the interval is not valid or the expression cannot be evaluated,
 * the function exits the program with an error message.
 */
double find_infimum(Node* expr, const double start, const double end,
                    const double step) {
    if (expr == NULL) {
        printf("Error parsing expression.\n");
        exit(1);
    }

    double x = start;
    double infimum = evaluate(expr, x);

    while (x <= end) {
        double value = evaluate(expr, x);
        if (value < infimum)
            infimum = value;
        x += step;
    }

    return infimum;
}


/**
 * Calculates the lower Darboux sum of a mathematical expression over a
 * specified interval.
 *
 * This function computes the lower Darboux sum by evaluating the infimum of the
 * expression at discrete points within the interval defined by `start` and
 * `end`, with a subinterval width of `dx`.
 *
 * @param expression A pointer to the `Node` representing the mathematical
 * expression to evaluate. The expression must be parsed and valid before being
 * passed to this function.
 * @param start The starting point of the interval over which the lower Darboux
 * sum is to be calculated.
 * @param end The ending point of the interval over which the lower Darboux sum
 * is to be calculated. It is assumed that `end` is greater than or equal to
 * `start`.
 * @param dx The width of each subinterval for the lower Darboux sum
 * calculation.
 * @param step The step size for evaluating the infimum. Smaller step sizes
 * provide higher accuracy.
 * @return The computed lower Darboux sum for the given expression over the
 * specified interval.
 */
double calculate_lower_Darboux_sum(Node* expression, const double start,
                                   const double end, const double dx,
                                   const double step) {
    double lower_Darboux_sum = 0;
    double x = start;

    while (x <= end) {
        lower_Darboux_sum += find_infimum(expression, x, x + dx, step) * dx;
        x += dx;
    }

    return lower_Darboux_sum;
}


/**
 * Finds the supremum (maximum value) of a mathematical expression within a
 * specified interval.
 *
 * @param expr A pointer to the `Node` representing the mathematical expression
 * to evaluate. The expression must be parsed and valid before being passed to
 * this function.
 * @param start The starting point of the interval over which the supremum is to
 * be found.
 * @param end The ending point of the interval over which the supremum is to be
 * found. It is assumed that `end` is greater than or equal to `start`.
 * @param step The step size for incrementing through the interval. Smaller step
 * sizes provide higher accuracy at the cost of additional computation.
 * @return The supremum value of the expression within the interval `[start,
 * end]`. If the interval is not valid or the expression cannot be evaluated,
 * the function exits the program with an error message.
 */
double find_supremum(Node* expr, const double start, const double end,
                     const double step) {
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


/**
 * Calculates the upper Darboux sum of a mathematical expression over a
 * specified interval.
 *
 * This function computes the upper Darboux sum by evaluating the supremum of
 * the expression at discrete points within the interval defined by `start` and
 * `end`, with a subinterval width of `dx`.
 *
 * @param expression A pointer to the `Node` representing the mathematical
 * expression to evaluate. The expression must be parsed and valid before being
 * passed to this function.
 * @param start The starting point of the interval over which the upper Darboux
 * sum is to be calculated.
 * @param end The ending point of the interval over which the upper Darboux sum
 * is to be calculated. It is assumed that `end` is greater than or equal to
 * `start`.
 * @param dx The width of each subinterval for the upper Darboux sum
 * calculation.
 * @param step The step size for evaluating the supremum. Smaller step sizes
 * provide higher accuracy.
 * @return The computed upper Darboux sum for the given expression over the
 * specified interval.
 */
double calculate_upper_Darboux_sum(Node* expression, const double start,
                                   const double end, const double dx,
                                   const double step) {
    double upper_Darboux_sum = 0;
    double x = start;

    while (x <= end) {
        upper_Darboux_sum += find_supremum(expression, x, x + dx, step) * dx;
        x += dx;
    }

    return upper_Darboux_sum;
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
void integrate(char* integrand, char* interval) {
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

    // The number of subintervals for the partitioning of the interval
    const int refinement = get_partition_refinement();
    if (refinement == -1) {
        free_resources(integrand, interval, nullptr);
        return;
    }

    Node* expression = parse(integrand);
    if (!expression) {
        perror("Error parsing expression.\n");
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

    // Size of each subinterval
    const double dx = (end - start) / refinement;

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);
    const double Riemann_sum =
        calculate_Riemann_sum(expression, start, end, dx);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);
    const double time_of_Riemann = timespec_diff_ms(&start_time, &end_time);

    constexpr double step = 1E-05; // The step size for evaluating the extremum

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);
    const double lower_Darboux_sum =
        calculate_lower_Darboux_sum(expression, start, end, dx, step);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);
    const double time_of_lower_Darboux =
        timespec_diff_ms(&start_time, &end_time);

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);
    const double upper_Darboux_sum =
        calculate_upper_Darboux_sum(expression, start, end, dx, step);
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);
    const double time_of_upper_Darboux =
        timespec_diff_ms(&start_time, &end_time);

    double time_spent[3] = {time_of_Riemann, time_of_lower_Darboux,
                            time_of_upper_Darboux};

    log_integral_values(minus, Riemann_sum, lower_Darboux_sum,
                        upper_Darboux_sum, time_spent);
    free_resources(integrand, interval, expression);
}
