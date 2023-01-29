/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:30 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/28 18:39:16 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	data->player[0] = -1;
	data->player[1] = -1;
	data->colors[0] = -1;
	data->colors[1] = -1;
	data->teta = -1;
	data->map = NULL;
	data->lines = 0;
	data->max = 0;
}
