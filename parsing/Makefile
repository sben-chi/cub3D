NAME = cub3D
NAME_B = cub3D_bonus
CC = gcc
CFLAGS		= -lm -lmlx -lbsd -lXext -lX11 -fsanitize=address -g -L /usr/local/lib -I /usr/local/include
F =  init_data.c parsing_utils.c gnl.c main.c parsing.c parsing_utils2.c

OFILES = ${F:.c=.o}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES)  -o $(NAME) $(CFLAGS)
re: fclean all

fclean:	clean
	rm -f $(NAME)
clean:
	rm -f $(OFILES)
