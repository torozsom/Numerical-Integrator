/**
 * @file gui.h
 * @brief Header file for the GUI components of the application.
 *
 * This file contains the declarations of structures and function prototypes
 * used in the graphical user interface of the application. It includes
 * definitions for grid layouts, buttons, entries, and labels used in the GUI.
 */


#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_SIZE 256


/**
 * @struct Grids
 *
 * A structure that represents the main grid layout components of the GUI. It
 * contains grid widgets used to organize various elements like function input,
 * buttons, and interval-related inputs in the application's graphical user interface.
 */
typedef struct Grids {
    GtkWidget *func;
    GtkWidget *buttons;
    GtkWidget *interval;
} Grids;


/**
 * @struct Buttons
 *
 * A structure that encapsulates various button widgets used within the
 * graphical user interface for user interactions such as confirming input
 * or managing operations.
 */
typedef struct Buttons {
    GtkWidget *okFunc;
    GtkWidget **matrix;
    GtkWidget *okInterval;
} Buttons;


/**
 * @struct Entry
 *
 * A structure used to manage input entries related to the function and interval
 * specification in the GUI for the numerical integral application. It holds
 * widgets for inputting the function expression and defining the integration
 * interval (start and end points).
 */
typedef struct Entry {
    GtkWidget *func;
    GtkWidget *start;
    GtkWidget *end;
} Entry;


/**
 * @struct Labels
 *
 * A structure that holds label widgets used in the GUI to display titles and
 * prompts for user input, such as the title of the application and labels for
 * start and end interval inputs.
 */
typedef struct Labels {
    GtkWidget *title;
    GtkWidget *start;
    GtkWidget *end;
} Labels;



void read_file(const char *filename, char **last, char **second_last);

void remove_spaces(char *str);

void apply_styling(const char *css_file_path);

void run_gui(int* argc, char*** argv);

void insert_text(GtkWidget *button, gpointer user_data);

void save_to_file(GtkWidget *button, gpointer user_data);

void save_interval(GtkWidget *button, gpointer user_data);

void disable_button(GtkWidget *button, gpointer user_data);

void over(GtkWidget *button, gpointer user_data);


#endif /* GUI_H */
