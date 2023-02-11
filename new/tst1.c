/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:36 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 21:43:23 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static double	is_equale(double n1, double n2)
{
	return ((n1 >= (n2 - 0.01)) && (n1 <= (n2 - 0.01)));
}

double	*get_intersection(t_data *data, double teta, short *sym, bool x_y)
{
	size_t	p[2];
	double	d[2];
	double	*info;

	// if ((x_y) && (is_equale(teta, 0) || is_equale(teta, PI)))
	// 	return (NULL);
	// if ((!x_y) && (is_equale(teta, PI_2) || is_equale(teta, _3PI_2)))
	// 	return (NULL);
	info = my_calloc(4, sizeof(double));
	p[x_y] = floor(data->p[x_y] / TILE);
	d[x_y] = fabs((floor(data->p[x_y] / TILE + (sym[x_y] == 1)) * TILE - data->p[x_y]));
	while (1)
	{
		p[x_y] += sym[x_y];
		if (x_y)
			d[!x_y] = fabs(d[x_y] / tan(teta));
		else
			d[!x_y] = fabs(d[x_y] * tan(teta));
		info[0] = data->p[0] + sym[0] * d[0];
		info[1] = data->p[1] + sym[1] * d[1];
		if (info[1] >= (data->lines * TILE) || info[1] <= 0
			|| info[0] >= (data->max - 1) * TILE || info[0] <= 0 )
		{
			free(info);
			return (NULL);
		}
		p[!x_y] = (int)(info[!x_y] / TILE);
		if (data->map_arr[p[1]][p[0]])
		{
			info[0] -= (sym[0] == 1);
			info[1] -= (sym[1] == 1);
			info[3] = fabs(sym[0] * d[0] * cos(data->teta) + sym[1] * d[1] * sin(data->teta));
			return (info);
		}
		d[x_y] += TILE;
	}
}

bool	get_dest(t_data *data, double *rays, double *diff, double teta)
{
	bool	inter;
	short	sym[2];
	double	*ptr_x;
	double	*ptr_y;

	sym[0] = ((teta > (_3PI_2)) || (teta < PI_2));
	sym[0] -= !sym[0];
	sym[1] = ((teta < PI) - (teta >= PI));
	ptr_x = get_intersection(data, teta, sym, 0);
	ptr_y = get_intersection(data, teta, sym, 1);
	inter = (!ptr_x || (ptr_y && (ptr_x[3] >= ptr_y[3])));
	if (inter)
	{
		(*diff) = ptr_y[0];
		(*rays) = ptr_y[3];
	}
	else
	{
		(*diff) = ptr_x[1];
		(*rays) = ptr_x[3];
	}
	free(ptr_x);
	free(ptr_y);
	return (inter);
}

void	get_view_info(t_data *data)
{
	short		k;
	double		teta;

	k = WIDTH;
	teta = data->teta + WIDTH_2 * ANGLE;
	while (--k >= 0)
	{
		while (teta < 0)
			teta += (2 * PI);
		while ((teta > 0) && (teta >= (2 * PI)))
			teta -= (2 * PI);
		data->inter[k] = get_dest(data, data->rays + k, data->diff + k, teta);
		teta -= ANGLE;
		if (data->inter[k])
			data->dir[k] = (teta <= PI) * 'S' + (teta > PI) * 'N';
		else
			data->dir[k] = ((teta <= _3PI_2) && (teta > PI_2)) * 'W';
		data->dir[k] += ('E' * !data->dir[k]);
	}
}
