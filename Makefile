NAME = cub3D
NAME_B = cub3D_bonus
CC = gcc 
# LINUX
#  CFLAGS		= -lm -lmlx -lbsd -lXext -lX11 -fsanitize=address -g
#  LFLAGS		= -L /usr/local/lib
#  CPPFLAGS	= -I /usr/local/include
CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror 
LFLAGS =  -framework OpenGl -framework Appkit -Imlx -Iincludes
MANDATORY = main.c ./new/fct.c ./new/intersections.c ./new/hooks.c ./new/draw_walls.c
F =  ./parsing/init_data.c ./parsing/parsing_utils.c ./parsing/gnl.c ./parsing/parsing.c ./parsing/parsing_utils2.c textures/textures.c

LIBRARY = libmlx.a

all: $(NAME)

$(NAME): $(F:.c=.o) $(MANDATORY:.c=.o)
	gcc $(F) $(MANDATORY) ./mlx/libmlx.a -o $@ $(CFLAGS) $(CPPFLAGS) $(LFLAGS) -lm 


clean:
	rm -rf *.o ./parsing/*.o ./new/*.o textures/textures.o

fclean: clean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re