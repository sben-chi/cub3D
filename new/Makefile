NAME = cub3D
NAME_B = cub3D_bonus
CC = gcc
# LINUX
# CFLAGS		= -lm -lmlx -lbsd -lXext -lX11 -fsanitize=address -g
# LFLAGS		= -L /usr/local/lib
# CPPFLAGS	= -I /usr/local/include
CFLAGS = -g -fsanitize=address #-lm -Wall -Wextra -Werror #
LFLAGS = -Imlx -lmlx -framework OpenGl -framework Appkit
MANDATORY = main.c double_fct.c fct.c intersections.c key_hook.c ../basic_fct.c draw_walls.c \
			2D_draw_line.c 2D_draw_map.c 2D_fct.c
F =  ../parsing/init_data.c ../parsing/parsing_utils.c ../parsing/gnl.c ../parsing/parsing.c ../parsing/parsing_utils2.c

BONUS =

all: $(NAME)

$(NAME): $(MANDATORY:.c=.o) $(F:.c=.o) 
	gcc $(MANDATORY) $(F) -o $@ $(CFLAGS) $(CPPFLAGS) $(LFLAGS) -lm

$(NAME_B): $(BONUS:.c=.o)
	gcc $(BONUS) -o $@ $(CFLAGS) $(CPPFLAGS) $(LFLAGS) 

bonus:$(NAME_B)

clean:
	rm -rf *.o ../parsing/*.o ../*.o

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re