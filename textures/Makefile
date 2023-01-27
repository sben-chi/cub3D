CC = cc

NAME = cub3d

CFLAGS = -I/usr/include -Imlx_linux -O3
LFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRCS = my_put.c genrl.c read_map.c

OBJS = ${SRCS:.c=.o}


.c.o:
		$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re