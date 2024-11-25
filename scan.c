#include "defs.h"
#include "data.h"
#include "decl.h"

/**
 * @brief Get the position of a char in a string
 *
 * @return int
 */
static int chrpos(char *s, int c) {
    char *p;
    p = strchr(s, c);
    return (p ? p - s : -1);
}

static int next(void) {
    int c;
    // If Putback exists, use Putback instead of getting next c in input
    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }
    c = fgetc(Infile);
    if ('\n' == c)
        Line++;
    return c;
}

//
static void putback(int c) { Putback = c; }

// Skip whitespace, newline, etc
static int skip(void) {
    int c;
    c = next();
    while (' ' == c || '\n' == c || '\r' == c || '\t' == c) {
        c = next();
    }
    return c;
}

/**
 * @brief Scan from a vaild digit char return the integer literal
 *
 * @return int the integer literal
 */
static int scan_int(int c) {
    int k, val = 0;
    while ((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }
    // Hit a non-int char
    putback(c);
    return val;
}

/**
 * @brief Scan a token and return the next token
 *
 * @return int 0 or 1 which means whether the next token is vaild
 */
int scan(struct token *t) {
    int c;
    // Go the next
    c = skip();
    switch (c) {
    case EOF:
        t->token = T_EOF;
        return 0;
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c)) {
            // A vaild digit
            t->token = T_INTLIT;
            t->intv = scan_int(c);
            break;
        }
        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }
    return 1;
}