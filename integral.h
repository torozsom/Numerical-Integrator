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
#include "gui.h"

#define INITIAL_SIZE 256
#define MAX_INTEGRAND_LENGTH 100
#define MIN_ITERATIONS 1
#define MAX_ITERATIONS 1000000


void free_resources(char *integrand, char *interval, Node *expression);

bool validate_integrand(const char *integrand);

bool validate_interval(const char *interval, double *start, double *end);

int get_iteration_count();

void integrate(char *integrand, char *interval);

double find_supremum(Node* expr, double start, double end, double step);


#endif /*INTEGRAL_H*/
