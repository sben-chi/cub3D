#include "../cub3D.h"

static void	draw_segment(t_segment *seg, t_image *img, int dx, int dy)
{
	int		delta;
	char	*dst;

	delta = 2 * dy - dx;
	while (1)
	{
		dst = img->address + (seg->yi * img->size + seg->xi * img->bit / 8);
		if (*(unsigned int *) dst == WALL || *(unsigned int *) dst == GRID)
			return ;
		*(unsigned int *) dst = seg->color;
		if (delta < 0)
			delta += 2 * dy;
		else
		{
			delta += 2 * (dy - dx);
			!seg->b && (seg->yi += seg->add[1]);
			seg->b && (seg->xi += seg->add[0]);
		}
		!seg->b && (seg->xi += seg->add[0]);
		seg->b && (seg->yi += seg->add[1]);
	}
}

void	draw_lines(t_segment *seg, t_window *win)
{
	long long	dx;
	long long	dy;
	short		add[2];

	dx = abs(seg->xf - seg->xi);
	dy = abs(seg->yf - seg->yi);
	seg->b = (dx < dy);
	seg->add[0] = (seg->xf > seg->xi) - (seg->xf < seg->xi);
	seg->add[1] = (seg->yf > seg->yi) - (seg->yf < seg->yi);
	if (dx >= dy)
		draw_segment(seg, win->image, dx, dy);
	else
		draw_segment(seg, win->image, dy, dx);
}
