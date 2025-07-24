# Numerical Integration Module

A sophisticated implementation of numerical integration methods using Riemann sums and Darboux integrals. This module is
part of the Numerical-Integrator project and provides accurate numerical approximations of definite integrals.

## Table of Contents

- [Overview](#overview)
- [Integration Methods](#integration-methods)
- [Algorithm Implementation](#algorithm-implementation)
- [Input Validation](#input-validation)
- [Error Handling](#error-handling)
- [Performance Considerations](#performance-considerations)
- [Dependencies](#dependencies)
- [Function Reference](#function-reference)

## Overview

The integrator module implements three different approaches to numerical integration:

1. Riemann Sum
2. Lower Darboux Sum
3. Upper Darboux Sum

These methods provide different approximations of the definite integral, allowing for error estimation and accuracy
assessment.

### Key Features

- Support for arbitrary mathematical expressions via expression parser
- Configurable integration precision through refinement levels
- Automatic interval direction handling (supports reverse intervals)
- Comprehensive error bounds calculation using Darboux sums
- Memory-safe implementation with proper resource cleanup
- Interactive refinement level selection

## Integration Methods

### Riemann Sum

$$\int_a^b f(x)dx \approx \sum_{i=1}^{n} f(x_i)\Delta x$$

The Riemann sum approximates the integral by sampling the function at any given 
point within the subinterval, so we use the left endpoint of each one.

### Darboux Sums

$$\text{Lower Sum: } L(f,P) = \sum_{i=1}^{n} m_i \cdot \Delta x$$

$$\text{Upper Sum: } U(f,P) = \sum_{i=1}^{n} M_i \cdot \Delta x$$

Where:


- `mi` is the infimum (minimum) of f(x) on subinterval i
- `Mi` is the supremum (maximum) of f(x) on subinterval i
- `Δx` is the width of each subinterval

The true integral value lies between the lower and upper Darboux sums, providing error bounds.

## Algorithm Implementation

### 1. Integration Process Flow

```
Input → Validation → Parsing → Computation → Result Analysis → Resource Cleanup
```

### 2. Key Steps

1. **Input Processing**
   - Remove spaces from integrand expression
   - Validate integrand expression syntax and length
   - Parse integration interval in `[start ; end]` format
   - Get user-specified refinement level

2. **Expression Parsing**
   - Parse mathematical expression into AST (Abstract Syntax Tree)
   - Validate expression structure

3. **Interval Handling**
   - Handle reverse intervals (start > end) by swapping and negating result
   - Calculate subinterval width: `dx = (end - start) / refinement`

4. **Computation**
   ```
   For each subinterval [xi, xi+1]:
   ├── Calculate Riemann sum
   │   └── Evaluate f(xi)∙Δx (left endpoint)
   ├── Calculate Lower Darboux sum
   │   ├── Find infimum in [xi, xi+1] with step size 1E-05
   │   └── Multiply by Δx
   └── Calculate Upper Darboux sum
       ├── Find supremum in [xi, xi+1] with step size 1E-05
       └── Multiply by Δx
   ```

5. **Result Analysis**
   - Log integral values with proper sign handling
   - Present comprehensive results including error bounds
   - Calculate average approximation from Darboux bounds

## Input Validation

### 1. Integrand Validation

- Maximum length check (`MAX_INTEGRAND_LENGTH = 100`)
- Expression syntax verification through parser
- Memory allocation validation
- Space removal preprocessing

### 2. Interval Validation

```c
[start ; end] format where:
├── start and end are numerical values
├── Proper bracket and semicolon syntax
├── Automatic handling of reverse intervals (start > end)
└── Result negation for reverse intervals
```

### 3. Refinement Parameters

```c
MIN_REFINEMENT (1) ≤ refinement ≤ MAX_REFINEMENT (20,000,000)
```

Interactive user input validation for refinement level selection.

## Error Handling

The module implements comprehensive error handling:

1. **Input Errors**
   - Invalid expression syntax (exits gracefully)
   - Malformed intervals
   - Out-of-range refinement values
   - Null expression pointers

2. **Computation Errors**
   - Memory allocation failures
   - Expression parsing errors (`perror` messages)
   - Null expression tree handling

3. **Resource Management**
   ```c
   integrate() function ensures:
   ├── Proper cleanup on early exits
   ├── Expression tree deallocation
   ├── Input string cleanup
   └── Consistent resource freeing via free_resources()
   ```

## Performance Considerations

### 1. Memory Management

- Dynamic allocation for expression trees
- Efficient resource cleanup via `free_resources()`
- Prevention of memory leaks with `debugmalloc.h`

### 2. Computation Optimization

- Configurable precision levels (1 to 20M refinements)
- Fixed step size for extremum finding (1E-05)
- Efficient subinterval calculations
- Balanced accuracy vs. performance trade-offs

### 3. Accuracy Control

```
Refinement Levels: 1 to 20,000,000 subintervals
Extremum Step Size: 1E-05 (fixed)
Error Bounds: |Upper - Lower| Darboux sums
```

## Dependencies

The module depends on several other components:

- `expression_parser.h` - For parsing mathematical expressions into AST
- `controls.h` - For input validation and user interface functions
- `debugmalloc.h` - For memory debugging and leak detection

### Required Functions from Dependencies

- `evaluate(Node* expr, double x)` - Evaluates expression at given x value
- `parse(char* expression)` - Parses string into expression tree
- `validate_integrand()` - Validates integrand syntax
- `validate_interval()` - Validates interval format
- `get_partition_refinement()` - Gets user refinement input
- `log_integral_values()` - Outputs integration results
- `free_resources()` - Cleans up allocated resources

## Function Reference

### Core Integration Functions

#### `calculate_Riemann_sum(Node* expression, double start, double end, double dx)`
Computes Riemann sum using left endpoint evaluation.

#### `calculate_lower_Darboux_sum(Node* expression, double start, double end, double dx, double step)`
Computes lower Darboux sum by finding infimum in each subinterval.

#### `calculate_upper_Darboux_sum(Node* expression, double start, double end, double dx, double step)`
Computes upper Darboux sum by finding supremum in each subinterval.

### Utility Functions

#### `find_infimum(Node* expr, double start, double end, double step)`
Finds minimum value of expression in given interval.

#### `find_supremum(Node* expr, double start, double end, double step)`
Finds maximum value of expression in given interval.

### Main Interface

#### `integrate(char* integrand, char* interval)`
Main integration function that orchestrates the entire process from input validation to result output.

## Usage Example

```c
// Define the integral
char *integrand = "x sin x *";   // sin(x) * x (in RNP)
char *interval = "[0 ; 3.14]";

// Compute the integral (user will be prompted for refinement)
integrate(integrand, interval);

// Output includes:
// - Riemann sum approximation
// - Lower Darboux sum 
// - Upper Darboux sum 
// - Proper handling of interval direction
// - Average approximation and error estimate
```

The output provides comprehensive information about the integral approximation, including multiple methods and rigorous error bounds through Darboux sum analysis.
