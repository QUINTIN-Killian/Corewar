##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile to compile files with the lib.
## Makefile
##

CC	=	gcc

SRC	=	src/champions.c	\
		src/endian.c	\
		src/error_handling.c	\
		src/extraction.c	\
		src/flags_recognition.c	\
		src/functions.c	\
		src/instructions.c	\
		src/instructions2.c	\
		src/main.c	\
		src/main_loop.c	\
		src/op.c

OBJ	=	$(SRC:src/%.c=bin/%.o)

CFLAGS	=	-g3 -W -Wall

LDFLAGS	=	-L. -lmy

EXEC	=	corewar

H_NAME	=	include/my.h	\
			include/corewar.h

LIB_NAME	=	libmy.a

all:	compile_lib $(EXEC)

compile_lib:
	make -C lib/my

$(EXEC):	$(H_NAME) $(LIB_NAME) $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

bin/%.o:	src/%.c $(H_NAME) $(LIB_NAME)
	@mkdir -p bin
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)
	@rm -rf bin
	make clean -C lib/my

fclean:	clean
	rm -f $(EXEC)
	make fclean -C lib/my

re:	fclean all

.PHONY:	all compile_lib clean fclean re
