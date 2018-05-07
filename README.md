# compi1er
mini x86 compiler exercise.

Translate x86 assembly instructions into machine code.
The compiler will translate at least 'MOV' and 'ADD' instructions.
The operand may be registers and immediates.

For example:

    MOV  AX, 0x1234 -> B8 34 12 (or 10111000 00110100 00010010)
    MOV  CL, DL     -> 88 D1    (or 10001000 11010001)
    or:
    MOV  CL, DL     -> 8A CA    (or 10001010 11001010)
    ADD  SI, AX     -> 01 C6    (or 00000001 11000110)

The default syntax is INTEL-style mnemonic assembly language.
But other syntax is also acceptable such as self-defined algebraic
assembly language:

    'AX = 0x1234' instead of 'MOV AX, 0x1234'
    'BX += CX'    instead of 'ADD BX, CX'

compile:
    gcc -o fasm fasm.c  format.c  operand.c  parser.c  syntax.c

The program read instructions line by line, or with input redirection:
    ./fasm < test.asm


BUG issues:
    1. Syntaxes are not intensively checked. Some individual operands
    are illegal, such as POP CS.
    2. Data or immediates must be in hexadecimal and without prefix or suffix,
    without any verification.
    3. Prefixes such as segment override or repeat may mismatch the following
    instruction.
    4. Lack of direct memory addressing and memory displacement
