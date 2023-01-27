NAME = cub
CFLAGS =  -Imlx#-fsanitize=address -g
LFLAGS = -lmlx -framework OpenGL -framework AppKit
CC = gcc
F =  init_data.c parsing_utils.c gnl.c main.c parsing.c parsing_utils2.c

OFILES = ${F:.c=.o}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) $(LFLAGS) -o $(NAME) 
re: fclean all

fclean:	clean
	rm -f $(NAME)
clean:
	rm -f $(OFILES)
