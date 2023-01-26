/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:30 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/26 18:45:28 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	i = -1;
	while (++i < 3)
		data->player[i] = -1;
	data->colors[0] = -1;
	data->colors[1] = -1;
	data->map = NULL;
	data->lines = 0;
	data->max = 0;
}
