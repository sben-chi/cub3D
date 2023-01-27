NAME = cub
CFLAGS =  -I/usr/include -Imlx_linux -O3#-fsanitize=address -g
CC = gcc
F =  init_data.c parsing_utils.c gnl.c main.c parsing.c parsing_utils2.c

OFILES = ${F:.c=.o}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) 
re: fclean all

fclean:	clean
	rm -f $(NAME)
clean:
	rm -f $(OFILES)
