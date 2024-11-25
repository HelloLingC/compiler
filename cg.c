#include "defs.h"
#include "data.h"
#include "decl.h"

static int free_reg[4];
static char *reg_list[4] = {"%r8", "%r9", "%r10", "%r11"};

/**
 * Alloc a free register
 */
static int alloc_register() {
    for(int i = 0; i < 4; i++) {
        if(free_reg[i]) {
            free_reg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Error: Out of registers!");
    exit(1);
}

static void free_register(int r) {
    if(free_reg[r] == 0) {
        fprintf(stderr, "Error: Trying to free a register already freed");
        exit(1);
    }
    free_reg[r] = 1;
}

static void free_all_registers() {

}

void cgpreamble()
{
  freeall_registers();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t.type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n",
  Outfile);
}

void cgpostamble()
{
  fputs(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n",
  Outfile);
}
/**
 * Load a integer literal into a free register
 */
int cgload(int v) {
    int r = alloc_register();
    fprintf(Outfile, "\tmovq\t$%d, %s\n", v, reg_list[r]);
    return r;
}

int cgadd(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", r1, r2);
    free_register(r1);
    return r2;
}

int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", r1, r2);
    free_register(r2);
    return r1;
}

int cgmul(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", r1, r2);
    free_register(r2);
    return r1;
}

int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", r1, r2);
    free_register(r2);
    return r1;
}