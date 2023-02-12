/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:38 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/30 12:11:11 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <mlx.h>

typedef struct mdata
{
	void	*img;
	void	*mlx_img;
	char	*addr;
	char	*add;
	int		bits_per_pixel;
	int		l_line;
	int		ed;
	int		bits_ppixel;
	int		lline;
	int		endian;
}mdata;

unsigned int	my_get_pixel_put(mdata *dt, int x, int y)
{
	return (*(unsigned int *)(dt->addr + (y * dt->lline + x * (dt->bits_per_pixel / 8))));
}

void	my_mlx_pixel_put(mdata *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->add + (y * data->l_line + x * (data->bits_ppixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	t_data	*my_data;
	void	*mlx;
	mdata	img;
	void	*mlx_win;
	int		fd;
	int		w;
	int		h;

	if (ac != 2)
		return (printf("Invalid argument!!\n"));
	my_data = calloc(1, sizeof(t_data));
	init_data(my_data);
	fd = check_files(av[1], ".cub");
	parse_time(my_data, fd);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, my_data->max * 32, my_data->lines * 32, "test");
	img.mlx_img = mlx_new_image(mlx, my_data->max * 32, my_data->lines * 32);
	img.add = mlx_get_data_addr(img.mlx_img, &img.bits_ppixel, &img.l_line, &img.ed);
	img.img = mlx_xpm_file_to_image(mlx, "../map_test/wall.xpm", &w, &h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.lline, &img.endian);
	printf("%d\n", img.bits_ppixel);
	
	t_map *m = my_data->map;
	int y = 0, x, a=0, b=0;
	while (y < 64)
	{
		x = 0;
		b = y / 2;
		while (x < 64)
		{
			a = x / 2;
			printf("> %d\n", a);
			my_mlx_pixel_put(&img, x, y, my_get_pixel_put(&img, a, b));
			my_mlx_pixel_put(&img, x+1, y, my_get_pixel_put(&img, a, b));
			x += 2;
		}
		y += 2;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.mlx_img, 0, 0);
	mlx_loop(mlx);
	//// printf("%d . %d\n", img_width, img_height);
	//printf("=> %zu . %zu\n", my_data->lines, my_data->max);
	//printf("=> %d . %d . %c\n", my_data->player[1], my_data->player[2],
	//	//my_data->player[0]);
	//printf("=> %zu . %zu\n", my_data->lines, my_data->max);
	//printf("=> x:%lld . y:%lld . teta:%lf\n", my_data->p[0], my_data->p[1], my_data->teta);
}


/*
// -----------------------------test_parsing------------------------\\
	for (int i = 0; i < 4; i++)
		printf("textures => %s\n", my_data->textures[i]);
	cl => 14443526 . 14753285
	cl => 6 . 225
	 printf("cl => %d . %d\n", my_data->colors[0], my_data->colors[1]);
	 printf("cl => %d . %d . %d . %d\n", (my_data->colors[0]) & 0xFF,
	 		(my_data->colors[0]) >> 8 & 0xFF, (my_data->colors[0] >> 16)
			& 0xFF, (my_data->colors[0] >> 24) & 0xFF);
	 printf("cl => %d . %d . %d . %d\n", (my_data->colors[1]) & 0xFF,
	 		(my_data->colors[1]) >> 8 & 0xFF, (my_data->colors[1] >> 16) 
			& 0xFF, (my_data->colors[1] >> 24) & 0xFF);
	printf("=> %d . %zu\n", my_data->lines, my_data->max);
	t_map *temp = my_data->map;
	for (; temp; temp = temp->next)
	{
		printf("map => %s . len => %d . prev => ", temp->line, temp->llen);
		if (temp->prev)
			printf("%s", temp->prev->line);
		printf("\n");
	}
	system("leaks cub");
*/
