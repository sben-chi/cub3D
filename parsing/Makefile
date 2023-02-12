NAME = cub3D
NAME_B = cub3D_bonus
CC = gcc
CFLAGS		= -fsanitize=address -g -lm -lmlx -lbsd -lXext -lX11 -I /usr/local/include
LDFLAGS		= -L /usr/local/lib 
F =  init_data.c parsing_utils.c gnl.c main.c parsing.c parsing_utils2.c

OFILES = ${F:.c=.o}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES)  -o $(NAME) $(CFLAGS) $(LDFLAGS)
re: fclean all

fclean:	clean
	rm -f $(NAME)
clean:
	rm -f $(OFILES)
