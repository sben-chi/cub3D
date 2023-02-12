/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:24 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 15:24:43 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	data->p[0] = -1;
	data->p[1] = -1;
	data->colors[0] = -1;
	data->colors[1] = -1;
	data->teta = -1;
	data->map = NULL;
	data->lines = 0;
	data->max = 0;
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
	!(win->mlx) && put_error("mlx_init error\n", 15);
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "cub3D");
	!(win->win) && put_error("mlx_new_window error\n", 21);
	win->image = my_calloc(1, sizeof(t_image));
	data->win = win;
	mlx_mouse_hide();
	mlx_mouse_move(data->win->win, (WIDTH / 2), HEIGHT / 2);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		put_error("Error:\n > wrong arguments\n", 26);
	data = init_data_(av[1]);
	new_image(data, data->win);
	mlx_hook(data->win->win, 2, 0, key_press, data);
	mlx_hook(data->win->win, 3, 0, key_release, data);
	mlx_hook(data->win->win, 6, 0, mouse_hook, data);
	mlx_hook(data->win->win, 17, 0, my_close, data->win);
	mlx_loop_hook(data->win->mlx, update_image, data);
	mlx_loop(data->win->mlx);
	return (1);
}
