# Numerical Integrator

Welcome to the **Numerical Integrator** project! This repository hosts a C program designed to compute definite
integrals of mathematical functions using numerical methods. With an intuitive GUI and powerful expression parsing, this
project bridges the gap between mathematical computation and user-friendly software design.

---

## Features

### 🚀 Core Functionality

- **Numerical Integration**: Accurately calculate the definite integral of user-defined functions using Riemann's
  method.
- **Expression Parsing**: Robust mathematical expression parsing with support for Reverse Polish Notation (RPN).
    - Only elementary functions such as polynomials, exponentials, trigonometric functions, and logarithms are
      supported.

### 🎨 Graphical User Interface

- A clean and intuitive GUI for inputting expressions and integration bounds.
- Using the GTK+ library and a CSS stylesheet for a modern look and feel.

### 🛠 Debugging and Development

- Includes a memory debugging utility (`debugmalloc.h`) to ensure stability and catch memory leaks during development.
- In order to apply the styles from the css file, you need to copy the styles.css to the same directory as the
  executable file.

---

## 📦 Project Structure

```
src/
├── integrator/       # Core integration logic
├── parser/          # Expression parsing engine
├── program/         # Program entry point
├── ui/             # User interface components
└── memcheck/        # Memory debugging utilities
```

## 🏗 Core Components

### Expression Tree Architecture

The parser uses a tree-based structure to represent mathematical expressions. Here are the key components:

#### Node Types
```c
typedef enum NodeType {
    NODE_VARIABLE,   // Variables (e.g., 'x')
    NODE_NUMBER,     // Numeric constants
    NODE_FUNCTION,   // Mathematical functions
    NODE_OPERATOR    // Mathematical operators
} NodeType;
```

#### Key Data Structures
```c
// Variable representation
typedef struct Variable {
    char name;       // Variable identifier
} Variable;

// Numeric value
typedef struct Number {
    double value;    // Numeric constant
} Number;

// Mathematical function
typedef struct Function {
    char name[FUNCTION_NAME_MAX];
    double (*func)(double);  // Function pointer
} Function;
```

## 🔧 Core Functions

### Integration Module

```c
// Performs numerical integration
void integrate(char *integrand, char *interval);

// Validates integration bounds
bool validate_interval(const char *interval, 
                      double *start, double *end);

// Finds maximum value in interval
double find_supremum(Node* expr, double start, 
                    double end, double step);
```

### Expression Parser

```c
// Parses RPN expression into tree
Node* parse_expression(const char *expression);

// Evaluates expression with given variable value
double evaluate(Node *root, double x);
```

## 🚀 Getting Started

### Prerequisites

- C Compiler (GCC recommended)
- GTK+ 3.0 Development Libraries
- CMake (3.10 or higher)

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/numerical-integrator.git
   cd numerical-integrator
   ```

2. Create build directory:
   ```bash
   mkdir build && cd build
   ```

3. Configure and build:
   ```bash
   cmake ..
   make
   ```

4. Copy required assets:
   ```bash
   cp ../src/ui/styles.css .
   ```

## 🎯 Usage

1. Launch the program:
   ```bash
   ./numerical_integral
   ```

2. Using the Interface:
   - Enter mathematical expressions using RPN notation
   - Use the GUI buttons for operators and functions
   - Enter numbers via keyboard
   - Specify integration bounds when prompted

### Example Input

```
x x * 2 +    # Represents x² + 2
[0, 5]       # Integration bounds
```

---

*Last updated: July 2025*
