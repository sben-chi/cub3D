/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:14:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 19:33:12 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	put_error(char *s, size_t len)
{
	write(2, s, len);
	exit (1);
}

//	is protected (exit in case of error)
void	*my_calloc(size_t count, size_t size)
{
	void	*new;
	size_t	i;

	new = malloc(count * size);
	if (!new)
		put_error("allocation error\n", 17);
	i = -1;
	while (++i < count * size)
		((unsigned char *)new)[i] = 0;
	return (new);
}

bool	**get_map_arr(t_map *map, size_t lines, size_t max)
{
	bool	**arr;
	ssize_t	i;
	ssize_t	j;

	i = -1;
	arr = my_calloc(lines + 1, sizeof(bool *));
	while (++i < lines)
	{
		j = -1;
		arr[i] = my_calloc(max, sizeof(bool));
		while (map->line[++j])
			arr[i][j] = (map->line[j] == '1');
		map = map->next;
	}
	arr[i] = NULL;
	return (arr);
}
