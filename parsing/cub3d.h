/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:52:55 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/28 18:39:16 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D__H
# define CUB3D__H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

# define BUFFER_SIZE 10
# define PI 3.14159265358979323846

typedef struct s_image
{
	void	*img;
	char	*address;
	int		bit;
	int		size;
	int		endian;
} t_image;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	long long	map_size[2];
	t_image	*image;
} t_window;

typedef struct s_map
{
	char			*line;
	long long			llen;
	struct s_map	*next;
	struct s_map	*prev;
} t_map;

typedef struct s_data
{
	char	*textures[4];
	int		colors[2];
	int		player[3];
	size_t	max;
	size_t	lines;
	t_map	*map;
	double	teta;
	t_window *win;
	long long p[2];
} t_data;


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
