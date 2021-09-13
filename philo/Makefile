SRC	=		main.c\
			init.c\
			pthread_actions.c\
			time.c\
			utils.c

OBJ		= 	$(SRC:.c=.o)
NAME	=	philo
CFLAGS	=	-Wall -Wextra -Werror
CC		=	gcc
RM		=	rm -f

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
		rm -rf $(OBJ)
fclean: clean
		rm -rf $(NAME)
re:	fclean all

.PHONY: all clean fclean re