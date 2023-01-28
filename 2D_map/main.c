#include "../cub3D.h"

static int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

void	new_image(t_data *data, t_window *win, int width, int length)
{
	t_image		*img;
	t_image		*tmp;
	char		*a;

	img = (t_image *) malloc(sizeof(t_image));
	img->img = mlx_new_image(win->mlx, width, length);
	a = mlx_get_data_addr(img->img, &(img->bit), &(img->size), &(img->endian));
	img->address = a;
	draw_map(img, data);
	tmp = win->image;
	win->image = img;
	draw_view_angle(data, win);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img->img, 10, 10);
	if (tmp)
		mlx_destroy_image(win->mlx, tmp->img);
	free(tmp);
}

static int	key_hook(int key, t_data *d)
{
	char		*dst;
	t_image		*img;
	long long	p[2];

	if (key == RIGHT || key == LEFT)
		d->teta += PI / 16 * ((key == LEFT) - (key == RIGHT));
	else if (key == UP || (key == DOWN))
	{
		img = d->win->image;
		p[0] = d->p[0] + STEP * cos(d->teta) * ((key == UP) - (key == DOWN));
		p[1] = d->p[1] - STEP * sin(d->teta) * ((key == UP) - (key == DOWN));
		dst = img->address + (p[1] * img->size + p[0] * img->bit / 8);
		if (*(unsigned int *) dst == WALL || *(unsigned int *) dst == GRID)
			return (0);
		d->p[0] = p[0];
		d->p[1] = p[1];
	}
	else
		my_close(d->win);
	new_image(d, d->win, (d->max + 1) * TILE, (d->lines + 1) * TILE);
}

t_data	*init_data_(char *file_name)
{
	int			fd;
	void		*t;
	t_data		*d;
	t_window	*win;

	d = malloc(sizeof(t_data));
	init_data(d);
	fd = check_files(file_name, ".cub");
	parse_time(d, fd);
	win = (t_window *) malloc(sizeof(t_window));
	win->mlx = mlx_init();
	t = mlx_new_window(win->mlx, d->max * TILE, (d->lines + 1) * TILE, "cub");
	win->win = t;
	d->win = win;
	d->win->image = NULL;
	d->p[0] = d->player[0] * TILE + TILE / 2;
	d->p[1] = d->player[1] * TILE + TILE / 2;
	return (d);
}

int	main(int ac, char **av)
{
	t_data		*data;

	data = init_data_(av[1]);
	new_image(data, data->win, (data->max + 1) * TILE, (data->lines) * TILE);
	mlx_hook(data->win->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win->win, 17, 0, my_close, data->win);
	mlx_loop(data->win->mlx);
}
