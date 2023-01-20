#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define BUFFER_SIZE 10

typedef struct s_map
{
    char			*line;
	int				llen;
    struct s_map	*next;
	struct s_map	*prev;
}t_map;

typedef struct s_data
{
    char	*textures[4];
    int		colors[2];
    char    player;
    int     p;
    t_map	*map;
}t_data;

/*-------functions----------*/

char	*get_next_line(int fd, int *t_len);
int		check_files(char *s1, char *s2);
int		my_strlen(char *s, char limit);
int		add_back(t_map **map, t_map **last, t_map *nnode);
t_map	*new(char *line, int len);

#endif
