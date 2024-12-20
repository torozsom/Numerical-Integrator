#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_SIZE 256


typedef struct Grids {
    GtkWidget *func;
    GtkWidget *buttons;
    GtkWidget *interval;
} Grids;


typedef struct Buttons {
    GtkWidget *okFunc;
    GtkWidget **matrix;
    GtkWidget *okInterval;
} Buttons;


typedef struct Entry {
    GtkWidget *func;
    GtkWidget *start;
    GtkWidget *end;
} Entry;


typedef struct Labels {
    GtkWidget *Title;
    GtkWidget *start;
    GtkWidget *end;
} Labels;



void read_file(const char *filename, char **last, char **second_last);

void remove_spaces(char *str);

void run_gui(int* argc, char*** argv);

void insert_text(GtkWidget *button, gpointer user_data);

void save_to_file(GtkWidget *button, gpointer user_data);

void save_interval(GtkWidget *button, gpointer user_data);

void disable_button(GtkWidget *button, gpointer user_data);

void over(GtkWidget *button, gpointer user_data);


#endif /* GUI_H */
