#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct token {
    int token;
    int intv;
};

// Token types
enum {
    T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

struct ASTnode {
    int op;
    struct ASTnode *left;
    struct ASTnode *right;
    int intv;
};

// ASTnode types
// A_INTLIT ASTnode has no left and right
enum {
    A_ADD, A_SUBTRACT, A_MUTIPLY, A_DIVIDE, A_INTLIT
};