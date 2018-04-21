/*
 * ============================================================================
 *
 *       Filename:  parser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/21/2018 10:49:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <string.h>

#include "fasm.h"

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  parser
 *  Description:  
 *     parser code
 * ===========================================================================
 */
int parser(char *line, char *buf, OPCODE *opcode)
{
    char *p = line;
    char operand[128];
    int n = 0, n1;
    int res;
    int index;

    opcode->word = 0;           /* set default memory size to BYTE */

    while (*p) {
        if (*p++ == ' ')
            break;
        n++;
    }/* find first WS */
    if (n == 0) {
        return -1;    // empty line
    }

    strncpy(buf, line, n);  /* get opcode */
    buf[n] = '\0';
    n1 = n;
    while (*p) {
        if(*p++ == ',')
            break;
        n++;
    }/* find destination operand */

    strncpy(operand, &line[n1+1], n - n1);  /* skip WS */
    operand[n - n1] = '\0';

    opcode->op1 = find_oprand(operand, &index);
    /* destination operand can be regster, seg-register */
    switch(index) {
    case 1:
        strcat(buf, " reg");
        opcode->mod = 0b11;
        break;
    case 2:
        strcat(buf, " reg");
        opcode->word = 1;
        opcode->mod = 0b11;
        break;
    case 3:
        strcat(buf, " seg");
        opcode->word = 1;
        break;
    case 4:
        strcat(buf, " mem");
        opcode->mod = 0b00;
        break;
    case 5:
        strcat(buf, " mem");
        opcode->word = 1;
        opcode->mod = 0b00;
        break;
    case 10:
        strcat(buf, " imm.");
		break;
    default:
        return 0;    /* No operand1 */
    }

    opcode->op2 = find_oprand(p, &index); /* match source operand */
    /* source operand can be register,seg-register, immediate or EMPTY */
    switch(index) {
    case 1:
        strcat(buf, ",reg");
        if (opcode->word == 1)
            opcode->errorType |= E_MISMATCH;
        break;
    case 2:
        strcat(buf, ",reg");
        opcode->word = 1;
        break;
    case 3:
        strcat(buf, ",seg");
        if (opcode->word == 0)
            opcode->errorType |= E_MISMATCH;
        break;
    case 4:
    case 5:
        strcat(buf, ",mem");
        opcode->mod = 0b00;
        break;
    case 10:
        strcat(buf, ",imm.");
		break;
    default:
        return 0;     /* illegal oprand2 */
    }

	return 0;
}		/* -----  end of function parser  ----- */
