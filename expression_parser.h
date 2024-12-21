#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>


#define STACK_SIZE 50
#define FUNCTION_NAME_MAX 10
#define OPERATORS "+-*/^" // Supported operators
#define NEW_NODE(TYPE) ((Node *)malloc(sizeof(Node)))


typedef struct Variable {
    char name;
} Variable;


typedef struct Number {
    double value;
} Number;


typedef double (*Func)(double);


typedef struct Function {
    char name[FUNCTION_NAME_MAX];
    Func func;
} Function;


typedef struct Operator {
    char symbol;
} Operator;


typedef enum NodeType {
    NODE_VARIABLE,
    NODE_NUMBER,
    NODE_FUNCTION,
    NODE_OPERATOR
} NodeType;


typedef union NodeData {
    Variable variable;
    Number number;
    Function function;
    Operator operator;
} NodeData;


typedef struct Node {
    NodeType type;
    NodeData data;
    struct Node *left, *right;
} Node;


typedef struct NodeStack {
    Node *data[STACK_SIZE];
    int top;
} NodeStack;


typedef struct FunctionEntry {
    const char *name;
    double (*operation)(double);
} FunctionEntry;



double cot(const double x);

void push(NodeStack *stack, Node *node);

Node *pop(NodeStack *stack);

Node *create_variable(char name);

Node *create_number(double value);

Node *create_function(const char *name, Func func);

Node *create_operator(char symbol);

Node *parse(char *expression);

double evaluate(Node *head, double x);

void free_tree(Node *node);


#endif /* EXPRESSION_PARSER_H */
