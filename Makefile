NAME = cub3D
CC = gcc 
# LINUX
# CFLAGS		= -lm -lmlx -lbsd -lXext -lX11 -fsanitize=address -g
# LFLAGS		= -L /usr/local/lib
# CPPFLAGS	= -I /usr/local/include
CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror 
MLXFLAGS =  -framework OpenGl -framework Appkit -Imlx -Iincludes

PARSING = parsing/parsing_utils.c parsing/parsing.c
RAYCASTING = raycasting/draw_walls.c raycasting/event_hook.c raycasting/loop_hook.c raycasting/intersections.c
UTILS = main.c utils/utils.c utils/utils2.c

LIBRARY = ./mlx/libmlx.a

all: $(NAME)

$(NAME): $(PARSING:.c=.o) $(RAYCASTING:.c=.o) $(UTILS:.c=.o) 
	$(CC)  $(PARSING) $(RAYCASTING) $(UTILS) $(LIBRARY) -o $@ $(CFLAGS) $(MLXFLAGS) -lm

clean:
	rm -rf *.o parsing/*.o raycasting/*.o utils/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re