/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:46 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/06 12:14:47 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	draw_segment(t_image *img, long long x, long long *y, long color)
{
	char	*dst;

	while ((y[0] < y[1]) && (y[0] < HEIGHT))
	{
		dst = img->address + (y[0] * img->len + x * img->bits / 8);
		*(unsigned int *) dst = color;
		++y[0];
	}
}

void	draw_walls(t_data *data, t_image *cub, double *rays)
{
	int			k;
	double		dst_proj;
	double		wall_h;
	long long	x;
	long long	y[2];

	k = WIDTH_2;
	x = -1;
	while (++x < WIDTH)
	{
		k += (x > WIDTH_2) - (x <= WIDTH_2);
		(rays[x] < 1) && (rays[x] = 1);
		wall_h = round((TILE / rays[x]) * PROJ_DST);
		dst_proj = round((HEIGHT - wall_h) / 2);
		y[0] = 0;
		y[1] = dst_proj * (dst_proj > 0);
		draw_segment(cub, x, y, data->colors[0]);
		y[1] += wall_h;
		draw_segment(cub, x, y, WALL * data->inter[x]);
		y[1] = HEIGHT;
		draw_segment(cub, x, y, data->colors[1]);
	}
}
