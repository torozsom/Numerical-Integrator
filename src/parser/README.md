# Mathematical Expression Parser Module

A robust implementation of a mathematical expression parser and evaluator that supports variables, functions, and
operators. This module is part of the Numerical-Integrator project and handles the parsing and evaluation of
mathematical expressions in Reverse Polish Notation (RPN).

## Table of Contents

- [Overview](#overview)
- [Supported Features](#supported-features)
- [Data Structures](#data-structures)
- [Control Flow](#control-flow)
- [Expression Evaluation](#expression-evaluation)
- [Memory Management](#memory-management)
- [Function Reference](#function-reference)
- [Error Handling](#error-handling)
- [Usage Examples](#usage-examples)

## Overview

The parser is designed to handle mathematical expressions in RPN format, where operators follow their operands. For
example, the expression `2 * x + 1` would be written as `2 x * 1 +` in RPN.

The parser creates an Abstract Syntax Tree (AST) from the input expression and provides efficient evaluation for any
given variable value.

## Supported Features

### Arithmetic Operations

- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`)
- Exponentiation (`^`)

### Mathematical Functions

- `sin` - Sine (radians)
- `cos` - Cosine (radians)
- `tg` - Tangent (radians)
- `ctg` - Cotangent (radians)
- `ln` - Natural logarithm
- `exp` - Exponential function (e^x)

### Data Types

- Variables (single character, typically 'x')
- Real numbers (floating-point values)
- Functions with single argument

## Data Structures

The parser uses several interconnected data structures to represent and manipulate expressions:

### 1. Abstract Syntax Tree (AST)

The expression is internally represented as a binary tree where:

- Each node contains a type identifier and corresponding data
- Leaf nodes represent variables or numbers
- Internal nodes represent operators or functions
- Functions are unary (single left child for argument)
- Operators are binary (left and right children for operands)

```
Example: 2 x * 1 +
    (+)
   /   \
  (*)   (1)
 /   \
(2)   (x)
```

### 2. Node Types

Each node in the AST can be one of four types:

- `NODE_VARIABLE`: Represents a variable (single character)
- `NODE_NUMBER`: Represents a numeric constant (double precision)
- `NODE_FUNCTION`: Represents a mathematical function (unary)
- `NODE_OPERATOR`: Represents an arithmetic operator (binary)

### 3. Node Structure

```c
typedef struct Node {
    NodeType type;        // Type identifier
    NodeData data;        // Union of possible data types
    struct Node *left;    // Left child (or function argument)
    struct Node *right;   // Right child (operators only)
} Node;
```

### 4. Data Storage

Each node type stores different information:

```c
typedef union NodeData {
    Variable variable;    // Contains: char name
    Number number;        // Contains: double value
    Function function;    // Contains: char name[10], Func pointer
    Operator operator;    // Contains: char symbol
} NodeData;
```

### 5. Parser Stack

A stack data structure (`NodeStack`) is used during parsing:

- Fixed size: `STACK_SIZE = 50`
- Stores `Node*` pointers during AST construction
- Implements stack overflow/underflow protection

## Control Flow

The parsing process follows these steps:

### 1. Tokenization

- Input string is split into tokens using `strtok()` with space delimiter
- Each token is processed sequentially in RPN order

### 2. Token Classification and Processing

```
For each token:
├── If token equals "x"
│   └── Create variable node and push to stack
├── If token contains operator character (+-*/^)
│   ├── Create operator node
│   ├── Pop right operand from stack
│   ├── Pop left operand from stack
│   ├── Set as children of operator node
│   └── Push operator node to stack
├── If token matches function name
│   ├── Create function node
│   ├── Pop argument from stack
│   ├── Set as left child of function node
│   └── Push function node to stack
└── Otherwise (numeric token)
    ├── Parse as double using strtod()
    ├── Create number node
    └── Push to stack
```

### 3. AST Construction

- After processing all tokens, stack contains single node
- This node is the root of the completed AST
- Stack underflow/overflow conditions trigger program termination

### 4. Function Resolution

Functions are resolved using a lookup table:

```c
const FunctionEntry FUNCTIONS[] = {
    {"sin", sin}, {"cos", cos}, {"tg", tan}, {"ctg", cot},
    {"ln", log}, {"exp", exp}
};
```

## Expression Evaluation

The evaluation process recursively traverses the AST using a depth-first approach:

### Evaluation Algorithm

```c
evaluate(node, x):
├── if node is NULL
│   └── return 0.0
├── if node is NODE_VARIABLE
│   └── return x
├── if node is NODE_NUMBER
│   └── return node.data.number.value
├── if node is NODE_FUNCTION
│   └── return function(evaluate(node.left, x))
└── if node is NODE_OPERATOR
    └── return evaluate(left, x) operator evaluate(right, x)
```

### Operator Evaluation

- `+`: Addition of left and right operands
- `-`: Subtraction (left - right)
- `*`: Multiplication of operands
- `/`: Division (left / right)
- `^`: Exponentiation using `pow(left, right)`

### Function Evaluation

Functions are evaluated by:

1. Recursively evaluating the argument (left child)
2. Applying the function to the result
3. Returning the computed value

## Memory Management

The parser implements comprehensive memory management:

### 1. Allocation

- All nodes use `NEW_NODE(TYPE)` macro
- Memory allocation failures trigger program termination
- Each allocation is checked before use

### 2. Initialization

- `initialize_node()` sets type and nullifies children
- Prevents uninitialized pointer access

### 3. Deallocation

```c
void free_tree(Node *node) {
    // Post-order traversal ensures children freed first
    // Prevents memory leaks and dangling pointers
}
```

**Note**: The `free_tree()` function is declared in the header but implementation should be provided separately.

## Function Reference

### Core Functions

#### `Node *parse(char *expression)`

Parses RPN expression string into AST.

- **Input**: Space-separated RPN expression
- **Output**: Root node of AST
- **Side effects**: Modifies input string (uses `strtok`)

#### `double evaluate(Node *head, double x)`

Evaluates AST for given variable value.

- **Input**: AST root node, variable value
- **Output**: Computed result
- **Complexity**: O(n) where n is number of nodes

### Node Creation Functions

#### `Node *create_variable(char name)`

Creates variable node with specified name.

#### `Node *create_number(double value)`

Creates number node with specified value.

#### `Node *create_function(const char *name, Func func)`

Creates function node with name and function pointer.

#### `Node *create_operator(char symbol)`

Creates operator node with specified symbol.

### Utility Functions

#### `void push(NodeStack *stack, Node *node)`

Pushes node onto parsing stack with overflow protection.

#### `Node *pop(NodeStack *stack)`

Pops node from parsing stack with underflow protection.

#### `Func find_function(const char *name)`

Looks up function by name in function table.

#### `double cot(double x)`

Implements cotangent function (1/tan(x)).

## Error Handling

The parser implements robust error handling:

### 1. Parse-time Errors

- **Invalid tokens**: Unrecognized symbols trigger program termination
- **Stack overflow**: Too many operands for available stack space
- **Stack underflow**: Insufficient operands for operators/functions
- **Memory allocation failures**: All allocation failures are fatal

### 2. Runtime Errors

- **Unknown operators**: Unsupported operator symbols
- **Unknown node types**: Corrupted or invalid AST nodes
- **Mathematical errors**: Division by zero, domain errors (handled by math library)

### 3. Error Reporting

All errors use `fprintf(stderr, ...)` and call `exit(1)` for immediate termination.

## Usage Examples

### Basic Arithmetic

```c
char expr1[] = "2 3 +";           // 2 + 3
Node *ast1 = parse(expr1);
double result1 = evaluate(ast1, 0); // = 5.0
free_tree(ast1);
```

### Variable Expression

```c
char expr2[] = "x 2 *";           // x * 2
Node *ast2 = parse(expr2);
double result2 = evaluate(ast2, 5); // = 10.0
free_tree(ast2);
```

### Function Usage

```c
char expr3[] = "x sin";           // sin(x)
Node *ast3 = parse(expr3);
double result3 = evaluate(ast3, 1.57); // ≈ 1.0
free_tree(ast3);
```

### Complex Expression

```c
char expr4[] = "2 x * 1 +";       // 2 * x + 1
Node *ast4 = parse(expr4);
double result4 = evaluate(ast4, 5); // = 11.0
free_tree(ast4);
```

### Integration Context

```c
// For numerical integration of sin(x) from 0 to π
char integrand[] = "x sin";
Node *expression = parse(integrand);

// Evaluate at multiple points
for (double x = 0; x <= 3.14159; x += 0.1) {
    double value = evaluate(expression, x);
    // Use value in integration calculations
}

free_tree(expression);
```

**Important Notes**:

- Input strings are modified by `strtok()` during parsing
- Always call `free_tree()` to prevent memory leaks
- Functions expect arguments in radians
- Parser does not validate mathematical domain (e.g., ln of negative numbers)
