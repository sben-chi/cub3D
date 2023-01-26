NAME = cub
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
CC = gcc
F =  init_data.c parsing_utils.c gnl.c main.c parsing.c parsing_utils2.c

OFILES = ${F:.c=.o}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
re: fclean all

fclean:	clean
	rm -f $(NAME)
clean:
	rm -f $(OFILES)
