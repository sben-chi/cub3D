# include "../cub3D.h"

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

void	draw_walls(t_image *cub, double *rays, bool *inter)
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
		if (rays[x] < 1)
			rays[x] = 1;
		wall_h = round((TILE / rays[x]) * PROJ_DST);
		dst_proj = round((HEIGHT - wall_h) / 2);
		y[0] = 0;
		y[1] = dst_proj * (dst_proj > 0);
		draw_segment(cub, x, y, FLOOR);
		y[1] += wall_h;
		draw_segment(cub, x, y, WALL);
		y[1] = HEIGHT;
		draw_segment(cub, x, y, GRID);
	}
}
