#include "../cub3D.h"

static void	draw_segment_up(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	int		color;
	char	*dst;

	color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && seg->xi <= seg->xf) || (seg->b && seg->yi <= seg->yf))
	{
		dst = img->address + (seg->yi * img->len + seg->xi * img->bits / 8);
		*(unsigned int *) dst = color;
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && seg->yi++;
			seg->b && seg->xi++;
		}
		!seg->b && seg->xi++;
		seg->b && seg->yi++;
	}
}

static void	draw_segment_down(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	int		color;
	char	*dst;

	color = seg->color;
	delta = 2 * dy - dx;
	while ((!seg->b && seg->xi >= seg->xf) || (seg->b && seg->yi <= seg->yf))
	{
		dst = img->address + (seg->yi * img->len + seg->xi * img->bits / 8);
		*(unsigned int *) dst = color;
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && seg->yi++;
			seg->b && seg->xi--;
		}
		!seg->b && seg->xi--;
		seg->b && seg->yi++;
	}
}

void	seg_init(t_segment *seg, t_image *map)
{
	double	tmp;
	int		dx;
	int		dy;

	if (seg->yf < seg->yi)
	{
		tmp = seg->yf;
		seg->yf = seg->yi;
		seg->yi = tmp;
		tmp = seg->xf;
		seg->xf = seg->xi;
		seg->xi = tmp;
	}
	seg->color = 0xFF0000;
	dx = llabs(seg->xf - seg->xi);
	dy = llabs(seg->yf - seg->yi);
	seg->b = (dx < dy);
	if ((seg->xf >= seg->xi) && (dx >= dy))
		draw_segment_up(seg, map, dx, dy);
	else if (seg->xf >= seg->xi)
		draw_segment_up(seg, map, dy, dx);
	else if (dx >= dy)
		draw_segment_down(seg, map, dx, dy);
	else
		draw_segment_down(seg, map, dy, dx);
}

