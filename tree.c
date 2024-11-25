/**
 * tree.c
 * functions to build ASTs
 */

#include "defs.h"
#include "decl.h"

struct ASTnode* mk_astnode(int op, struct ASTnode *left, struct ASTnode *right,
                          int intv) {
    struct ASTnode *n;
    n = (struct ASTnode*) malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fprintf(stderr, "Unable to malloc a new astnode \n");
        exit(1);
    }
    n->op = op;
    n->left = left;
    n->right = right;
    n->intv = intv;
    return n;
}

// Make a leaf node with no child
struct ASTnode* mk_astleaf(int op, int intv) {
    return mk_astnode(op, NULL, NULL, intv);
}

// Make a node with only one child
struct ASTnode* mk_astunary(int op, struct ASTnode *l, int intv) {
    return mk_astnode(op, l, NULL, intv);
}

