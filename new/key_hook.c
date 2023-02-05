# include "../cub3D.h"

int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
}

int	key_hook(int key, t_data *d)
{
	char		*dst;
	t_image		*img;
	long long	p[2];

	if (key == RIGHT || key == LEFT)
		d->teta += 0.1 * ((key == RIGHT) - (key == LEFT));
	else if ((key == A) || (key == D) || (key == W) || (key == S))
	{
		img = d->win->image;
		p[0] = d->p[0] + STEP * cos(d->teta) * ((key == W) - (key == S));
		p[1] = d->p[1] + STEP * sin(d->teta) * ((key == W) - (key == S));
		p[0] -= STEP * sin(d->teta) * ((key == D) - (key == A));
		p[1] += STEP * cos(d->teta) * ((key == D) - (key == A));
		if (d->map_arr[p[1] / TILE][p[0] / TILE])
			return (0);
		d->p[0] = p[0];
		d->p[1] = p[1];
	}
	else if (key == ESC)
	// {
	// 	my_close(d->tst); // to delete
		my_close(d->win);
	// }
	else
		return (0);
	new_image_tst(d, d->tst);
	new_image(d, d->win);
	return (1);
}