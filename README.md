# Numerical Integrator

<div align="center">
    <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language: C">
    <img src="https://img.shields.io/badge/UI-GTK3-green.svg" alt="UI: GTK3">
    <img src="https://img.shields.io/badge/Math-Integration-red.svg" alt="Math: Integration">
</div>

<p align="center">
    <strong>A modern, user-friendly numerical integration system with mathematical expression parsing and a sleek graphical interface.</strong>
</p>

---

## ✨ Overview

The **Numerical Integrator** is a sophisticated C application designed to compute definite integrals of mathematical functions using multiple numerical methods. It combines powerful expression parsing, precise numerical integration algorithms, and an intuitive graphical user interface to provide a complete solution for mathematical integration problems.

<p align="center">
    <em>Bridging the gap between mathematical computation and user-friendly software design</em>
</p>

## 🚀 Features

### Mathematical Core

- **Multiple Integration Methods**:
  - Riemann Sum approximation
  - Lower and Upper Darboux Sum bounds
  - Error estimation between approximation methods

- **Comprehensive Expression Support**:
  - Variables (x)
  - Numeric constants
  - Binary operators (+, -, *, /, ^)
  - Mathematical functions (sin, cos, tg, ctg, ln, exp)

- **Robust Parsing System**:
  - Reverse Polish Notation (RPN) support
  - Abstract Syntax Tree (AST) representation
  - Efficient expression evaluation

### Modern User Interface

- **Sleek Design**:
  - Modern gradient-based visual styling
  - Responsive grid layouts
  - Intuitive workflow progression

- **Interactive Elements**:
  - Mathematical buttons for easy input
  - Smart text formatting
  - Real-time input validation

- **User Experience**:
  - Context-sensitive button states
  - Clear visual feedback
  - Guided integration process

### System Design

- **Modular Architecture**:
  - Separation of concerns across specialized modules
  - Clean interfaces between components
  - Maintainable and extensible codebase

- **Memory Safety**:
  - Comprehensive resource management
  - Memory leak prevention
  - Debug utilities for development

- **Error Handling**:
  - Input validation at multiple levels
  - Graceful error recovery
  - Clear user feedback

## 📦 Project Architecture

The project is organized into specialized modules, each with distinct responsibilities:

### Module Structure

```
src/
├── integrator/     # Numerical integration algorithms
├── parser/         # Mathematical expression parsing
├── controls/       # Coordination and validation
├── ui/             # Graphical user interface
└── memcheck/       # Memory debugging utilities
```

### Module Interactions

```
┌─────────────┐      ┌──────────────┐
│     UI      │─────▶│   Controls   │
└─────────────┘      └──────┬───────┘
      ▲                     │
      │                     ▼
┌─────┴───────┐      ┌──────────────┐
│  Integrator  │◀────┤    Parser    │
└─────────────┘      └──────────────┘
```

## 🧮 Core Components

### Numerical Integration Engine

The integration module implements three different approaches:

- **Riemann Sum**: Approximates the integral by evaluating the function at left endpoints
- **Lower Darboux Sum**: Uses minimum function values in each subinterval
- **Upper Darboux Sum**: Uses maximum function values in each subinterval

Providing multiple methods allows for error estimation and accuracy assessment.

### Expression Parser

The parser converts mathematical expressions from RPN format into an abstract syntax tree (AST):

```
Example: "2 x * 1 +" (representing 2*x + 1)

    (+)
   /   \
  (*)   (1)
 /   \
(2)   (x)
```

This tree structure allows for efficient evaluation at any point within the integration interval.

### Graphical User Interface

The GUI provides a clean, modern interface with three main sections:

1. **Function Input Area**:
   ```
   ┌─────────────────────────────────────┬──────────────────┐
   │ Enter function: ∫ f(x) dx           │ ✓ Confirm Function│
   └─────────────────────────────────────┴──────────────────┘
   ```

2. **Mathematical Button Matrix**:
   ```
   ┌─────┬─────┬─────┬─────┬─────┬─────┐
   │  +  │  -  │  *  │  /  │  ^  │  x  │
   ├─────┼─────┼─────┼─────┼─────┼─────┤
   │ sin │ cos │ tg  │ ctg │ ln  │ exp │
   └─────┴─────┴─────┴─────┴─────┴─────┘
   ```

3. **Integration Interval Section**:
   ```
   ┌─────────────────────┬─────────────────────┐
   │ Lower bound (a)     │ Upper bound (b)     │
   ├─────────────────────┴─────────────────────┤
   │           🚀 Calculate Integral            │
   └───────────────────────────────────────────┘
   ```

## 🔧 Core Functions

### Integration Module

```c
// Main integration function
void integrate(char *integrand, char *interval);

// Compute Riemann sum approximation
double calculate_Riemann_sum(Node* expression, double start, double end, double dx);

// Compute lower and upper Darboux sum bounds
double calculate_lower_Darboux_sum(Node* expression, double start, double end, double dx, double step);
double calculate_upper_Darboux_sum(Node* expression, double start, double end, double dx, double step);
```

### Expression Parser

```c
// Parse RPN expression into abstract syntax tree
Node* parse(char *expression);

// Evaluate expression at a specific point
double evaluate(Node *head, double x);

// Create nodes for different elements
Node* create_variable(char name);
Node* create_number(double value);
Node* create_function(const char *name, Func func);
Node* create_operator(char symbol);
```

### User Interface

```c
// Initialize and run the GUI
void run_gui(int* argc, char*** argv);

// Apply CSS styling to the interface
void apply_styling(const char *css_file_path);

// Event handlers
void insert_text(GtkWidget *button, gpointer user_data);
void save_to_file(GtkWidget *button, gpointer user_data);
void save_interval(GtkWidget *button, gpointer user_data);
```

### Controls Module

```c
// Input validation
bool validate_integrand(const char *integrand);
bool validate_interval(const char *interval, double *start, double *end);
int get_partition_refinement();

// Resource management
void free_tree(Node *node);
void free_resources(char *integrand, char *interval, Node *expression);

// Integration workflow
void numerical_integration(int argc, char *argv[], const char *filename);
void integrate_last(const char *filename);
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

## 🎯 Usage Guide

### Starting the Application

```bash
./numerical_integral
```

### Using the Interface

1. **Enter Your Function**:
   - Use the mathematical buttons for operators and functions
   - Enter numbers via keyboard
   - Functions use Reverse Polish Notation (e.g., `x sin` for sin(x))
   - Click "Confirm Function" when ready

2. **Specify Integration Interval**:
   - Enter lower and upper bounds
   - Click "Calculate Integral"

3. **Select Refinement Level**:
   - Enter a number between 1 and 20,000,000
   - Higher values provide more accurate results

4. **View Results**:
   - Riemann sum approximation
   - Lower and upper Darboux sums
   - Error bounds and average approximation

### Example Calculation

**Function**: x² + 1 (entered as `x x * 1 +`)
**Interval**: [0, 5]
**Refinement**: 1000

**Results**:
```
Riemann-sum = 46,734187
Lower Darboux-sum = 46,734187
Upper Darboux-sum = 46,859285

Difference between Darboux-sums = 0,125098
Average of the Darboux-sums = 46,796736

Difference between Riemann-sum and average of the Darboux-sums = 0,062549
```

## 📋 Supported Mathematical Functions

| Function | Description | Example (RPN) |
|----------|-------------|--------------|
| + | Addition | `2 3 +` |
| - | Subtraction | `5 2 -` |
| * | Multiplication | `2 x *` |
| / | Division | `x 2 /` |
| ^ | Exponentiation | `x 2 ^` |
| sin | Sine (radians) | `x sin` |
| cos | Cosine (radians) | `x cos` |
| tg | Tangent (radians) | `x tg` |
| ctg | Cotangent (radians) | `x ctg` |
| ln | Natural logarithm | `x ln` |
| exp | Exponential function | `x exp` |

## 🔍 More Example Integrals

| Function (RPN) | Interval | Mathematical Equivalent | Exact Result |
|----------------|----------|-------------------------|-------------|
| `x sin` | [0 ; π] | ∫₀ᵗ sin(x) dx | 2 |
| `x x * 1 +` | [0 ; 5] | ∫₀⁵ (x² + 1) dx | 41.6667 |
| `x exp` | [0 ; 1] | ∫₀¹ eˣ dx | 1.7183 |
| `x cos x *` | [0 ; π/2] | ∫₀ᵗ/² x·cos(x) dx | 0.5 |

## 🛠️ Advanced Features

### Integration Methods

The application provides three different numerical integration methods:

1. **Riemann Sum**: Evaluates the function at the left endpoint of each subinterval
2. **Lower Darboux Sum**: Finds the minimum value within each subinterval
3. **Upper Darboux Sum**: Finds the maximum value within each subinterval

The difference between upper and lower Darboux sums provides a rigorous error bound for the approximation.

### Styling Customization

The user interface appearance can be customized by modifying the `styles.css` file. The styling system includes:

- Color schemes
- Typography
- Button appearances
- Layout spacing
- Visual effects

### Error Handling

The application includes comprehensive error handling:

- Invalid expression detection
- Improper interval formatting
- Out-of-range refinement values
- Memory allocation failures
- File operation errors

---

<p align="center">
<em>Developed with ❤️ for mathematical precision and user experience</em>
</p>

*Last updated: July 2025*
