##
## EPITECH PROJECT, 2018
## k
## File description:
## k
##

SRC	= 	src/main.c\
		src/init.c\
		src/sem.c\
		src/player2.c \
		src/player.c\
		src/display.c\
		src/display2.c

OBJ	= $(SRC:.c=.o)

NAME	= lemipc

CC	= gcc

CFLAGS	+= -Wall -Wextra -W -I./inc/

INC +=

LDFLAGS	= -lm

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

ipcs:
	@python scripts/rmipcs

re:	fclean all

.PHONY:	all clean fclean re
