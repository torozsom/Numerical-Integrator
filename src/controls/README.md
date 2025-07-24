# Controls Module

A central coordination module for the Numerical Integration Calculator that handles input validation, resource management, file operations, and integration workflow. This module bridges the user interface, expression parser, and integration engine, ensuring robust operation of the application.

## Table of Contents

- [Overview](#overview)
- [Core Responsibilities](#core-responsibilities)
- [Module Architecture](#module-architecture)
- [Validation System](#validation-system)
- [Resource Management](#resource-management)
- [File Operations](#file-operations)
- [User Interface](#user-interface)
- [Integration Workflow](#integration-workflow)
- [Function Reference](#function-reference)
- [Error Handling](#error-handling)
- [Usage Examples](#usage-examples)

## Overview

The Controls module serves as the backbone of the Numerical Integration Calculator, orchestrating operations between different components of the system. It provides functions for validating user inputs, managing system resources, performing file operations, and controlling the integration workflow.

This module ensures that all inputs meet required specifications before passing them to the integration engine, and handles proper resource allocation and deallocation to prevent memory leaks.

## Core Responsibilities

### Input Validation
- Validates mathematical expressions (integrands)
- Verifies integration intervals for proper formatting and validity
- Confirms partition refinement parameters are within acceptable bounds

### Resource Management
- Allocates memory for expressions and intervals
- Ensures proper deallocation of all resources
- Manages expression tree memory through recursive traversal

### User Interaction
- Displays program rules and guidelines
- Presents menu options for different operations
- Formats and displays integration results

### File Operations
- Reads mathematical expressions and intervals from files
- Extracts the last entries for integration operations
- Logs function outputs to console with proper formatting

## Module Architecture

The Controls module is structured around four main functional areas:

### 1. Validation Functions
Responsible for ensuring all inputs meet required specifications:
```
validate_integrand() → validate_interval() → get_partition_refinement()
```

### 2. Resource Management Functions
Handle memory allocation and deallocation:
```
free_tree() → free_resources()
```

### 3. User Interface Functions
Manage interaction with the user:
```
print_rules() → print_menu() → log_integral_values()
```

### 4. File Operations
Handle reading from and writing to files:
```
log_file_content() → read_last_two_lines() → remove_spaces()
```

### 5. Workflow Control Functions
Orchestrate the integration process:
```
numerical_integration() → integrate_last()
```

## Validation System

### Expression Validation

```c
bool validate_integrand(const char *integrand)
```

The function checks if:
- Expression length does not exceed `MAX_INTEGRAND_LENGTH` (100 characters)
- Returns true if valid, false otherwise

### Interval Validation

```c
bool validate_interval(const char *interval, double *start, double *end)
```

The function verifies:
- Interval is properly formatted as `[start ; end]`
- Interval bounds are valid numerical values
- Start and end points are not equal (which would result in zero integral)
- Parses and extracts start and end values into provided pointers

### Partition Refinement Validation

```c
int get_partition_refinement()
```

This function:
- Prompts user for refinement level (number of subintervals)
- Validates input is within range `[MIN_REFINEMENT, MAX_REFINEMENT]`
- Returns the validated refinement level or -1 if invalid

## Resource Management

### Tree Deallocation

```c
void free_tree(Node *node)
```

Recursively frees memory allocated for expression tree:
- Uses post-order traversal (left subtree → right subtree → node)
- Handles null pointers safely
- Sets freed pointers to null

### Comprehensive Resource Cleanup

```c
void free_resources(char *integrand, char *interval, Node *expression)
```

Cleans up all allocated resources:
- Safely frees integrand string if non-null
- Safely frees interval string if non-null
- Recursively frees expression tree if non-null

## File Operations

### Reading Last Entries

```c
void read_last_two_lines(const char *filename, char **last, char **second_last)
```

This function:
- Opens specified file for reading
- Dynamically allocates memory for result strings
- Reads file line by line, keeping track of last two lines
- Handles variable-length lines through dynamic reallocation
- Stores results in provided pointers

### Content Logging

```c
void log_file_content(const char *filename)
```

Displays the entire content of a file:
- Opens file in read mode
- Reads and prints content in blocks of up to 1024 bytes
- Handles file opening errors gracefully

### String Processing

```c
void remove_spaces(char *str)
```

Removes extraneous spaces from strings:
- Trims leading and trailing whitespace
- Modifies string in-place
- Preserves internal spacing structure

## User Interface

### Program Information

```c
void print_rules()
```

Displays usage guidelines including:
- Interface instructions
- Input format requirements (RPN notation)
- Spacing requirements
- Length constraints

### Menu System

```c
void print_menu()
```

Presents available program options:
- Numerical integration
- Processing last saved function
- Listing saved functions
- Exit option

### Result Presentation

```c
void log_integral_values(bool minus, double Riemann_sum, double lower_Darboux_sum, double upper_Darboux_sum)
```

Formatted display of integration results:
- Shows Riemann sum approximation
- Shows lower and upper Darboux sum bounds
- Calculates and displays difference between bounds
- Presents average approximation
- Handles sign correction for reverse intervals

## Integration Workflow

### Standard Integration

```c
void numerical_integration(int argc, char *argv[], const char *filename)
```

Orchestrates the complete integration process:
1. Launches GUI for user input
2. Reads resulting expressions from file
3. Initiates integration process

### Last Function Integration

```c
void integrate_last(const char *filename)
```

Processes the most recently saved function:
1. Reads last two lines from specified file
2. Displays the function and interval to be integrated
3. Initiates integration process

## Function Reference

### Validation Functions

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `validate_integrand()` | Checks if integrand is valid | `const char *integrand` | `bool` success |
| `validate_interval()` | Validates integration interval | `const char *interval`, `double *start`, `double *end` | `bool` success |
| `get_partition_refinement()` | Gets and validates refinement level | None | `int` refinement level |

### Resource Management Functions

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `free_tree()` | Recursively frees expression tree | `Node *node` | `void` |
| `free_resources()` | Frees all allocated resources | `char *integrand`, `char *interval`, `Node *expression` | `void` |

### Output Functions

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `print_signed_value()` | Displays signed numeric value | `bool minus`, `double value` | `void` |
| `log_integral_values()` | Displays integration results | `bool minus`, `double Riemann_sum`, `double lower_Darboux_sum`, `double upper_Darboux_sum` | `void` |
| `print_rules()` | Shows program usage rules | None | `void` |
| `print_menu()` | Displays program menu | None | `void` |

### File Operations Functions

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `log_file_content()` | Displays file contents | `const char *filename` | `void` |
| `read_last_two_lines()` | Extracts last two lines from file | `const char *filename`, `char **last`, `char **second_last` | `void` |
| `remove_spaces()` | Removes spaces from string | `char *str` | `void` |

### Integration Functions

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `numerical_integration()` | Runs complete integration process | `int argc`, `char *argv[]`, `const char *filename` | `void` |
| `integrate_last()` | Integrates last saved function | `const char *filename` | `void` |

## Error Handling

### Validation Errors
- Invalid integrand length: Displays error message and returns false
- Invalid interval format: Returns false with specific error message
- Equal interval bounds: Informs user that integral is zero by definition
- Invalid refinement level: Returns -1 with descriptive error message

### File Operation Errors
- File opening failures: Uses `perror()` to display system error message
- Memory allocation failures: Reports allocation errors with `perror()`

### Resource Management
- Null pointer protection: All memory functions check for null before freeing
- Safe pointer handling: Freed pointers are set to null when appropriate

## Usage Examples

### Complete Integration Workflow

```c
// Launch the GUI and perform integration
const char *filename = "functions.txt";
numerical_integration(argc, argv, filename);
```

### Process Last Function

```c
// Integrate the last function saved in the file
const char *filename = "functions.txt";
integrate_last(filename);
```

### Display Saved Functions

```c
// Show all functions saved in the file
const char *filename = "functions.txt";
log_file_content(filename);
```

### Manual Integration Process

```c
// Manually validate and process an integrand and interval
char *integrand = "x x * 1 +";
char *interval = "[0 ; 5]";
double start, end;

if (validate_integrand(integrand) && validate_interval(interval, &start, &end)) {
    Node *expression = parse(integrand);
    // Perform integration calculations...
    free_resources(integrand, interval, expression);
}
```

### Resource Management Example

```c
// Proper resource handling pattern
char *integrand = strdup("x sin");
char *interval = strdup("[0 ; 3.14]");
Node *expression = parse(integrand);

// Process the expression...

// Clean up all resources
free_resources(integrand, interval, expression);
```

The Controls module ensures that all components of the Numerical Integration Calculator work together seamlessly, providing robust input validation, efficient resource management, and a user-friendly interface for mathematical operations.