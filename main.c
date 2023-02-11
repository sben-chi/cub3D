/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:24 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 19:51:23 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

t_data	*init_data_(char *file_name)
{
	int			fd;
	t_data		*data;
	t_window	*win;

	data = my_calloc(1, sizeof(t_data));
	init_data(data);
	fd = check_files(file_name, ".cub");
	parse_time(data, fd);
	data->inter = my_calloc(WIDTH, sizeof(bool));
	data->rays = my_calloc(WIDTH, sizeof(double));
	data->diff = my_calloc(WIDTH, sizeof(double));
	data->dir = my_calloc(WIDTH, sizeof(short));
	data->keys = my_calloc(1, sizeof(t_keys));
	data->map_arr = get_map_arr(data->map, data->lines, data->max);
	win = (t_window *) my_calloc(1, sizeof(t_window));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "cub3D");
	win->image = my_calloc(1, sizeof(t_image));
	data->win = win;
	mlx_mouse_hide();
	mlx_mouse_move(data->win->win, WIDTH_2, HEIGHT /  2);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		put_error("wrong arguments\n", 16);
	data = init_data_(av[1]);
	new_image(data, data->win);
	mlx_hook(data->win->win, 2, 0, key_press, data);
	mlx_hook(data->win->win, 3, 0, key_release, data);
	mlx_hook(data->win->win, 6, 0, mouse_hook, data);
	mlx_hook(data->win->win, 17, 0, my_close, data->win);
	mlx_loop_hook(data->win->mlx, update_player_data, data);
	mlx_loop(data->win->mlx);
	return (1);
}
