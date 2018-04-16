/*
 * ============================================================================
 *
 *       Filename:  fasm.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2018 02:28:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fasm.h"

/* 
* ===  FUNCTION  =============================================================
*         Name:  main
*  Description:  
* ============================================================================
*/
int main (int argc, char *argv[])
{
    char *aline, code[128];
    size_t n;
    ssize_t read;
    OPCODE opcode;

    aline = malloc(256);
    for(;;) {
        opcode.errorType = 0;			/* reset error type */
        n = 256;
        read = getline(&aline, &n, stdin);
        if (read == -1)
            break;
        /* "  MoV   AX , [bX] ; comment" -> "mov ax,[bx]" */
        format(code, aline);
        printf("%-20s  ", code);
        /* "mov ax,[bx]" -> "mov reg,mem", oprand1=0,oprand2=7,mod=10 */
        parser(code, aline, &opcode);
        opcode.errorType |= syntax(aline, opcode);

        /* errorProcessing(opcode.errorType); */

        printf("\n");
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
