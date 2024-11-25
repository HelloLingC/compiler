
int scan(struct token *t);
struct ASTnode *binexpr();
struct ASTnode *additive_expr();
int interpretTree(struct ASTnode *n);

struct ASTnode* mk_astleaf(int op, int intv);
struct ASTnode* mk_astnode(int op, struct ASTnode *left, struct ASTnode *right,
                          int intv);