/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:36 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 16:08:39 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static double	is_equale(double n1, double n2)
{
	return ((n1 >= (n2 - 0.01)) && (n1 <= (n2 - 0.001)));
}

double	*get_intersection_x(double *p, double teta, short *sym, bool **arr,t_data *data)
{
	size_t	px;
	double	dx;
	double	dy;
	double	hyp;
	double	*info;

	info = my_calloc(4, sizeof(double));
	if (is_equale(teta, PI_2) || is_equale(teta, _3PI_2))
		return (NULL);
	px = floor(p[0] / TILE);
	dx = fabs((floor(p[0] / TILE + (sym[0] == 1)) * TILE - p[0]));
	while (1)
	{
		px += sym[0];
		dy = fabs(dx * tan(teta));

		info[0] = p[0] + sym[0] * dx;
		info[1] = p[1] + sym[1] * dy;
		
		if (info[1] >= (data->lines * TILE) || info[1] < 0 || info[0] > (data->max - 1) * TILE || info[0] < 0 )
		{
			free(info);
			return (NULL);
		}
		if (arr[(int)(info[1] / TILE)][px])
		{
			info[0] -= (sym[0] == 1);
			info[1] -= (sym[1] == 1);
			info[3] = fabs(sym[0] * dx * cos(data->teta) + sym[1] * dy * sin(data->teta));
			return (info);
		}
		dx += TILE;
	}
}

double	*get_intersection_y(double *p, double teta, short *sym, bool **arr,t_data *data)
{
	size_t	py;
	double	dx;
	double	dy;
	double	hyp;
	double	*info;

	if (is_equale(teta, 0) || is_equale(teta, PI))
		return (NULL);
	info = my_calloc(4, sizeof(double));
	py = floor(p[1] / TILE);
	dy = fabs((floor(p[1] / TILE + (sym[1] == 1)) * TILE - p[1]));
	while (1)
	{
		py += sym[1];
		dx = fabs(dy / tan(teta));

		info[0] = p[0] + sym[0] * dx;
		info[1] = p[1] + sym[1] * dy;

		if (info[1] >= (data->lines * TILE) || info[1] < 0 || info[0] > (data->max - 1) * TILE || info[0] < 0 )
		{
			free(info);
			return (NULL);
		}
		if (arr[py][(int)(info[0] / TILE)])
		{
			info[0] -= (sym[0] == 1);
			info[1] -= (sym[1] == 1);
			info[3] = fabs(sym[0] * dx * cos(data->teta) + sym[1] * dy * sin(data->teta));
			return (info);
		}
		dy += TILE;
	}
}

bool	get_dest(t_data *data, double *rays, double *diff, double teta)
{
	bool	inter;
	short	sym[2];
	double	*ptr_x;
	double	*ptr_y;

	sym[0] = ((teta > (3 * PI / 2)) || (teta < (PI / 2)));
	sym[0] -= !sym[0];
	sym[1] = ((teta < PI) - (teta >= PI));

	ptr_x = get_intersection_x(data->p, teta, sym, data->map_arr, data);
	ptr_y = get_intersection_y(data->p, teta, sym, data->map_arr, data);
	inter = (!ptr_x || (ptr_y && (ptr_x[3] >= ptr_y[3])));
	if (inter)
	{
		(*diff) = ptr_y[1];
		(*rays) = ptr_y[3];
	}
	else
	{
		(*diff) = ptr_x[0];
		(*rays) = ptr_x[3];
	}
	
	// delete later -----------
	if (inter)
		draw_tst(data, ptr_y);
	else
		draw_tst(data, ptr_x);
	// -------------------------

	free(ptr_x);
	free(ptr_y);
	return (inter);
}

void	draw_view_angle(t_data *data, t_window *win)
{
	short		k;
	double		teta;

	k = WIDTH;
	teta = data->teta + WIDTH_2 * ANGLE;
	while (--k)
	{
		while (teta < 0)
			teta += (2 * PI);
		while ((teta > 0) && (teta >= (2 * PI)))
			teta -= (2 * PI);
		data->inter[k] = get_dest(data, data->rays + k, data->diff + k, teta);
		teta -= ANGLE;
		if (data->inter[k])
			data->dir[k] = (teta <= PI) * 'N' + (teta > PI) * 'S';
		else
			data->dir[k] = ((teta <= _3PI_2) && (teta > PI_2)) * 'W';
		data->dir += ('E' * !data->dir);
	}
}

// void	draw_view_angle(t_data *data, t_window *win)
// {
// 	short		k;
// 	double		teta;

// 	k = WIDTH_2;
// 	data->teta = angle_round(data->teta);
// 	teta = data->teta;
// 	while (--k >= -WIDTH_2)
// 	{
// 		teta = data->teta + k * ANGLE;
// 		teta = angle_round(teta);
// 		data->inter[WIDTH_2 + k] = get_dest(data->tst->image, data->p, teta, data->rays + WIDTH_2 + k, data->map_arr, data);
// 	}
// }
