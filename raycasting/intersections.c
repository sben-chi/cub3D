/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:36 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 14:04:51 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	*get_intersection_x(t_data *dt, double *p, double teta, short *sy)
{
	size_t	px;
	double	d[2];
	double	*ray;

	ray = my_calloc(3, sizeof(double));
	px = floor(p[0] / TILE);
	d[0] = fabs((floor(p[0] / TILE + (sy[0] == 1)) * TILE - p[0]));
	while (1)
	{
		px += sy[0];
		d[1] = fabs(d[0] * tan(teta));
		ray[0] = p[0] + sy[0] * d[0];
		ray[1] = p[1] + sy[1] * d[1];
		if ((ray[1] >= (dt->lines * TILE)) || (ray[1] <= 0)
			|| (ray[0] >= (dt->max * TILE)) || (ray[0] <= 0))
		{
			free(ray);
			return (NULL);
		}
		if (dt->map_arr[(int)(ray[1] / TILE)][px])
			break ;
		d[0] += TILE;
	}
	ray[2] = fabs(sy[0] * d[0] * cos(dt->teta) + sy[1] * d[1] * sin(dt->teta));
	return (ray);
}

double	*get_intersection_y(t_data *dt, double *p, double teta, short *sy)
{
	size_t	py;
	double	d[2];
	double	*ray;

	ray = my_calloc(3, sizeof(double));
	py = floor(p[1] / TILE);
	d[1] = fabs((floor(p[1] / TILE + (sy[1] == 1)) * TILE - p[1]));
	while (1)
	{
		py += sy[1];
		d[0] = fabs(d[1] / tan(teta));
		ray[0] = p[0] + sy[0] * d[0];
		ray[1] = p[1] + sy[1] * d[1];
		if ((ray[1] >= (dt->lines * TILE)) || (ray[1] <= 0)
			|| (ray[0] >= (dt->max * TILE)) || (ray[0] <= 0))
		{
			free(ray);
			return (NULL);
		}
		if (dt->map_arr[py][(int)(ray[0] / TILE)])
			break ;
		d[1] += TILE;
	}
	ray[2] = fabs(sy[0] * d[0] * cos(dt->teta) + sy[1] * d[1] * sin(dt->teta));
	return (ray);
}

void	get_dest(t_data *data, double teta, long long k)
{
	short	sym[2];
	double	*ptr_x;
	double	*ptr_y;

	sym[0] = ((teta > (3 * PI / 2)) || (teta < (PI / 2)));
	sym[0] -= !sym[0];
	sym[1] = ((teta < PI) - (teta >= PI));
	ptr_x = get_intersection_x(data, data->p, teta, sym);
	ptr_y = get_intersection_y(data, data->p, teta, sym);
	data->inter[k] = (!ptr_x || (ptr_y && (ptr_x[2] >= ptr_y[2])));
	if (data->inter[k])
	{
		data->diff[k] = ptr_y[0];
		data->rays[k] = ptr_y[2];
	}
	else
	{
		data->diff[k] = ptr_x[1];
		data->rays[k] = ptr_x[2];
	}
	free(ptr_x);
	free(ptr_y);
}

void	get_view_info(t_data *data)
{
	double		teta;
	long long	k;

	k = WIDTH;
	teta = data->teta + (WIDTH / 2) * (M_PI / (3 * WIDTH));
	while (--k >= 0)
	{
		while (teta < 0)
			teta += (2 * PI);
		while ((teta > 0) && (teta >= (2 * PI)))
			teta -= (2 * PI);
		get_dest(data, teta, k);
		teta -= (M_PI / (3 * WIDTH));
		if (data->inter[k])
			data->dir[k] = (teta <= PI) * 'S' + (teta > PI) * 'N';
		else
			data->dir[k] = ((teta <= (3 * PI_2)) && (teta > PI_2)) * 'W';
		data->dir[k] += ('E' * !data->dir[k]);
	}
}
