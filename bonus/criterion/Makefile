##
## EPITECH PROJECT, 2023
## undefined
## File description:
## Makefile to compile files with the lib.
## Makefile
##

CC	=	gcc

PATH_TO_SRC	=	../../src/

SRC	=	$(PATH_TO_SRC)move.c	\
		tests/test_cycle_nb.c	\
		tests/test_cycle_coords.c

OBJ	=	$(SRC:%.c=%.o)

CFLAGS	=	-g3 -W -Wall

LDFLAGS	=	--coverage -lcriterion

EXEC	=	unit_tests

tests_run:	$(EXEC)

$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o:	%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(EXEC)

re:	fclean tests_run

.PHONY:	all clean fclean re
