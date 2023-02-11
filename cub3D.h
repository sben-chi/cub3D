/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 20:10:41 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./mlx/mlx.h"
# include <string.h>
# include <limits.h>
# include "stdbool.h"

# include "./data.h"
# include "./macros.h"



// basic fcts
void	*my_calloc(size_t count, size_t size);
bool	put_error(char *s, size_t len);
bool	**get_map_arr(t_map *map, size_t lines, size_t max);

// update image
void	get_view_info(t_data *data);
void	draw_walls(t_data *data, t_image *cub, double *rays);
void	new_image(t_data *data, t_window *win);

// hooks functions
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		mouse_hook(int x, int y, t_data *data);
int		update_player_data(t_data *d);
int		my_close(t_window *win);


// double	*get_inter(t_data *data, double dx, double dy, short *sym);





char	*get_next_line(int fd, size_t *t_len);
int		check_files(char *s1, char *s2);
int		my_strlen(char *s);
short	add_back(t_map **map, t_map **last, t_map *nnode);
t_map	*new(char *line, int len);
void	init_data(t_data *data);
void	parse_time(t_data *data, int fd);
short	element(t_data *data, char *element, int len);

//------------new modif from saida
void	textures(t_data *dt, long long x, long long *y, double wall_h);
//--------------------------------

#endif
