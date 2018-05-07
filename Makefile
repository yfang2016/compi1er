CC 		= gcc
SRC 	= format.c parser.c operand.c syntax.c fasm.c codefmt.h

fasm: $(SRC)
	$(CC) -o $@ $^
