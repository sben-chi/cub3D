/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:46 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 13:57:58 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int	my_get_pixel_color(t_image *dt, long long x, long long y)
{
	return (*(unsigned int *)(dt->address
		+ (y * dt->len + x * (dt->bits / 8))));
}

t_image	*get_imgs_data(t_data *dt, long x)
{
	static t_image	*text_img;
	int				i;

	if (!text_img)
	{
		i = 0;
		text_img = malloc(4 * sizeof(t_image));
		while (i < 4)
		{
			text_img[i].img = mlx_xpm_file_to_image(dt->win->mlx,
					dt->textures[i], &text_img[i].w_img, &text_img[i].h_img);
			if (!text_img[i].img)
				exit(printf("Error: xpm_file\n"));
			text_img[i].address = mlx_get_data_addr(text_img[i].img,
					&text_img[i].bits, &text_img[i].len, &text_img[i].endian);
			i++;
		}
	}
	i = (dt->dir[x] == 'S') + (dt->dir[x] == 'E') * 2 + (dt->dir[x] == 'W') * 3;
	return (&text_img[i]);
}

void	textures(t_data *dt, long long x, long long *y, double wall_h)
{
	long	img_x;
	long	img_y;
	char	*dst;
	t_image	*win_img;
	t_image	*img_text;

	win_img = dt->win->image;
	img_text = get_imgs_data(dt, x);
	img_x = (long)(dt->diff[x] * (img_text->w_img / TILE)) % img_text->w_img;
	while ((y[0] < y[1]) && (y[0] < HEIGHT))
	{
		img_y = ((y[0] - ((HEIGHT - wall_h) / 2)) * (img_text->h_img / wall_h));
		dst = win_img->address + (y[0] * win_img->len + x * win_img->bits / 8);
		*(unsigned int *) dst = my_get_pixel_color(img_text, img_x, img_y);
		++y[0];
	}
}

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

	k = (WIDTH / 2);
	x = -1;
	while (++x < WIDTH)
	{
		k += (x > (WIDTH / 2)) - (x <= (WIDTH / 2));
		(rays[x] < 1) && (rays[x] = 1);
		wall_h = round((TILE / rays[x]) * ((WIDTH / 2) / tan((PI / 6))));
		dst_proj = round((HEIGHT - wall_h) / 2);
		y[0] = 0;
		y[1] = dst_proj * (dst_proj > 0);
		draw_segment(cub, x, y, data->colors[0]);
		y[1] += wall_h;
		textures(data, x, y, wall_h);
		y[1] = HEIGHT;
		draw_segment(cub, x, y, data->colors[1]);
	}
}
