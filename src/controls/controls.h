/**
 * @file controls.h
 * @brief Header file for the controls module, which includes function
 * declarations for validating input, performing numerical integration, and
 * managing resources.
 *
 * This module is part of a numerical integration program that allows users to
 * compute integrals using various methods and manage input/output operations.
 */


#ifndef CONTROLS_H
#define CONTROLS_H


#include "expression_parser.h"
#include "gui.h"
#include "integral.h"


#define INITIAL_SIZE 256


// Used for the integrator module:

double timespec_diff_ms(const struct timespec* start,
                        const struct timespec* end);

bool validate_integrand(const char* integrand);

bool validate_interval(const char* interval, double* start, double* end);

int get_partition_refinement();

void print_signed_value(bool minus, double value);

void log_integral_values(bool minus, double Riemann_sum,
                         double lower_Darboux_sum, double upper_Darboux_sum,
                         const double* times_elapsed);


// Resource memory deallocation:

void free_tree(Node* node);

void free_resources(char* integrand, char* interval, Node* expression);


// Used for the main program:

void print_rules();

void print_menu();

void numerical_integration(int argc, char* argv[], const char* filename);

void integrate_last(const char* filename);


// File and string operations:

void log_file_content(const char* filename);

void read_last_two_lines(const char* filename, char** last, char** second_last);

void remove_spaces(char* str);


#endif /* CONTROLS_H */
