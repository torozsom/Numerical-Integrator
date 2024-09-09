#include "gui.h"
#include "debugmalloc.h"

// Inserts the appropriate Reverse Polish Notation into the entry
void insert_text(GtkWidget *button, gpointer user_data) {
    Entry *entry = (Entry *)user_data;
    const char *text = gtk_button_get_label(GTK_BUTTON(button));

    if (strcmp(text, "sin") == 0 || strcmp(text, "cos") == 0 || 
        strcmp(text, "tg") == 0  || strcmp(text, "ctg") == 0 || 
        strcmp(text, "exp") == 0 || strcmp(text, "ln") == 0) {

        const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry->func));
        gchar *new_text = g_strdup_printf("%s x %s", current_text, text);
        gtk_entry_set_text(GTK_ENTRY(entry->func), new_text);
        g_free(new_text);
    

    } else {
        const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry->func));
        gchar *new_text = g_strdup_printf("%s %s", current_text, text);
        gtk_entry_set_text(GTK_ENTRY(entry->func), new_text);
        g_free(new_text);
    }
}

void save_to_file(GtkWidget *button, gpointer user_data) {
    Entry *entry = (Entry *)user_data;
    const gchar *text_to_save = gtk_entry_get_text(GTK_ENTRY(entry->func));
    const char *filename = "functions.txt";
    
    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s\n", text_to_save);
        fclose(file);
    } else {
        perror("Could not open the file.\n");
    }
}

void save_interval(GtkWidget *button, gpointer user_data){
    Entry *entry = (Entry*) user_data;
    const gchar *text1 = gtk_entry_get_text(GTK_ENTRY(entry->start));
    const gchar *text2 = gtk_entry_get_text(GTK_ENTRY(entry->end));
    const char *filename = "functions.txt";

    FILE *file = fopen(filename, "a");
    if(file){
        fprintf(file, "[%s ; ", text1);
        fprintf(file, "%s]\n", text2);
        fclose(file);
    } else {
        perror("Could not open the file.\n");
    }
}

void disable_button(GtkWidget *button, gpointer user_data) {
    gtk_widget_set_sensitive(button, FALSE);
}

void over(GtkWidget *button, gpointer user_data){
    gtk_widget_destroy(GTK_WIDGET(user_data));
}
