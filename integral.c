#include "integral.h"
#include "debugmalloc.h"

// Reads the last two lines of a txt file
void read_file(const char *filename, char **last, char **second_last){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        perror("Error opening file");
        return;
    }

    char *last_line = NULL;
    char *second_last_line = NULL;
    size_t size = INITIAL_SIZE;

    last_line = (char *)malloc(size * sizeof(char)+1);
    second_last_line = (char *)malloc(size * sizeof(char)+1);

    if (last_line == NULL || second_last_line == NULL){
        perror("Did not manage to allocate memory");
        return;}

    last_line[0] = '\0';
    second_last_line[0] = '\0';

    char *temp;

    while (fgets(last_line, size, file) != NULL){
        if (last_line[strlen(last_line) - 1] == '\n'){
            temp = last_line;
            last_line = second_last_line;
            second_last_line = temp;

        } else {
            size *= 2;
            last_line = (char *)realloc(last_line, size * sizeof(char));
            second_last_line = (char *)realloc(second_last_line, size * sizeof(char));

            if (last_line == NULL || second_last_line == NULL){
                perror("Did not manage to allocate memory");
                return;}
        }
    }

    *last = last_line;
    *second_last = second_last_line;

    fclose(file);
}

// Removes leading and trailing spaces of a string
void remove_spaces(char *str){
    int start = 0, end = strlen(str) - 1;
    while (isspace(str[start]))
        start++;
    while (end > start && isspace(str[end])) 
        end--;

    int i, j;
    for (i = start, j = 0; i <= end; i++, j++) 
        str[j] = str[i];
    str[j] = '\0';
}

double find_supremum(Node* expr, double start, double end, double step) {
  if (expr == NULL){printf("Error parsing expression.\n"); exit(1);}
  double x = start;
  double supremum = evaluate(expr, x);

  while (x <= end) {
    double value = evaluate(expr, x);
    if (value > supremum)
      supremum = value;
    x += step;}

  return supremum;
}