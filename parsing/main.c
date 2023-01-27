/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:38 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/27 12:14:58 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*my_data;
	int		fd;

	if (ac != 2)
		return (printf("Invalid argument!!\n"));
	my_data = malloc(sizeof(t_data));
	init_data(my_data);
	fd = check_files(av[1], ".cub");
	parse_time(my_data, fd);
	printf("=> %zu . %zu\n", my_data->lines, my_data->max);
	printf("=> %d . %d . %c\n", my_data->player[1], my_data->player[2],
		my_data->player[0]);
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
