/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:56:27 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/23 13:43:28 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

short check_mapTime(t_data *data)
{
	int i;

	i = -1;
	while (++i < 4)
		if (!data->textures[i])
			exit(printf("Error: invalid elements\n"));
	if (data->colors[0] == -1 || data->colors[1] == -1)
		exit(printf("Error: invalid elements\n"));
	return (1);
}

short	is_valid(t_map *t, char *player, int i)
{
	if ((t->line[i] == '0') && (!i || i == t->llen - 2 || t->line[i - 1] == ' ' 
		|| t->line[i + 1] == ' ' || (t->next && (t->next->llen < i
		|| t->next->line[i] == ' ' || t->next->line[i] == '\n'))
		|| (t->prev && (t->prev->llen < i || t->prev->line[i] == ' ' || t->prev->line[i] == '\n'))))
			return (0);
	else if ((t->line[i] != '0' && t->line[i] != ' ' && t->line[i] != '1' && t->line[i] != 'N' &&
		t->line[i] != 'S' && t->line[i] != 'E' && t->line[i] != 'W'))
			return (0);
	else if (t->line[i] == 'E' || t->line[i] == 'N' 
		|| t->line[i] == 'S' || t->line[i] == 'W')
	{
		if (*player != '0')
			return (0);
		*player = t->line[i];
	}
	return (1);
}

int	check_lines(t_data *data)
{
	short			b;
	int				i;
	t_map			*t;

	t = data->map;
	b = 0;
	while (t)
	{
		i = -1;
		b = (!t->prev || !t->next);
		while (++i < t->llen - 1)
		{
			if (b && t->line[i] != '1' && t->line[i] != ' ')
				exit(printf("Error: your map doesn't surrounded by walls\n"));
			else if (!is_valid(t, &data->player, i))
				exit(printf("Error: Invalid map\n"));
		}
		t = t->next;
	}
	if (data->player == '0')
		exit(printf("Error: Invalid map\n"));
	return (1);
}

void parse_time(t_data *data, int fd)
{
	char	*line;
	static t_map *map_last;
	int		llen;
	short	mapTime;

	line = get_next_line(fd, &llen);
	mapTime = 0;
	while (line)
	{
		if (line[0] != '\n')
		{
			mapTime = !element(data, line, llen) && check_mapTime(data);
			mapTime && add_back(&data->map, &map_last, new(line, llen));
		}
		else if (line[0] == '\n' && !mapTime)
			free(line);
		else
			exit(printf("Error: invalid map2\n"));
		line = get_next_line(fd, &llen);
	}
	check_lines(data);
}
