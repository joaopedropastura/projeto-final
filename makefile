
SCRCS =	game.c \
		main.c \

NAME = game.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck

OBJS = $(SRCS:.c=.o)

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

