/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 13:56:27 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/28 18:39:16 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

short	check_maptime(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (!data->textures[i])
			exit(printf("Error: invalid elements\n"));
	if (data->colors[0] == -1 || data->colors[1] == -1)
		exit(printf("Error: invalid elements\n"));
	return (1);
}

short	exist_err(t_map *t, int i)
{
	short	a;
	short	b;

	a = (t->next && ((t->next->llen < (size_t)i) || t->next->line[i] == ' '
				|| t->next->line[i] == '\n' || !t->next->line[i]));
	b = (t->prev && (t->prev->llen < (size_t)i || t->prev->line[i] == ' '
				|| t->prev->line[i] == '\n'));
	return (!i || (size_t)i == t->llen - 2 || t->line[i - 1] == ' '
		|| t->line[i + 1] == ' ' || a || b);
}

short	is_valid(t_map *t, t_data *data, int i)
{
	short		b;
	static char	str[] = "NSEW 01";

	b = 0;
	while (str[b] && str[b] != t->line[i])
		b++;
	if ((((t->line[i] == '0') || t->line[i] == 'N') && exist_err(t, i))
		|| b == 7 || (b < 4 && data->teta != -1))
		return (0);
	if (b < 4)
	{
		data->player[0] = i + 1;
		data->player[1] = data->lines;
		data->teta = (3 * PI / 2) * (t->line[i] == 'S')
			+  PI * (t->line[i] == 'N') + (PI / 2) * (t->line[i] == 'W');
	}
	return (1);
}

int	check_lines(t_data *data)
{
	short	b;
	int		i;
	t_map	*t;

	t = data->map;
	b = 0;
	while (t)
	{
		i = -1;
		b = (!t->prev || !t->next);
		data->lines++;
		while (++i < (int)t->llen - 1)
			if ((b && t->line[i] != '1' && t->line[i] != ' ') || !is_valid(t, data, i))
				exit(printf("Error: Invalid map\n"));
		t = t->next;
	}
	if (data->player[0] < 0)
		exit(printf("Error: Invalid map\n"));
	return (1);
}

void	parse_time(t_data *data, int fd)
{
	char			*line;
	static t_map	*map_last;
	size_t			llen;
	short			map_time;

	line = get_next_line(fd, &llen);
	map_time = 0;
	while (line)
	{
		if (line[0] != '\n')
		{
			map_time = (!element(data, line, llen) && check_maptime(data));
			(map_time && add_back(&data->map, &map_last, new(line, llen)));
			data->max = map_time * ((llen > data->max) * llen
					+ (llen <= data->max) * data->max);
		}
		else if (line[0] == '\n' && !map_time)
			free(line);
		else
			exit(printf("Error: invalid map2\n"));
		line = get_next_line(fd, &llen);
	}
	check_lines(data);
}
