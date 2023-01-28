#include "../cub3D.h"

static double	my_absolute(double teta)
{
	return ((teta >= 0) * teta + (teta < 0) * -teta);
}

static double	angle_round(double teta)
{
	while ((teta < 0) && (teta <= (2 * -PI)))
		teta += (2 * PI);
	while ((teta > 0) && (teta >= (2 * PI)))
		teta -= (2 * PI);
	return (teta);
}

void	new_update(t_data *data, t_segment *seg, double teta)
{
	seg->xf = seg->xi;
	if (((teta > 0) && (teta < PI)) || ((teta < 0) && (teta < -PI)))
		seg->yf = 0;
	else
		seg->yf = data->lines * TILE;
}

void	get_dest(t_data *data, t_window *win, t_segment *seg, double teta)
{
	double		sym[2];
	long long	dy;
	long long	dx;

	dx = (my_absolute(teta) < (PI / 2));
	dx = (data->max * TILE - seg->xi) * dx + (seg->xi) * !dx;
	dy = (my_absolute(teta) < (PI));
	dy = (seg->yi) * dy + (data->lines * TILE - seg->yi) * !dy;
	if (my_absolute(teta) != (PI / 2) && my_absolute(teta) != (3 * PI / 2))
	{
		sym[0] = (teta > 0) && ((teta > (3 * PI / 2)) || (teta < (PI / 2)));
		sym[0] += (teta <= 0) && ((teta > (-PI / 2)) || (teta < (3 * -PI / 2)));
		sym[0] -= !sym[0];
		sym[1] = (teta > 0) * ((teta >= PI) - (teta < PI));
		sym[1] += (teta <= 0) * ((teta >= -PI) - (teta < -PI));
		dy = abs(dx * tan(teta));
		seg->xf = sym[0] * dx + seg->xi;
		seg->yf = sym[1] * dy + seg->yi;
	}
	if (my_absolute(teta) == (PI / 2) || my_absolute(teta) == (3 * PI / 2)
		|| (dy > 1000000000) || (dy < -1000000000))
		new_update(data, seg, teta);
}

void	draw_view_angle(t_data *data, t_window *win)
{
	int			k;
	double		teta;
	t_segment	*seg;

	k = -90;
	data->teta = angle_round(data->teta);
	seg = malloc(sizeof(t_segment));
	seg->color = RAYS;
	teta = data->teta;
	while (k < 90)
	{
		seg->xi = data->p[0];
		seg->yi = data->p[1];
		teta = data->teta - k * (PI / 540);
		teta = angle_round(teta);
		get_dest(data, win, seg, teta);
		draw_lines(seg, win);
		k++;
	}
	seg->color = PLAYER_RAY;
	seg->xi = data->p[0];
	seg->yi = data->p[1];
	get_dest(data, win, seg, data->teta);
	draw_lines(seg, win);
	free (seg);
}
