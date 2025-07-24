/**
 * @file integral.h
 * @brief Header file for integral calculation functions.
 *
 * This file contains declarations for functions that compute Riemann sums,
 * Darboux sums, and perform integration based on user input.
 */


#ifndef INTEGRAL_H
#define INTEGRAL_H


#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <float.h>

#include "expression_parser.h"
#include "controls.h"


#define INITIAL_SIZE 256
#define MAX_INTEGRAND_LENGTH 100
#define MIN_REFINEMENT 1
#define MAX_REFINEMENT 20000000


double calculate_Riemann_sum(Node* expression, double start, double end, double dx);

double find_infimum(Node* expr, double start, double end, double step);

double calculate_lower_Darboux_sum(Node* expression, double start, double end, double dx, double step);

double find_supremum(Node* expr, double start, double end, double step);

double calculate_upper_Darboux_sum(Node* expression, double start, double end, double dx, double step);

void integrate(char *integrand, char *interval);


#endif /*INTEGRAL_H*/
