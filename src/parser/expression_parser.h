/**
 * @file expression_parser.h
 * @brief Header file for expression parser and evaluator.
 *
 * This header file defines the structures, types, and function prototypes
 * necessary for parsing and evaluating mathematical expressions. It includes
 * support for variables, numbers, functions, and operators.
 *
 * The implementation allows for the creation of an expression tree, parsing
 * of expressions from strings, and evaluation of the expressions with a given
 * variable value.
 */


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


/**
 * @struct Variable
 * @brief Represents a variable in an expression.
 *
 * The Variable structure is used to hold information about a single variable
 * within an expression. Each variable is identified by its name, which is
 * a single character.
 */
typedef struct Variable {
    char name;
} Variable;


/**
 * @struct Number
 * @brief Represents a numeric value in an expression.
 *
 * The Number structure is used to hold a numeric value, which can be
 * either an integer or a floating-point number.
 */
typedef struct Number {
    double value;
} Number;


/**
 * @typedef Func
 * @brief Function pointer type for mathematical functions.
 *
 * This type defines a pointer to a function that takes a double as input
 * and returns a double. It is used to represent mathematical functions
 * that can be applied to numeric values.
 */
typedef double (*Func)(double);


/**
 * @struct Function
 * @brief Represents a mathematical function.
 *
 * The Function structure is used to hold information about a mathematical
 * function, including its name and a pointer to the function implementation.
 */
typedef struct Function {
    char name[FUNCTION_NAME_MAX];
    Func func;
} Function;


/**
 * @struct Operator
 * @brief Represents an operator in an expression.
 *
 * The Operator structure is used to hold information about a single operator,
 * identified by its symbol (e.g., '+', '-', '*', '/').
 */
typedef struct Operator {
    char symbol;
} Operator;


/**
 * @enum NodeType
 * @brief Types of nodes in the expression tree.
 *
 * This enumeration defines the different types of nodes that can exist
 * in the expression tree, including variables, numbers, functions, and operators.
 */
typedef enum NodeType {
    NODE_VARIABLE,
    NODE_NUMBER,
    NODE_FUNCTION,
    NODE_OPERATOR
} NodeType;


/**
 * @union NodeData
 * @brief Union to hold different types of node data.
 *
 * The NodeData union is used to store the data for a node in the expression tree.
 * It can hold either a Variable, Number, Function, or Operator, depending on the
 * type of node.
 */
typedef union NodeData {
    Variable variable;
    Number number;
    Function function;
    Operator operator;
} NodeData;


/**
 * @struct Node
 * @brief Represents a node in the expression tree.
 *
 * The Node structure is used to represent a single node in the expression tree.
 * Each node can be of different types (variable, number, function, operator)
 * and can have left and right children for binary operations.
 */
typedef struct Node {
    NodeType type;
    NodeData data;
    struct Node *left, *right;
} Node;


/**
 * @struct NodeStack
 * @brief Stack structure for managing nodes.
 *
 * The NodeStack structure is used to implement a stack that can hold
 * pointers to Node structures. It is used for parsing expressions and
 * evaluating them in a last-in-first-out (LIFO) manner.
 */
typedef struct NodeStack {
    Node *data[STACK_SIZE];
    int top;
} NodeStack;


/**
 * @struct FunctionEntry
 * @brief Represents a mathematical function entry.
 *
 * The FunctionEntry structure is used to associate a function's name
 * with its corresponding mathematical operation. Each entry includes
 * a string representing the name of the function and a pointer to the
 * function implementation.
 */
typedef struct FunctionEntry {
    const char *name;
    double (*operation)(double);
} FunctionEntry;



double cot(double x);

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
