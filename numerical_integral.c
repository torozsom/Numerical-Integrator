#include "debugmalloc.h"

#include "gui.h"
#include "integral.h"
#include "expression_parser.h"


int main(int argc, char *argv[]) {

  GtkWidget *window;
  Grids grids;
  Buttons buttons;
  Entry entry;
  Labels labels;

  const char *button_labels[] = {"+",   "-",   "*",  "/",   "^",  "x",
                                 "sin", "cos", "tg", "ctg", "ln", "exp"};

  const char *filename = "functions.txt";

  int num;
  printf("Welcome to my program of numerical integration!\n\n");
  printf(
      "------------------------------------------------------------------------"
      "----------------------------------------\n"
      "| The rules of integrating: \n"
      "| \t a. An interface will be of your assistance. \n"
      "| \t b. You will need to enter your functions by pressing buttons. \n"
      "| \t c. Only numbers are to be entered by the keyboard. \n"
      "| \t d. You have to use Reverse Polish Notation! \n"
      "| \t e. You must enter the right amount of operators, otherwise the "
      "program terminates. (Stack Over-/Underflow)\n"
      "| \t f. You must enter spaces between all operands and operators. \n"
      "| \t g. The entry for the integrand must not exceed 100 characters. \n"
      "------------------------------------------------------------------------"
      "----------------------------------------\n\n\n");

  do {
    printf("\nI can do the following tasks for you:\n\n"
           "\t 1. Numerical integration\n"
           "\t 2. List the functions that have been saved\n"
           "\t 9. Exit\n\n"
           "To execute a task, enter a number chosen from above: ");
    scanf("%d", &num);
    printf("\n");

    switch (num) {

    case 1:

      // RUNNING THE GUI:

      gtk_init(&argc, &argv);

      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
              font_desc); // setting the design of the buttons
          pango_font_description_free(font_desc);

          gtk_grid_attach(GTK_GRID(grids.buttons), buttons.matrix[i * 2 + j], j,
                          i, 1, 1);
          gtk_widget_set_hexpand(buttons.matrix[i * 2 + j], TRUE);
          gtk_widget_set_vexpand(buttons.matrix[i * 2 + j], TRUE);

          const char *label_text = button_labels[i * 2 + j];
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

      // INTEGRATING:

      char *integrand;
      char *interval;
      read_file(filename, &integrand, &interval);

      remove_spaces(integrand);

      if (strlen(integrand) > 100) {
        printf("The integrand is too long.\n");
        free(integrand);
        free(interval);
        break;
      }

      if (strcmp(interval, "[ ; ]") == 0) {
        printf("The interval is not defined.\n");
        free(integrand);
        free(interval);
        break;
      }

      double start, end;
      sscanf(interval, "[%lf ; %lf]", &start, &end);

      if (start == end) {
        printf(
            "Integrating in a [c ; c] interval is defined to be equal to 0.\n");
        free(integrand);
        free(interval);
        break;
      }

      bool minus = false;

      if (start > end) {
        double temp = start; // ∫ [a ; b] f(x) dx = (-1) * ∫ [b ; a] f(x) dx
        start = end;
        end = temp;
        minus = true;
      }

      double step = 0.000001;
      double interval_size = end - start;

      int iters;
      printf("You can modify the accuracy of the numerical integral by setting "
             "the number (x in [1 ; 1 000 000]) of iterations.\n"
             "Enter the number of iterations: ");

      scanf("%d", &iters);
      printf("\n");

      if (iters < 1 || iters > 1000000) {
        printf("Error: The number of iterations must be between 0 and 1 000 000.\n");
        free(integrand);
        free(interval);
        break;
      }

      double subinterval_size = interval_size / iters;
      double integral = 0;

      Node* expression = parse(integrand);
      if (expression == NULL) {
        perror("Error parsing expression.\n");
        free(interval);
        free(integrand);
        free_tree(expression);
        break;
      }

      /*  Using the Upper-sum to calculate the integral,
          where one side of the inscribed rectangle is the supremum of the given
         function, and the other side is the length of the subinterval:*/

      for (double x = start; x < end; x += subinterval_size)
        integral += subinterval_size * find_supremum(expression, x, x + subinterval_size, step);

      if (minus)
        printf("Integral = %.4f\n\n", -1 * integral);
      else
        printf("Integral = %.4f\n\n", integral);

      free(integrand);
      free(interval);
      free_tree(expression);

      break;

    case 2:

      FILE *file = fopen(filename, "r");
      if (file == NULL) {
        perror("Error opening file.\n");
        break;
      }

      char buffer[1024];
      while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
      }

      fclose(file);
      break;

    case 9:
      return 0;
      break;
    }
  } while (num == 1 || num == 2 || num == 9);

  return 0;
}
