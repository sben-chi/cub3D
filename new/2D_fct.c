#include "../cub3D.h"

void	draw_tst(t_data *data, double *ptr)
{
	t_segment	*seg;
		
	seg = malloc(sizeof(t_segment));
	seg->xf = round(ptr[0]);
	seg->yf = round(ptr[1]);
	seg->xi = data->p[0];
	seg->yi = data->p[1];
	seg_init(seg, data->tst->image);
	free(seg);
}


void	new_image_tst(t_data *data, t_window *win)
{
	void		*img;
	void		*tmp;
	char		*a;

	img = mlx_new_image(win->mlx, (data->max - 1) * TILE, (data->lines) * TILE);
	a = mlx_get_data_addr(img, &(win->image->bits), &(win->image->len), &(win->image->endian));
	win->image->address = a;
	tmp = win->image->img;
	win->image->img = img;
	draw_map(data, win->image);
	draw_view_angle(data, win);
	mlx_clear_window(win->mlx, win->win);
	// mlx_put_image_to_window (win->mlx, win->win, img, 0, 0);
	(tmp) && mlx_destroy_image(win->mlx, tmp);
}

void	init_data_tst(t_data *data)
{
	t_window *win = (t_window *) my_calloc(1, sizeof(t_window));
	// win->mlx = data->win->mlx;
	// win->win = mlx_new_window(win->mlx, (data->max - 1) * TILE, (data->lines) * TILE, "map");
	win->image = my_calloc(1, sizeof(t_image));
	data->tst = win;
}