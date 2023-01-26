/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:38 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/26 17:56:47 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"
#include <mlx.h>

typedef struct mdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		lline;
	int		endian;
}mdata;

void	my_mlx_pixel_put(mdata *dt, int x, int y, int color)
{
	char *dst;
	dst = dt->addr + (y * dt->lline + x * (dt->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	t_data	*my_data;
	void	*mlx;
	void	*img;
	int		fd;
	// int		img_width;
	// int		img_height;

	if (ac != 2)
		return (printf("Invalid argument!!\n"));
	my_data = malloc(sizeof(t_data));
	init_data(my_data);
	fd = check_files(av[1], ".cub");
	parse_time(my_data, fd);
	mlx = mlx_init();
	img = mlx_new_window(mlx, my_data->max * 32, my_data->lines * 32, "test");
	mlx_loop(mlx);
	// printf("%d . %d\n", img_width, img_height);
}
