/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:27 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 19:02:01 by irhesri          ###   ########.fr       */
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
	draw_view_angle(data, win);				// put it back when u remove tst map
	draw_walls(data, win->image, data->rays);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img, 0, 0);
	(tmp) && mlx_destroy_image(win->mlx, tmp);
}

int	key_hook(t_data *d)
{
	t_keys		*keys;
	double		p[2];

	keys = d->keys;
	if (keys->esc)
	{
		// mlx_destroy_window(d->tst->mlx, d->tst->win); // to delete
		my_close(d->win);
	}
	if (keys->r_rotate || keys->l_rotate)
		d->teta += 0.1 * (keys->r_rotate - keys->l_rotate);
	if (keys->left || keys->right || keys->up || keys->down)
	{
		p[0] = d->p[0] + STEP * cos(d->teta) * (keys->up - keys->down);
		p[1] = d->p[1] + STEP * sin(d->teta) * (keys->up - keys->down);
		p[0] -= STEP * sin(d->teta) * (keys->right - keys->left);
		p[1] += STEP * cos(d->teta) * (keys->right - keys->left);
		if (!d->map_arr[(int)d->p[1] / TILE][(int)p[0] / TILE])
			d->p[0] = p[0];
		if (!d->map_arr[(int)p[1] / TILE][(int)d->p[0] / TILE])
			d->p[1] = p[1];
	}
	// new_image_tst(d, d->tst); // to delete
	new_image(d, d->win);
	return (1);
}

int	key_press(int key, t_data *data)
{
	t_keys	*keys;

	keys = data->keys;
	keys->esc = (key == ESC);
	keys->up |= (key == W);
	keys->down |= (key == S);
	keys->left |= (key == A);
	keys->right |= (key == D);
	keys->l_rotate |= (key == LEFT);
	keys->r_rotate |= (key == RIGHT);
	return (1);
}

int	key_release(int key, t_data *data)
{
	t_keys	*keys;

	keys = data->keys;
	keys->up &= (key != W);
	keys->down &= (key != S);
	keys->left &= (key != A);
	keys->right &= (key != D);
	keys->l_rotate &= (key != LEFT);
	keys->r_rotate &= (key != RIGHT);
	return (1);
}

int	mouse_hook(int x, int y, t_data *data)
{
	data->teta += 0.1 * ((x > WIDTH_2) - (x < WIDTH_2));
	mlx_mouse_hide();
	mlx_mouse_move(data->win->win, WIDTH_2, HEIGHT /  2);
	// new_image_tst(data, data->tst); // to delete
	// new_image(data, data->win);
	return (1);
}