/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:27 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 17:30:28 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	my_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	exit(0);
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
	// draw_map(data, win->image);				// put it back when u remove tst map
	// draw_view_angle(data, win);				// put it back when u remove tst map
	draw_walls(data, win->image, data->rays);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img, 0, 0);
	(tmp) && mlx_destroy_image(win->mlx, tmp);
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
		if (!d->map_arr[(int)d->p[1] / TILE][(int)p[0] / TILE])
			d->p[0] = p[0];
		if (!d->map_arr[p[1] / TILE][(int)d->p[0] / TILE])
			d->p[1] = p[1];
	}
	else if (key == ESC)
	{
		mlx_destroy_window(d->tst->mlx, d->tst->win); // to delete
		my_close(d->win);
	}
	else
		return (0);
	new_image_tst(d, d->tst); // to delete
	new_image(d, d->win);
	return (1);
}

int	mouse_hook(int x, int y, t_data *data)
{
	data->teta += 0.1 * ((x > WIDTH_2) - (x < WIDTH_2));
	mlx_mouse_hide();
	mlx_mouse_move(data->win->win, WIDTH_2, HEIGHT /  2);
	new_image_tst(data, data->tst); // to delete
	new_image(data, data->win);
	return (1);
}