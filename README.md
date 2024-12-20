# Numerical Integrator

Welcome to the **Numerical Integrator** project! This repository hosts a C program designed to compute definite integrals of mathematical functions using numerical methods. With an intuitive GUI and powerful expression parsing, this project bridges the gap between mathematical computation and user-friendly software design.

---

## Features

### 🚀 Core Functionality
- **Numerical Integration**: Accurately calculate the definite integral of user-defined functions using Riemann's method.
- **Expression Parsing**: Robust mathematical expression parsing with support for Reverse Polish Notation (RPN).
  - Only elementary functions such as polynomials, exponentials, trigonometric functions, and logarithms are supported.

### 🎨 Graphical User Interface
- A clean and intuitive GUI for inputting expressions and integration bounds.
- Visual feedback for integration results.

### 🛠 Debugging and Development
- Includes a memory debugging utility (`debugmalloc.h`) to ensure stability and catch memory leaks during development.

---

## Project Structure

- **`main.c`**: Entry point for the program. Coordinates initialization and execution.
- **`integral.c` / `integral.h`**: Implements numerical integration logic.
- **`expression_parser.c` / `expression_parser.h`**: Handles mathematical expression parsing.
- **`gui.c` / `gui.h`**: Provides the graphical user interface.
- **`debugmalloc.h`**: Utility for debugging memory allocation issues.
- **`CMakeLists.txt`**: Build configuration for the project.

---

## Build and Run

### Prerequisites
- **C Compiler**: GCC or similar.
- **CMake**: Build tool for project configuration.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/torozsom/numerical-integrator.git
   cd numerical-integrator
   ```
2. Configure the project using CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   ```
3. Build the project:
   ```bash
   make
   ```
4. Run the program:
   ```bash
   ./numerical_integrator
   ```

---

## Usage

1. Launch the program.
2. Enter the mathematical function to integrate in **RPN format** (e.g., `x sin`).
3. Specify the integration bounds (e.g., `a = -2.3, b = 12.8`).
4. View the computed integral value.

### Note:
- The program utilizes the properties of the Riemann integral to perform calculations. Ensure the function is well-behaved over the integration bounds for accurate results.

---
