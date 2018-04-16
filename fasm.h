/*
 * ============================================================================
 *
 *       Filename:  fasm.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2018 10:55:16 AM
 *       Revision:  none
 *       Compiler: 
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

#ifndef _FASM_H
#define _FASM_H

#define     E_FOUDN     1   /* mnemonic not found */
#define     E_MISMATCH  2   /* operand not match */
#define     E_SIZE      4   /* operand size illegal */
#define     E_EXIST     8   /* instruction not exist */

typedef struct {
    int op1;        /* code of first operand(destination) */
    int op2;        /* code second operand(source) */
    int word;       /* word or byte */
    int mod;	    /* register or memory */
    int data;	    /* data in instruction (if present) */
    int errorType;  /* error type */
} OPCODE;

/* legend:
 * mov ax,[bx]:
 *     op1=0, op2=7, word=1, mod=10B
 * mov byte[bp+si+1234],56:
 *     op1=2, op2=56H, word=0, mod=10B, data=1234H
 */

#endif
