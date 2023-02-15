OS			= $(shell uname)

NAME 		= cub3D
CC 			= gcc 
CFLAGS		= #-O3 -g -fsanitize=address

PARSING 	= parsing/parsing_utils.c parsing/parsing.c
RAYCASTING 	= raycasting/draw_walls.c raycasting/event_hook.c raycasting/loop_hook.c raycasting/intersections.c
UTILS 		= main.c utils/utils.c utils/utils2.c

ifeq ($(OS), Linux)
	MLXFLAGS	= -lmlx -lbsd -lXext -lX11
	LIBRARY		= mlx_linux/libmlx.a
endif
ifeq ($(OS), Darwin)
	MLXFLAGS	= -framework OpenGl -framework Appkit -Imlx -Iincludes
	LIBRARY		= mlx_mac/libmlx.a
endif

OBJ	= $(PARSING:.c=.o) $(RAYCASTING:.c=.o) $(UTILS:.c=.o) 

all: $(NAME)

check_OS:
ifndef MLXFLAGS
	@echo "\033[1;31m INCOMPATIBLE OS \033[0;37m"
	@exit 1
endif

$(NAME): check_OS $(OBJ) 
	$(CC) $(OBJ) $(LIBRARY) -o $@ $(CFLAGS) $(MLXFLAGS) -lm

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re