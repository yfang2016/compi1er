/*
 * ============================================================================
 *
 *       Filename:  codefmt.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/15/2018 03:34:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */

typedef struct {
    char strfmt_m[32];          /* instruction format (Mnemonic) */
    char strfmt_a[32];          /* instruction format (Algebraic) */
    int word;                   /* word/byte mark shift in opcode */
                                /* -1 means no such attribute */
    unsigned int ncode;         /* bytes of instruction */
    unsigned int ndata;			/* bytes of data (add 1 byte if word==1) */
    int shift_d, shift_s;       /* source and destination register shift */
                                /* -1 means do not shift (mostly immediate) */
    unsigned char opcode[8];    /* opcode + oprands, max. 8 bytes */
} CODEFMT;  /* code format. */

/*
 * legend:
 * mm : mod. 11=reg.
 * s/S: source register(8bit/16bit)
 * d/D: destination register(8bit/16bit)
 * i/I: immediate(8bit/16bit)
 * w  : word mark. Most 'w' at bit0 but a few instructions marked bit3
 */

CODEFMT iset [] = {   /* instruction set */
    {"mov reg,reg",         /* register <- register */
     "reg=reg",
     0,
     2, 0, 8, 11,
     /* opcode=2 bytes, oprand=1bytes, register index L-shift by 8/11bit */
     0b10001000, 0b000000,
    }, /* 1000100w mmdddsss */  

    {"mov reg,imm.",        /* register <- immediate */
     "reg=imm.",
     3,
     1, 1, 0, -1,
     0b10110000, 0b00000000,
    }, /* 1011wddd iiiiiiii */

    {"adc reg,reg",         /* register += register + CF */
     "reg++=reg",
     0,
     2, 0, 8, 11,
     0b00010000, 0b00000000,
    }, /* 0001000w mmdddsss */
                            
    {"adc reg,imm.",        /* register += immediate + CF */
     "reg++=imm.",
     0,
     2, 1, 8, -1,
     0b10000000, 0b00010000, 0,
    }, /* 1000000w mm010ddd iiiiiiii */
                            
    {"nop",                 /* no operation */
     "nop",
     -1,
     1, 0, -1, -1,
     0b10010000,
    }, /* 10010000 */

};
