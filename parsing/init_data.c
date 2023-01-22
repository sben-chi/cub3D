/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:30 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/22 14:06:31 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	data->colors[0] = -1;
	data->colors[1] = -1;
	data->map = NULL;
	data->p = 0;
}
