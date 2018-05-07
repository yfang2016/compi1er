/*
 * ============================================================================
 *
 *       Filename:  syntax.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/28/2017 07:24:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <string.h>
#include <stdio.h>

#include "codefmt.h"
#include "fasm.h"
/* 
* ===  FUNCTION  =============================================================
*         Name:  encode
*  Description:  
* ============================================================================
*/
int encode(int index, OPCODE opcode)
{
    int ncode = iset[index].ncode;
    int ndata = iset[index].ndata;
    int word = 0;
    unsigned short op;

    static int address = 0;  /* instructio address */

    op = *(short *)iset[index].opcode;
    op |= opcode.mod << 14;
    if (iset[index].word >= 0)   /* word/byte is used */
        op |= opcode.word << iset[index].word;

    if (iset[index].shift_d >= 0)
        op |= (opcode.op1 <<= iset[index].shift_d);

    if (iset[index].shift_s >= 0)
        op |= (opcode.op2 <<= iset[index].shift_s);

    printf("%08X ", address);
    while (ncode-- > 0) {
        printf("%02X ", (unsigned char)(op));
        op >>= 8;
        address++;
    }

    if (ndata > 0)       /* source operand is immediate */
        ndata += opcode.word;

    if (iset[index].shift_d < 0)    /* the first operand is a number */
        op = opcode.op1;
    else
        op = opcode.op2;
    while(ndata-- > 0) {
        printf("%02X ", (unsigned char)(op));
        op >>= 8;
        address++;
    }

    return 0;
}		/* -----  end of function encode  ----- */

/* 
* ===  FUNCTION  =============================================================
*         Name:  syntax
*  Description:  
* ============================================================================
*/
int syntax (char *string, OPCODE opcode)
{
    int i, item;
	
    item = sizeof(iset) / sizeof(CODEFMT);
    for(i = 0; i < item ;i++) {
        if (!strcmp(string, iset[i].strfmt_m)) {
            encode(i, opcode);
            return 0;
        }
    }

    return E_EXIST;         /* instruction not found */
}		/* -----  end of function syntax  ----- */
