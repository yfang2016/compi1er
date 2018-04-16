/*
 * ============================================================================
 *
 *       Filename:  operand.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/12/2018 10:48:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */


#include <stdlib.h>
#include <string.h>

char *REGS8[] = {
    "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"
};

char *REGS16[] = {
    "ax", "cx", "dx", "bx", "sp", "bp", "si", "di"
};

char *SEGS[] = {
    "es", "cs", "ss", "ds"
};

char *MEM[] = {
    "[bx+si]", "[bx+di]", "[bp+si]", "[bp+di]",
    "[si]", "[di]", "[bp]", "[bx]"
};

/* 
* ===  FUNCTION  =============================================================
*         Name:  match
*  Description:  
* ============================================================================
*/
int match(char *regs[], char *pattern, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (!strcmp(regs[i], pattern)) {
            return i;
        }
    }
    return -1;    /* register not listed */
}		/* -----  end of function match ----- */

int memory(char *pattern, int *word)
{
    *word = 0;
    if (strncmp(pattern, "word", 4) == 0) {
        *word = 1;
        pattern += 4;
    } else if (strncmp(pattern, "byte", 4) == 0) {
        pattern += 4;
    }

    return match(MEM, pattern, 8);
}

/* 
* ===  FUNCTION  =============================================================
*         Name:  find_oprand
*  Description:  
*  RETURN : register number
*  index=type of operand (0=REGS8, 1=REGS16, 2=SEGS, 3=immediate)
* ============================================================================
*/
int find_oprand (char *operand, int *index)
{
    int op;
    int word;

    if (strlen(operand) < 1) {  /* operand empty*/
        *index = 0;
		return 0;
    }

    op = match(REGS8, operand, 8);
    if (op >= 0) {
        *index = 1;              /* 8-bit register */
        return op;
    }

    op = match(REGS16, operand, 8);
    if (op >= 0) {
        *index = 2;              /* 16-bit register */
        return op;
    }

    op = match(SEGS, operand, 4);
    if (op >= 0) {              /* segment register */
        *index = 3;
        return op;
    }

    op = memory(operand, &word);
    if (op >= 0) {
        if (word == 1)
            *index = 5;     /* word memory */
        else
            *index = 4;     /* byte memory (default) */
        return op;
    }

    /* convert hexadecimal string to integer as immediate */
    op = strtol(operand, NULL, 16); 
    *index = 10;             /* immediate */
    return op;
}		/* -----  end of function find_oprand  ----- */
