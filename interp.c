// Interpret the Tree
#include"defs.h"
#include"decl.h"

int interpretTree(struct ASTnode *n) {
    int leftVal, rightVal;
    if(n->left)
        leftVal = interpretTree(n->left);
    if(n->right)
        rightVal = interpretTree(n->right);
    
    switch(n->op) {
        case A_ADD:
            return (leftVal + rightVal);
            break;
        case A_SUBTRACT:
            return (leftVal - rightVal);
            break;
        case A_MUTIPLY:
            return (leftVal * rightVal);
            break;
        case A_DIVIDE:
            return (leftVal / rightVal);
            break;
        case A_INTLIT:
            return (n->intv);
            break;
        default:
            fprintf(stderr, "Unknow operator %d\n", n->op);
            exit(1);
    }
}
