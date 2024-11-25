#include "defs.h"
#include "data.h"
#include "decl.h"

// return a AST node representing primary factor
static struct ASTnode *primary() {
    struct ASTnode *n;
    switch (Token.token) {
    case T_INTLIT:
        n = mk_astleaf(A_INTLIT, Token.intv);
        scan(&Token);
        break;
    default:
        fprintf(stderr, "Unsupported token type %d in ast primary on line %d\n",
                Token.token, Line);
        exit(1);
    }
    return n;
}

// Convert a token into AST op
int artith_op(int t) {
    switch (t) {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUBTRACT;
    case T_STAR:
        return A_MUTIPLY;
    case T_SLASH:
        return A_DIVIDE;
    default:
        fprintf(stderr, "Unknowen token %d occurd in artith_op on line %d\n",
                t, Line);
        exit(1);
    }
}

struct ASTnode *multipicative_expr() {
    struct ASTnode *left, *right;
    int t_type;
    printf("mul:%d\n", Token.token);
    t_type = Token.token;
    if(t_type == T_EOF) 
        return left;
    left = primary();
    // grab next token type
    while(t_type == T_STAR || t_type == T_SLASH) {
        // get next integer
        scan(&Token);
        right = primary();
        left = mk_astnode(artith_op(t_type), left, right, 0);
        if(t_type == T_EOF)
            break;
    }
    return left;
}

struct ASTnode *additive_expr() {
    struct ASTnode *left, *right;
    int t_type;
    // get for higher precedence
    left = multipicative_expr();
    t_type = Token.token;    
    if(t_type == T_EOF) 
        return left;
    while(1) {
        scan(&Token);
        printf("add: %d\n", Token.token);
        right = multipicative_expr();
        left = mk_astnode(artith_op(t_type), left, right, 0);
        t_type = Token.token;
        if(t_type == T_EOF)
            break;
    }
    return left;
}

// Operator precedence EOF PLUS MINUS STAR SLASH INTLIT
static int OpPrec[] = {0, 10, 10, 20, 20, 0};

static int op_prec(int t_type) {
    int prec = OpPrec[t_type];
    if(prec == 0) {
        // Hits when not a operator
        fprintf(stderr, "syntax error on line %d", Line);
        exit(1);
    }
    return prec;
}

/**
 * Build ast tree from top to bottom
 * high prec operators is in the bottom
 * high prec will 
 */
struct ASTnode *binexpr(int ptp) {
    struct ASTnode *n, *left, *right;
    int t_type;
    left = primary();
    t_type = Token.token;
    if(Token.token == T_EOF)
        return left;
    while(op_prec(t_type) > ptp) {
        scan(&Token); // get next int literal
        right = binexpr(op_prec(t_type));
        left = mk_astnode(artith_op(t_type), left, right, 0);
        t_type = Token.token;
        if(t_type == T_EOF)
            return left;
    }
    return left;
}

