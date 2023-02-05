#include "../cub3D.h"

t_data	*init_data_(char *file_name)
{
	int			fd;
	size_t		height;
	t_data		*data;
	t_window	*win;

	data = my_calloc(1, sizeof(t_data));
	init_data(data);
	fd = check_files(file_name, ".cub");
	parse_time(data, fd);
	
	data->inter = my_calloc(WIDTH, sizeof(bool));
	data->rays = my_calloc(WIDTH, sizeof(double));
	
	win = (t_window *) my_calloc(1, sizeof(t_window));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "cub3D");
	win->image = my_calloc(1, sizeof(t_image));
	data->win = win;
	data->map_arr = get_map_arr(data->map, data->lines, data->max);
	
	
	return (data);
}


void	new_image(t_data *data, t_window *win)
{
	void		*img;
	void		*tmp;
	char		*a;

	img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	a = mlx_get_data_addr(img, &(win->image->bits), &(win->image->len), &(win->image->endian));
	win->image->address = a;
	tmp = win->image->img;
	win->image->img = img;
	// draw_map(data, win->image);
	// draw_view_angle(data, win);
	draw_walls(win->image, data->rays, data->inter);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img, 0, 0);
	(tmp) && mlx_destroy_image(win->mlx, tmp);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		put_error("wrong arguments\n", 16);
	data = init_data_(av[1]);
	init_data_tst(data);
	// data->tst = NULL;
	// if (data->tst)
	new_image_tst(data, data->tst);
	new_image(data, data->win);
	// new_image(data, win, (data->max - 1) * TILE, (data->lines) * TILE);
	// mlx_put_image_to_window (data->tst->mlx, data->tst->win, data->tst->image->img, 0, 0);

	//----------


	mlx_hook(data->win->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win->win, 17, 0, my_close, data->tst);
	
	mlx_loop(data->win->mlx);
	// mlx_loop(data->tst->mlx);
	return (1);
}
