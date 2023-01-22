/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:56:27 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/22 14:03:18 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

short check_map(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
		if (!data->textures[i])
			exit(printf("Error: wrong elemet\n"));
	if (data->colors[0] == -1 || data->colors[1] == -1)
		exit(printf("Error: wrong elemet\n"));
	return (1);
}

int	check_lines(t_data *data, t_map *last)
{
	static int		i;
	int		b;
	t_map	*t;

	t = data->map;
	while (i++ < t->llen - 2) 
		if (t->line[i] != '1' && t->line[i] != ' ')
			exit(printf("your map doesn't surrounded by walls1\n"));
	i = -1;
	while (++i < last->llen) 
		if ((last->line[i] != '1' && last->line[i] != ' '))
			exit(printf("your map doesn't surrounded by walls2\n"));
	while (t->next->next)
	{
		t = t->next;
		i = 0;
		if ((t->line[i] != ' ' && t->line[i] != '1') 
			|| (t->line[t->llen - 2] != ' ' && t->line[t->llen - 2] != '1'))
			exit(printf("your map doesn't surrounded by walls3\n"));
		while (i++ < t->llen - 2)
		{
			data->p += t->line[i] == 'N' || t->line[i] == 'S'
							|| t->line[i] == 'E'|| t->line[i] == 'W';
			if (t->line[i] == '0')
			{
				if (t->line[i - 1] == ' ' || t->line[i + 1] == ' ' || (t->next && t->next->line[i] != '1' && t->next->line[i] != '0' &&
					t->next->line[i] != 'N' &&t->next->line[i] != 'S' 
					&& t->next->line[i] != 'E' && t->next->line[i] != 'W')
					|| (t->prev && t->prev->line[i] != '1' && t->prev->line[i] != '0' &&
					t->prev->line[i] != 'N' &&t->prev->line[i] != 'S' 
					&& t->prev->line[i] != 'E' && t->prev->line[i] != 'W'))
					exit(printf("Invalid map1\n"));
			}
			else if (data->p > 1 || (t->line[i] != ' ' && t->line[i] != '1' && t->line[i] != 'N' &&
				t->line[i] != 'S' && t->line[i] != 'E' && t->line[i] != 'W'))
						exit(printf("Invalid map2\n"));
			else if (t->line[i] == 'E' || t->line[i] == 'N' || t->line[i] == 'S' || t->line[i] == 'W')
				data->player = t->line[i];
		}
	}
	return (1);
}

void parse_time(t_data *data, int fd)
{
	char	*line;
	static t_map *map_last;
	int		llen;
	short	mapTime;
	short	f;

	line = NULL;
	mapTime = 0;
	while (1)
	{
		line = get_next_line(fd, &llen);
		if (!line)
			break;
		if (!mapTime)
		{
			if (line[0] != '\n')
			{
				mapTime = !element(data, line, llen) && check_map(data);
				f = 1;
			}
			else
				free(line);
		}
		if (mapTime) 
			add_back(&data->map, &map_last, new(line, llen));
	}
	// check_lines(data, map_last);
}
