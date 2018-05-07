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

    {"mov reg,mem",        /* register <- [memory] */
     "reg=mem",
     0,
     2, 0, 8, 11,
     0b10001010, 0b00000000,
    }, /* 1000101w mmdddsss */

    {"mov mem,reg",        /* [memory] <- register */
     "mem=reg",
     0,
     2, 0, 8, 11,
     0b10001000, 0b00000000,
    }, /* 1000100w mmdddsss */

    {"mov mem,imm.",        /* [memory] <- immediate */
     "mem=imm.",
     0,
     2, 1, 8, -1,
     0b11000110, 0b00000000,
    }, /* 1100011w mm000ddd iiiiiiii */

    {"mov reg,imm.",        /* register <- immediate */
     "reg=imm.",
     3,
     1, 1, 0, -1,
     0b10110000, 0b00000000,
    }, /* 1011wddd iiiiiiii */

    {"mov reg,seg",         /* register <- segment register */
     "reg=seg",
     -1,
     2, 0, 11, 8,
     0b10001100, 0b00000000,
    }, /* 10001100 mm0SSDDD */

    {"mov seg,reg",         /* segment register -> register */
     "seg=reg",
     -1,
     2, 0, 11, 8,
     0b10001110,0b00000000,
    }, /* 10001110 mm0DDSSS */

    {"add reg,reg",         /* register += register */
     "reg+=reg",
     0,
     2, 0, 8, 11,
     0b00000000, 0b00000000,
    }, /* 0000000w mmdddsss */

    {"add reg,imm.",        /* register += immediate */
     "reg+=imm.",
     0,
     2, 1, 8, -1,
     0b10000000, 0b00000000, 0,
    }, /* 1000000w mm000ddd iiiiiiii */

	{"push reg",           /* push register */
     "push reg",
     0,
     1, 0, 0, -1,
     0b01010000,
	}, /* 01010DDD. actually, this should be considered as source register */
    /* Also, this instruction can be coded as "11111111 mod 110 r/m" */

	{"push seg",            /* push segment register */
     "push seg",
     -1,
     1, 0, 3, -1,
     0b00000110,
	}, /* 000DD110 */

	{"pop reg",             /* pop register */
     "pop reg",
     -1,
     1, 0, 0, -1,
     0b01011000,
	}, /* 01011DDD */
    /* Also, this instruction can be coded as "10001111 mod 000 r/m" */

	{"pop seg",             /* pop segment register */
     "pop seg",
     -1,
     1, 0, 3, -1,
     0b00000111,
	}, /* 000DD111 */

	{"xlat",                /* translate byte to AL */
     "xlat",
     -1,
     1, 0, -1, -1,
     0b11010111,
	}, /* 11010111 */

	{"lahf",                /* load AH with flags */
     "lahf",
     -1,
     1, 0, -1, -1,
     0b10011111,
	}, /* 10011111 */

	{"sahf",                /* store AH into flags */
     "sahf",
     -1,
     1, 0, -1, -1,
     0b10011110,
	}, /* 10011110 */

	{"pushf",                /* push flags */
     "pushf",
     -1,
     1, 0, -1, -1,
     0b10011100,
	}, /* 10011100 */

	{"popf",                 /* pop flags */
     "popf",
     -1,
     1, 0, -1, -1,
     0b10011101,
	}, /* 10011101 */

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
                            
    {"inc reg",             /* register += 1 */
     "reg++",
     0,
     2, 0, 8, -1,
     0b11111110, 0b00000000,
    }, /* 1111111w mm000ddd */

    {"dec reg",             /* register -= 1 */
     "reg--",
     0,
     2, 0, 8, -1,
     0b11111110, 0b00001000,
    }, /* 1111111w mm001ddd */

    {"sub reg,reg",         /* register -= register */
     "reg-=reg",
     0,
     2, 0, 8, 11,
     0b00101001, 0b00000000,
    }, /* 0010100w mmDDDSSS */

    {"sub reg,imm.",        /* register -= immediate */
     "reg-=imm.",
     0,
     2, 1, 8, -1,
     0b10000000, 0b00101000, 0,
    }, /* 1000000w mm101ddd iiiiiiii */
                            
    {"sbb reg,reg",         /* register -= register + CF */
     "reg--=reg",
     0,
     2, 0, 8, 11,
     0b00011000, 0b00000000,
    }, /* 0001100w mmdddsss */

    {"sbb reg,imm.",        /* register -= immediate + CF */
     "reg--=imm.",
     0,
     2, 1, 8, -1,
     0b10000000, 0b00011000, 0,
    }, /* 1000000w mm011ddd iiiiiiii */

    {"int imm.",            /* interrupt */
     "int imm.",
     -1,
     1, 1, -1, -1,
     0b11001101, 0b00000000,
    }, /* 11001101 iiiiiiii */

    {"nop",                 /* no operation */
     "nop",
     -1,
     1, 0, -1, -1,
     0b10010000,
    }, /* 10010000 */

    {"seg seg",             /* segment override prefix */
     "seg=seg",
     -1,
     1, 0, 11, -1,
     0b00100110,
    }, /* 001RR110 */

};
