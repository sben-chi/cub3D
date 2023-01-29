NAME = cub3D
NAME_B = cub3D_bonus
CC = gcc
CFLAGS		= -lm -lmlx -lbsd -lXext -lX11 -fsanitize=address -g
LDFLAGS		= -L /usr/local/lib
CPPFLAGS	= -I /usr/local/include
MANDATORY = main.c bresenham.c search.c grids.c
F =  ../parsing/init_data.c ../parsing/parsing_utils.c ../parsing/gnl.c ../parsing/parsing.c ../parsing/parsing_utils2.c

BONUS =

all: $(NAME)

$(NAME): $(MANDATORY:.c=.o) $(F:.c=.o) 
	gcc $(MANDATORY) $(F) -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

$(NAME_B): $(BONUS:.c=.o)
	gcc$(BONUS) -o $@ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) 

bonus:$(NAME_B)

clean:
	rm -rf *.o rm -rf ../parsing/*.o

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re