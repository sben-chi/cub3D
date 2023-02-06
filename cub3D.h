/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/06 11:48:51 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <string.h>
# include <limits.h>
# include "stdbool.h"

# include "./data.h"
# include "./macros.h"


// void	draw_lines(t_segment *seg, t_window *win);
bool	**get_map_arr(t_map *map, size_t lines, size_t max);
void	draw_view_angle(t_data *data, t_window *win);
// void	draw_map(t_image *img, t_data *data);


void	*my_calloc(size_t count, size_t size);
bool	put_error(char *s, size_t len);

int		my_close(t_window *win);
int		key_hook(int key, t_data *d);
void	draw_walls(t_data *data, t_image *cub, double *rays);
void	new_image(t_data *data, t_window *win);
void	init_data_tst(t_data *data);


// to delete
void	draw_tst(t_data *data, double *ptr);
void	draw_map(t_data *data, t_image *img);
void	seg_init(t_segment *seg, t_image *map);
void	new_image_tst(t_data *data, t_window *win);
//-----------






char	*get_next_line(int fd, size_t *t_len);
int		check_files(char *s1, char *s2);
int		my_strlen(char *s);
short	add_back(t_map **map, t_map **last, t_map *nnode);
t_map	*new(char *line, int len);
void	init_data(t_data *data);
void	parse_time(t_data *data, int fd);
short	element(t_data *data, char *element, int len);

#endif
