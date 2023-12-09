#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"

static void usage(char *prog)
{
    fprintf(stderr, "Usage: %s infile\n", prog);
    exit(0);
}

static void init()
{
    Line = 1;
    Putback = '\n';
}

static void scan_file()
{
    struct token T;
    while (scan(&T))
    {
        printf("Find A token\n");
    }
}

void main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);
    }
    init();
    printf("A compiler written by C");
    if ((Infile = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(0);
    }
    scan_file();
    exit(0);
}