# Graphical User Interface Module

A modern GTK-based graphical user interface for the Numerical Integration Calculator. This module provides an intuitive, user-friendly interface for entering mathematical expressions, specifying integration intervals, and initiating calculations with professional styling and responsive design.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Data Structures](#data-structures)
- [User Interface Components](#user-interface-components)
- [Styling System](#styling-system)
- [Event Handling](#event-handling)
- [File Operations](#file-operations)
- [Function Reference](#function-reference)
- [Usage Examples](#usage-examples)
- [Dependencies](#dependencies)

## Overview

The GUI module creates a comprehensive graphical interface using GTK3, featuring:
- Modern gradient-based visual design
- Intuitive mathematical function input with helper buttons
- Integration interval specification
- Real-time text insertion and formatting
- File-based data persistence
- Responsive layout with proper spacing and alignment

The interface follows a logical workflow: function entry → interval specification → calculation execution.

## Features

### Visual Design
- **Modern Styling**: Gradient backgrounds, rounded corners, and professional color scheme
- **CSS-based Theming**: External stylesheet support for easy customization
- **Responsive Layout**: Grid-based organization with proper spacing
- **Visual Feedback**: Hover effects, focus states, and button styling

### User Interaction
- **Mathematical Input Buttons**: Pre-defined buttons for operators and functions
- **Text Entry Fields**: Dedicated fields for function expression and interval bounds
- **Smart Text Formatting**: Automatic spacing and function formatting
- **Button State Management**: Context-sensitive button enabling/disabling

### Data Management
- **File Persistence**: Automatic saving of functions and intervals
- **Input Validation**: Real-time text processing and formatting
- **Memory Management**: Proper allocation and cleanup of GUI resources

## Architecture

### Component Hierarchy
```
Main Window
├── Title Section
│   └── Application Title Label
├── Function Input Section
│   ├── Function Entry Field
│   └── Confirm Function Button
├── Mathematical Buttons Section
│   └── 6×2 Button Matrix
│       ├── Operators: +, -, *, /, ^, x
│       └── Functions: sin, cos, tg, ctg, ln, exp
└── Interval Section
    ├── Start Bound Entry
    ├── End Bound Entry
    └── Calculate Button
```

### Layout System
- **Main Container**: Vertical box layout with proper margins
- **Grid Layouts**: Three separate grids for different UI sections
- **Responsive Design**: Automatic resizing and proper spacing
- **Fixed Window Size**: 650×550 pixels for consistent appearance

## Data Structures

### Core Structures

#### `Grids`
Manages the main layout containers:
```c
typedef struct Grids {
    GtkWidget *func;       // Function input grid
    GtkWidget *buttons;    // Mathematical buttons grid
    GtkWidget *interval;   // Interval specification grid
} Grids;
```

#### `Buttons`
Contains all interactive button widgets:
```c
typedef struct Buttons {
    GtkWidget *okFunc;      // Function confirmation button
    GtkWidget **matrix;     // 12-element button array
    GtkWidget *okInterval;  // Calculation trigger button
} Buttons;
```

#### `Entry`
Manages all text input fields:
```c
typedef struct Entry {
    GtkWidget *func;   // Function expression field
    GtkWidget *start;  // Interval start bound
    GtkWidget *end;    // Interval end bound
} Entry;
```

#### `Labels`
Contains descriptive text elements:
```c
typedef struct Labels {
    GtkWidget *title;  // Main application title
    GtkWidget *start;  // Start bound label
    GtkWidget *end;    // End bound label
} Labels;
```

## User Interface Components

### 1. Application Window
- **Title**: "✨ Numerical Integration Calculator"
- **Size**: 650×550 pixels (non-resizable)
- **Position**: Centered on screen
- **Icon**: Custom application icon (icon.png)
- **Background**: Gradient from #667eea to #764ba2

### 2. Function Input Section
```
┌─────────────────────────────────────────┬──────────────────┐
│ Enter function: ∫ f(x) dx               │ ✓ Confirm Function│
└─────────────────────────────────────────┴──────────────────┘
```
- **Entry Field**: Large text input with placeholder
- **Confirm Button**: Saves function and disables itself
- **Styling**: Semi-transparent white background with blue border

### 3. Mathematical Buttons Matrix
```
┌─────┬─────┬─────┬─────┬─────┬─────┐
│  +  │  -  │  *  │  /  │  ^  │  x  │
├─────┼─────┼─────┼─────┼─────┼─────┤
│ sin │ cos │ tg  │ ctg │ ln  │ exp │
└─────┴─────┴─────┴─────┴─────┴─────┘
```

#### Button Categories:
- **Operators** (`+`, `-`, `*`, `/`, `^`, `x`): Cyan gradient styling
- **Functions** (`sin`, `cos`, `tg`, `ctg`, `ln`, `exp`): Purple gradient styling
- **Interactive**: Hover effects and click feedback

### 4. Integration Interval Section
```
┌─────────────────────┬─────────────────────┐
│ Lower bound (a)     │ Upper bound (b)     │
├─────────────────────┴─────────────────────┤
│           🚀 Calculate Integral            │
└───────────────────────────────────────────┘
```
- **Dual Entry**: Side-by-side interval bounds
- **Calculate Button**: Full-width execution button
- **Green Styling**: Distinctive color for primary action

## Styling System

### CSS Architecture
The module uses external CSS (`styles.css`) for comprehensive theming:

#### Color Scheme
- **Primary**: Blue gradients (#4a90e2 to #357abd)
- **Accent**: Purple for functions (#6c5ce7 to #a29bfe)
- **Success**: Green for actions (#00b894 to #00cec9)
- **Background**: Blue-purple gradient (#667eea to #764ba2)

#### Typography
- **Font Family**: 'Segoe UI', 'Liberation Sans', sans-serif
- **Function Buttons**: 'Cambria Math', 'Times New Roman', serif
- **Sizes**: 18px (labels), 20px (buttons), 24px (entries), 25px (title)

#### Visual Effects
- **Gradients**: All buttons and backgrounds use CSS gradients
- **Shadows**: Box shadows for depth and focus states
- **Borders**: Rounded corners (8px radius) throughout
- **Transparency**: Semi-transparent entry backgrounds

### Style Classes
- `.title`: Large, bold application title
- `.operator`: Cyan gradient for mathematical operators
- `.math-function`: Purple gradient for mathematical functions
- `.ok-button`: Green gradient for action buttons

## Event Handling

### Signal Connections

#### Button Click Events
```c
// Mathematical buttons
g_signal_connect(buttons.matrix[i], "clicked", 
                 G_CALLBACK(insert_text), &entry);

// Function confirmation
g_signal_connect(buttons.okFunc, "clicked", 
                 G_CALLBACK(save_to_file), &entry);
g_signal_connect(buttons.okFunc, "clicked", 
                 G_CALLBACK(disable_button), NULL);

// Interval calculation
g_signal_connect(buttons.okInterval, "clicked", 
                 G_CALLBACK(save_interval), &entry);
g_signal_connect(buttons.okInterval, "clicked", 
                 G_CALLBACK(over), window);
```

#### Window Events
```c
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
```

### Event Flow
1. **Text Insertion**: Mathematical buttons → `insert_text()` → Update entry field
2. **Function Saving**: Confirm button → `save_to_file()` + `disable_button()`
3. **Interval Processing**: Calculate button → `save_interval()` + `over()`
4. **Application Exit**: Window close → `gtk_main_quit()`

## File Operations

### Data Persistence
All user input is automatically saved to `functions.txt`:

#### Function Storage
```c
void save_to_file(GtkWidget *button, gpointer user_data) {
    // Appends function expression to file
    FILE *file = fopen("functions.txt", "a");
    fprintf(file, "%s\n", function_text);
}
```

#### Interval Storage
```c
void save_interval(GtkWidget *button, gpointer user_data) {
    // Appends interval in [start ; end] format
    FILE *file = fopen("functions.txt", "a");
    fprintf(file, "[%s ; %s]\n", start_text, end_text);
}
```

### File Format
```
x sin 2 *
[0 ; 3.14159]
x x * exp
[-1 ; 1]
```

## Function Reference

### Core Functions

#### `void run_gui(int* argc, char*** argv)`
Main GUI initialization and execution function.
- **Parameters**: Command line arguments (passed to GTK)
- **Creates**: Complete GUI interface with all components
- **Starts**: GTK main event loop
- **Memory**: Allocates button matrix, handles cleanup

#### `void apply_styling(const char *css_file_path)`
Loads external CSS styling for the application.
- **Parameters**: Path to CSS file
- **Function**: Applies modern visual styling
- **Error Handling**: Graceful fallback if CSS loading fails

### Event Handlers

#### `void insert_text(GtkWidget *button, gpointer user_data)`
Handles mathematical button clicks and text insertion.
- **Smart Formatting**: Adds spaces and special formatting for functions
- **Function Detection**: Special handling for sin, cos, tg, ctg, exp, ln
- **Text Concatenation**: Appends button text to current entry content

#### `void save_to_file(GtkWidget *button, gpointer user_data)`
Saves function expression to persistent storage.
- **File**: Appends to "functions.txt"
- **Format**: Plain text with newline termination
- **Error Handling**: Prints error message on file operation failure

#### `void save_interval(GtkWidget *button, gpointer user_data)`
Saves integration interval to file.
- **Format**: `[start ; end]` notation
- **File**: Appends to same "functions.txt" file
- **Validation**: Basic text extraction and formatting

#### `void disable_button(GtkWidget *button, gpointer user_data)`
Disables button to prevent multiple activations.
- **Usage**: Called after function confirmation
- **Effect**: Makes button insensitive (grayed out)

#### `void over(GtkWidget *button, gpointer user_data)`
Closes the application window.
- **Trigger**: Calculate button click
- **Action**: Destroys main window widget
- **Result**: Application termination

## Usage Examples

### Basic Application Launch
```c
int main(int argc, char *argv[]) {
    run_gui(&argc, &argv);
    return 0;
}
```

### Custom Styling Application
```c
// Apply custom theme
apply_styling("/path/to/custom/styles.css");

// Launch with custom styling
run_gui(&argc, &argv);
```

### Typical User Workflow
1. **Launch Application**: GUI window opens with all components
2. **Enter Function**: 
   - Type directly: "2 x * sin"
   - Use buttons: Click "2", "x", "*", "sin"
3. **Confirm Function**: Click "✓ Confirm Function" (button becomes disabled)
4. **Set Interval**: Enter "0" and "3.14159" in bound fields
5. **Calculate**: Click "🚀 Calculate Integral" (window closes, processing begins)

### File Output Example
After user interaction, `functions.txt` contains:
```
2 x * sin
[0 ; 3.14159]
```

## Dependencies

### Required Libraries
- **GTK3**: Core GUI framework (`gtk/gtk.h`)
- **GLib**: String manipulation and memory management
- **GDK**: Display and styling management

### System Requirements
- GTK3 development libraries
- CSS file (`styles.css`) in `../src/ui/` directory
- Optional: Application icon (`icon.png`)

### External Files
- `styles.css`: Modern visual styling definitions
- `icon.png`: Application window icon (optional)
- `debugmalloc.h`: Memory debugging support

### Integration Dependencies
The GUI module integrates with:
- **File System**: Reads CSS, writes function data
- **Integration Engine**: Provides input for numerical calculations
- **Parser Module**: Functions/intervals processed by expression parser

## Error Handling

### CSS Loading Errors
- Graceful fallback to default GTK styling
- Error messages printed to stderr
- Application continues without custom styling

### File Operation Errors
- `perror()` messages for file access issues
- Application continues with reduced functionality
- Data loss prevention through error checking

### Memory Management
- Proper allocation checking for button matrix
- Automatic GTK widget cleanup on application exit
- No explicit memory leaks in GUI components

### GTK Errors
- Standard GTK error handling through GError system
- Signal connection validation
- Widget state management for proper UI flow