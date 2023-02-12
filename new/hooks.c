/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:27 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 13:21:17 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	new_image(t_data *data, t_window *win)
{
	char		*a;
	void		*img;
	void		*tmp;

	img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	(!img) && put_error("mlx_new_image error\n", 20);
	a = mlx_get_data_addr(img, &(win->image->bits),
			&(win->image->len), &(win->image->endian));
	(!a) && put_error("mlx_get_data_addr error\n", 20);
	win->image->address = a;
	tmp = win->image->img;
	win->image->img = img;
	get_view_info(data);
	draw_walls(data, win->image, data->rays);
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window (win->mlx, win->win, img, 0, 0);
	(tmp) && mlx_destroy_image(win->mlx, tmp);
}

int	update_image(t_data *data)
{
	double		p[2];
	t_keys		*keys;

	keys = data->keys;
	if (keys->esc)
		my_close(data->win);
	if (keys->r_rotate || keys->l_rotate)
		data->teta += 0.1 * (keys->r_rotate - keys->l_rotate);
	if (keys->left || keys->right || keys->up || keys->down)
	{
		p[0] = data->p[0] + STEP * cos(data->teta) * (keys->up - keys->down);
		p[1] = data->p[1] + STEP * sin(data->teta) * (keys->up - keys->down);
		p[0] -= STEP * sin(data->teta) * (keys->right - keys->left);
		p[1] += STEP * cos(data->teta) * (keys->right - keys->left);
		if (!data->map_arr[(int)data->p[1] / TILE][(int)p[0] / TILE])
			data->p[0] = p[0];
		if (!data->map_arr[(int)p[1] / TILE][(int)data->p[0] / TILE])
			data->p[1] = p[1];
	}
	new_image(data, data->win);
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
	(void)y;
	data->teta += 0.1 * ((x > (WIDTH / 2)) - (x < (WIDTH / 2)));
	mlx_mouse_hide();
	mlx_mouse_move(data->win->win, (WIDTH / 2), HEIGHT / 2);
	return (1);
}
