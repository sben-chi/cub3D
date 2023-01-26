/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:52:55 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/26 14:54:43 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 10

typedef struct s_map
{
	char			*line;
	size_t			llen;
	struct s_map	*next;
	struct s_map	*prev;
}t_map;

typedef struct s_data
{
	char	*textures[4];
	int		colors[2];
	char	player;
	// size_t	max;
	// int		lines;
	t_map	*map;
}t_data;

/*-------functions----------*/

char	*get_next_line(int fd, size_t *t_len);
int		check_files(char *s1, char *s2);
int		my_strlen(char *s);
short	add_back(t_map **map, t_map **last, t_map *nnode);
t_map	*new(char *line, int len);
void	init_data(t_data *data);
void	parse_time(t_data *data, int fd);
short	element(t_data *data, char *element, int len);

#endif
