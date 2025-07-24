/**
 * @file expression_parser.c
 * @brief Implementation of functions for parsing and evaluating mathematical expressions.
 *
 * This file contains the implementation of functions to parse mathematical expressions in Reverse Polish Notation (RPN),
 * build an abstract syntax tree (AST), evaluate the expression for a given variable value, and manage memory for the nodes.
 */


#include "expression_parser.h"
#include "debugmalloc.h"


/**
 * @brief A constant array containing mathematical functions and their corresponding names.
 *
 * This array maps function names, represented as strings, to their implementation in the code.
 * It includes common mathematical functions such as sine, cosine, tangent, cotangent, natural logarithm, and exponential.
 *
 * The available functions are:
 * - "sin": Computes the sine of a given angle (in radians).
 * - "cos": Computes the cosine of a given angle (in radians).
 * - "tg": Computes the tangent of a given angle (in radians).
 * - "ctg": Computes the cotangent of a given angle (in radians).
 * - "ln": Computes the natural logarithm of a given number.
 * - "exp": Computes the exponential (e^x) of a given number.
 */
const FunctionEntry FUNCTIONS[] = {
    {"sin", sin}, {"cos", cos}, {"tg", tan}, {"ctg", cot},
    {"ln", log}, {"exp", exp}
};


/**
 * Computes the cotangent of a given angle in radians.
 *
 * @param x The angle in radians for which the cotangent is to be computed.
 * @return The cotangent of the given angle.
 */
double cot(const double x) {
    return 1 / tan(x);
}


/**
 * Pushes a node onto a stack.
 *
 * @param stack The stack where the node will be pushed. Must be a valid pointer to a NodeStack structure.
 * @param node The node to push onto the stack. Must be a valid pointer to a Node structure.
 *
 * If the stack is full (i.e., the number of elements exceeds `STACK_SIZE - 1`), an error message is printed,
 * and the program exits with an error state.
 */
void push(NodeStack *stack, Node *node) {
    if (stack->top == STACK_SIZE - 1) {
        fprintf(stderr, "Error: Stack overflow.\n");
        exit(1);
    }
    stack->data[++stack->top] = node;
}


/**
 * @brief Removes and returns the top element of the stack.
 *
 * This function retrieves the element from the top of the stack while decreasing
 * the stack's top index. If the stack is empty, it reports an error and terminates
 * the program.
 *
 * @param stack A pointer to the NodeStack structure representing the stack.
 *
 * @return The pointer to the Node located at the top of the stack.
 *
 * @note Exits the program with an error message if the stack is empty
 *       (stack underflow condition).
 */
Node *pop(NodeStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Stack underflow.\n");
        exit(1);
    }
    return stack->data[stack->top--];
}


/**
 * @brief Initializes a node with the given type and sets its children to null.
 *
 * @param node A pointer to the Node structure to initialize.
 * @param type The type of the node to assign.
 */
void initialize_node(Node *node, const NodeType type) {
    node->type = type;
    node->left = nullptr;
    node->right = nullptr;
}


/**
 * @brief Creates a new variable node with the given name.
 *
 * This function allocates memory for a new `Node` of type `NODE_VARIABLE`,
 * initializes its properties, and sets the variable's name.
 *
 * @param name The name of the variable to assign to the created node.
 *
 * @return A pointer to the newly created variable node. Exits the program
 *         on memory allocation failure.
 */
Node *create_variable(const char name) {
    Node *node = NEW_NODE(NODE_VARIABLE);
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for variable node.\n");
        exit(1);
    }
    initialize_node(node, NODE_VARIABLE);
    node->data.variable.name = name;
    return node;
}


/**
 * Creates a new number node with the specified value.
 *
 * @param value The numeric value to be assigned to the node.
 * @return A pointer to the created number node. If memory allocation fails,
 *         the program will terminate with an error message.
 */
Node *create_number(const double value) {
    Node *node = NEW_NODE(NODE_NUMBER);
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for number node.\n");
        exit(1);
    }
    initialize_node(node, NODE_NUMBER);
    node->data.number.value = value;
    return node;
}


/**
 * Creates a function node with the given name and function pointer.
 *
 * @param name The name of the function. It should not exceed FUNCTION_NAME_MAX length.
 * @param func The function pointer associated with the function node.
 * @return A pointer to the newly created function node. If memory allocation fails,
 *         the program exits with an error.
 */
Node *create_function(const char *name, const Func func) {
    Node *node = NEW_NODE(NODE_FUNCTION);

    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for function node.\n");
        exit(1);
    }

    initialize_node(node, NODE_FUNCTION);
    strncpy(node->data.function.name, name, FUNCTION_NAME_MAX);
    node->data.function.func = func;

    return node;
}


/**
 * Creates a new operator node in an expression tree.
 *
 * @param symbol The symbol representing the operator (e.g., '+', '-', '*', '/').
 * @return Pointer to the newly created operator node.
 */
Node *create_operator(const char symbol) {
    Node *node = NEW_NODE(NODE_OPERATOR);

    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for operator node.\n");
        exit(1);
    }

    initialize_node(node, NODE_OPERATOR);
    node->data.operator.symbol = symbol;

    return node;
}


/**
 * Finds a function by its name from a predefined list of functions.
 *
 * Iterates through a list of predefined functions and attempts to match
 * the given name with the name of one of the functions. If a match is found,
 * returns the corresponding function operation; otherwise, returns NULL.
 *
 * @param name The name of the function to search for. Must be a null-terminated string.
 * @return A pointer to the function corresponding to the given name if found,
 *         or NULL if no matching function is found.
 */
Func find_function(const char *name) {
    constexpr size_t function_count = sizeof(FUNCTIONS) / sizeof(FUNCTIONS[0]);

    for (size_t i = 0; i < function_count; i++)
        if (strcmp(name, FUNCTIONS[i].name) == 0)
            return FUNCTIONS[i].operation;

    return nullptr;
}


/**
 * Parses a mathematical expression in Reverse Polish Notation (RPN) and constructs
 * the corresponding abstract syntax tree (AST).
 *
 * The function processes tokens from the input expression and determines their type
 * (number, variable, operator, or function). It then builds nodes for the AST
 * accordingly and uses a stack to manage intermediate nodes during construction.
 *
 * @param expression A null-terminated string containing the mathematical expression
 * in Reverse Polish Notation (RPN). The tokens within the expression should be
 * separated by spaces.
 * @return A pointer to the root node of the abstract syntax tree (AST) representing
 * the parsed expression. Returns NULL if an error occurs during parsing.
 */
Node *parse(char *expression) {
    NodeStack stack = {.top = -1};
    char *token = strtok(expression, " ");

    while (token != NULL) {
        if (strcmp(token, "x") == 0) {
            push(&stack, create_variable('x'));
        } else if (strpbrk(OPERATORS, token) != NULL) {
            Node *node = create_operator(token[0]);
            node->right = pop(&stack);
            node->left = pop(&stack);
            push(&stack, node);
        } else {
            Func operation = find_function(token);
            if (operation != NULL) {
                Node *node = create_function(token, operation);
                node->left = pop(&stack);
                push(&stack, node);
            } else {
                char *endptr;
                double value = strtod(token, &endptr);
                if (*endptr != '\0') {
                    fprintf(stderr, "Error: Invalid token '%s' in expression.\n", token);
                    exit(1);
                }
                push(&stack, create_number(value));
            }
        }
        token = strtok(nullptr, " ");
    }

    return stack.data[0];
}


/**
 * Evaluates the value of an expression represented by a syntax tree for a given variable value.
 *
 * The `evaluate` function traverses the syntax tree of the expression, computes the result
 * based on the type of the node, and returns the evaluated value. It supports variables,
 * numerical constants, operators, and functions.
 *
 * @param head Pointer to the root node of the syntax tree representing the expression.
 * @param x The value of the variable in the expression.
 * @return The evaluated result of the expression for the given value of x.
 */
double evaluate(Node *head, const double x) {
    if (!head) return 0.0;

    switch (head->type) {
        case NODE_VARIABLE:
            return x;

        case NODE_NUMBER:
            return head->data.number.value;

        case NODE_FUNCTION:
            return head->data.function.func(evaluate(head->left, x));

        case NODE_OPERATOR:
            switch (head->data.operator.symbol) {
                case '+':
                    return evaluate(head->left, x) + evaluate(head->right, x);
                case '-':
                    return evaluate(head->left, x) - evaluate(head->right, x);
                case '*':
                    return evaluate(head->left, x) * evaluate(head->right, x);
                case '/':
                    return evaluate(head->left, x) / evaluate(head->right, x);
                case '^':
                    return pow(evaluate(head->left, x), evaluate(head->right, x));
                default:
                    fprintf(stderr, "Error: Unknown operator '%c'.\n", head->data.operator.symbol);
                    exit(1);
            }

        default:
            fprintf(stderr, "Error: Unknown node type.\n");
            exit(1);
    }
}
