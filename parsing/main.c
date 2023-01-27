/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:38 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/26 17:56:32 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

typedef struct mdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		lline;
	int		endian;
}mdata;

void	my_mlx_pixel_put(mdata *dt, int x, int y)
{
	char *dst;
	dst = dt->addr + (y * dt->lline + x * (dt->bits_per_pixel / 8));
	//*(unsigned int*)dst = color;
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
	my_data = malloc(sizeof(t_data));
	init_data(my_data);
	fd = check_files(av[1], ".cub");
	parse_time(my_data, fd);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, my_data->max * 32, my_data->lines * 32, "test");
	img.img = mlx_xpm_file_to_image(mlx, "../map_test/wall.xpm", &w, &h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.lline, &img.endian);
	
	t_map *m = my_data->map;
	int y = -1, x;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			my_mlx_pixel_put(&img, x, y);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	// printf("%d . %d\n", img_width, img_height);
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
