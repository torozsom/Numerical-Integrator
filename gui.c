#include "gui.h"
#include "debugmalloc.h"


/**
 * Reads the last two lines of a file and stores them in the provided pointers.
 * Memory for the lines is dynamically allocated and must be freed by the caller.
 *
 * @param filename Name of the file to read from.
 * @param last Pointer to a char pointer where the last line of the file will be stored.
 * @param second_last Pointer to a char pointer where the second-to-last line of the file will be stored.
 */
void read_file(const char *filename, char **last, char **second_last) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char *last_line = nullptr;
    char *second_last_line = nullptr;
    int size = INITIAL_SIZE;

    last_line = (char *) malloc(size * sizeof(char)+1);
    second_last_line = (char *) malloc(size * sizeof(char)+1);

    if (last_line == NULL || second_last_line == NULL) {
        perror("Did not manage to allocate memory");
        return;
    }

    last_line[0] = '\0';
    second_last_line[0] = '\0';

    while (fgets(last_line, size, file) != NULL) {
        if (last_line[strlen(last_line) - 1] == '\n') {
            char *temp = last_line;
            last_line = second_last_line;
            second_last_line = temp;
        } else {
            size *= 2;
            last_line = (char *) realloc(last_line, size * sizeof(char));
            second_last_line = (char *) realloc(second_last_line, size * sizeof(char));

            if (last_line == NULL || second_last_line == NULL) {
                perror("Did not manage to allocate memory");
                return;
            }
        }
    }

    *last = last_line;
    *second_last = second_last_line;

    fclose(file);
}


/**
 * @brief Removes leading and trailing spaces from a given string and compresses the string.
 *        The trimmed string is stored in the same memory location as the input string.
 *
 * @param str The input string from which spaces are to be removed.
 *            After execution, the string will no longer contain leading or trailing spaces.
 */
void remove_spaces(char *str) {
    size_t start = 0, end = strlen(str) - 1;
    while (isspace(str[start]))
        start++;
    while (end > start && isspace(str[end]))
        end--;

    size_t i, j;
    for (i = start, j = 0; i <= end; i++, j++)
        str[j] = str[i];
    str[j] = '\0';
}


/**
 * @brief Initializes and runs a GTK graphical user interface for numerical integration.
 *
 * This function sets up a graphical user interface (GUI) using GTK for entering
 * mathematical functions, specifying integration intervals, and calculating results.
 * It includes input fields, buttons for mathematical operators, and grid-based layouts
 * for organizing the components.
 *
 * @param argc Pointer to the argument count (usually provided from the main function).
 * @param argv Pointer to the argument vector (usually provided from the main function).
 */
void run_gui(int *argc, char ***argv) {
    Grids grids;
    Buttons buttons;
    Entry entry;
    Labels labels;

    const char *button_labels[] = {
        "+", "-", "*", "/", "^", "x",
        "sin", "cos", "tg", "ctg", "ln", "exp"
    };

    gtk_init(argc, argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Numerical Integral");
    gtk_window_set_default_size(GTK_WINDOW(window), 450,
                                700); // Default settings
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grids.func = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grids.func);
    gtk_widget_set_hexpand(grids.func, TRUE);
    gtk_widget_set_vexpand(grids.func, TRUE);

    entry.func = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry.func), "∫ f(x) dx");
    buttons.okFunc = gtk_button_new_with_label("OK!");

    gtk_grid_attach(GTK_GRID(grids.func), entry.func, 0, 0, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grids.func), buttons.okFunc, entry.func,
                            GTK_POS_RIGHT, 1, 1);

    grids.buttons = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grids.buttons), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grids.buttons), TRUE);

    gtk_grid_attach_next_to(GTK_GRID(grids.func), grids.buttons, entry.func,
                            GTK_POS_BOTTOM, 2, 1);

    buttons.matrix = malloc(12 * sizeof(GtkWidget *));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
            buttons.matrix[i * 2 + j] =
                    gtk_button_new_with_label(button_labels[i * 2 + j]);
            PangoFontDescription *font_desc = pango_font_description_new();
            pango_font_description_set_family(font_desc, "Times New Roman");
            pango_font_description_set_size(font_desc, 15 * PANGO_SCALE);
            gtk_widget_override_font(
                buttons.matrix[i * 2 + j],
                font_desc);
            pango_font_description_free(font_desc);

            gtk_grid_attach(GTK_GRID(grids.buttons), buttons.matrix[i * 2 + j], j,
                            i, 1, 1);
            gtk_widget_set_hexpand(buttons.matrix[i * 2 + j], TRUE);
            gtk_widget_set_vexpand(buttons.matrix[i * 2 + j], TRUE);

            g_signal_connect(buttons.matrix[i * 2 + j], "clicked",
                             G_CALLBACK(insert_text), &entry);
        }
    }

    g_signal_connect(buttons.okFunc, "clicked", G_CALLBACK(save_to_file),
                     &entry);
    g_signal_connect(buttons.okFunc, "clicked", G_CALLBACK(disable_button),
                     NULL);

    grids.interval = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grids.interval), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grids.interval), TRUE);

    gtk_grid_attach_next_to(GTK_GRID(grids.func), grids.interval,
                            grids.buttons, GTK_POS_BOTTOM, 2, 1);

    labels.Title = gtk_label_new("Enter the interval: ");
    gtk_misc_set_alignment(GTK_MISC(labels.Title), 0.5, 0);

    gtk_grid_attach(GTK_GRID(grids.interval), labels.Title, 0, 0, 2, 1);

    entry.start = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry.start), "Start:");
    entry.end = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry.end), "End:");
    buttons.okInterval = gtk_button_new_with_label("OK!");

    gtk_grid_attach(GTK_GRID(grids.interval), entry.start, 0, 1, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grids.interval), entry.end, entry.start,
                            GTK_POS_RIGHT, 1, 1);
    gtk_grid_attach_next_to(GTK_GRID(grids.interval), buttons.okInterval,
                            entry.start, GTK_POS_BOTTOM, 2, 1);

    g_signal_connect(buttons.okInterval, "clicked", G_CALLBACK(save_interval),
                     &entry);
    g_signal_connect(buttons.okInterval, "clicked", G_CALLBACK(over), window);

    gtk_widget_show_all(window);

    gtk_main();

    free(buttons.matrix);
}


/**
 * @brief Appends the text of a clicked button to an entry widget,
 *        formatting it appropriately based on certain conditions.
 *
 * This function is triggered when a button is clicked in the GUI.
 * It retrieves the label of the clicked button and appends it to
 * the text in the provided GtkEntry widget. For mathematical
 * functions (e.g., "sin", "cos", etc.), it formats the text
 * by including a multiplication sign ("x").
 *
 * @param button A GtkWidget representing the clicked button.
 * @param user_data A pointer to user data, expected to be a struct
 *                  of type Entry containing the target GtkEntry widget.
 */
void insert_text(GtkWidget *button, gpointer user_data) {
    Entry *entry = (Entry *) user_data;
    const char *text = gtk_button_get_label(GTK_BUTTON(button));

    if (strcmp(text, "sin") == 0 || strcmp(text, "cos") == 0 ||
        strcmp(text, "tg") == 0 || strcmp(text, "ctg") == 0 ||
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


/**
 * @brief Saves the text from the GtkEntry widget associated with the specified button
 * into a file named "functions.txt".
 *
 * This function is typically connected to a button click signal to save user input
 * from a GtkEntry widget to a predefined file. The file is opened in append mode,
 * so new entries are added to the end of the file.
 *
 * @param button The GtkWidget pointer representing the button that triggered the signal.
 * @param user_data A gpointer to the user-provided data, expected to be a pointer to an Entry
 * structure containing the GtkEntry widget whose text is to be saved.
 */
void save_to_file(GtkWidget *button, gpointer user_data) {
    Entry *entry = (Entry *) user_data;
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


/**
 * @brief Saves the interval entered by the user to a file.
 *
 * This function is triggered upon a button click in the GUI to read the start and end
 * interval values from the provided GtkEntry widgets, and appends them as an interval
 * to a file named "functions.txt". If the file cannot be opened, an error message is displayed.
 *
 * @param button The GtkWidget pointer representing the button that triggered the callback.
 * @param user_data A gpointer to the user-provided data, expected to be a pointer to an Entry structure
 *                  containing GtkEntry widgets for the start and end interval.
 */
void save_interval(GtkWidget *button, gpointer user_data) {
    Entry *entry = (Entry *) user_data;
    const gchar *text1 = gtk_entry_get_text(GTK_ENTRY(entry->start));
    const gchar *text2 = gtk_entry_get_text(GTK_ENTRY(entry->end));
    const char *filename = "functions.txt";

    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "[%s ; ", text1);
        fprintf(file, "%s]\n", text2);
        fclose(file);
    } else {
        perror("Could not open the file.\n");
    }
}


/**
 * Disables a given GTK button, making it insensitive to user interactions.
 *
 * @param button A pointer to the GtkWidget representing the button to disable.
 * @param user_data A pointer to user-defined data. This is not used in the function.
 */
void disable_button(GtkWidget *button, gpointer user_data) {
    gtk_widget_set_sensitive(button, FALSE);
}


/**
 * @brief Destroys a GTK widget.
 *
 * This function destroys the GTK widget passed as user_data.
 *
 * @param button The GTK widget that triggers the function, generally a button.
 * @param user_data A pointer to the GTK widget to be destroyed (typically a window or another widget).
 */
void over(GtkWidget *button, gpointer user_data) {
    gtk_widget_destroy(GTK_WIDGET(user_data));
}
