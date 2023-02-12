/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:27 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 18:17:36 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
