#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "expression_parser.h"

#define INITIAL_SIZE 256

void read_file(const char *filename, char **last, char **second_last);
void remove_spaces(char *str);
double find_supremum(Node* expr, double start, double end, double step);

#endif /*INTEGRAL_H*/