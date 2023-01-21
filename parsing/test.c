#include "test.h"

short	check_color_error(int nb, int i, short shift, char *e)
{
	return (nb > 255 || (shift > 16)
			|| (!i && (e[i] < '0' || e[i] > '9')) ||
			(e[i] != ',' && e[i] != '+' && (e[i] < '0' || e[i] > '9')));
}

void	atSplit(t_data *data, char *element, int k, int len)
{
	int		i;
	int		div;
	int		cl[3] = {-1, -1, -1};
	int		j;

	div = 1;
	if (data->colors[k] >= 0 || element[len - 1] != '\n')
		exit(printf("Error: color: data < \n"));
	i = len - 1;
	j = 2;
	while (--i >= 0)
	{
		if (element[i] == ',')
		{
			if (cl[j] < 0 || (!i && cl[0] < 0))
				exit(printf("Error: invalid nb of color1\n"));
			j--;
			div = 1;
		}
		else if (element[i] >= '0' && element[i] <= '9')
		{
			cl[j] += (element[i] - 48) * div + (cl[j] < 0);
			if (cl[j] > 255)
				exit(printf("Error: invalid nb of color2\n"));
			div *= 10;
		}
		if ((j < 0) || (element[i] != ',' && element[i] != '+' && (element[i] < '0' || element[i] > '9')))
			exit(printf("Error: invalid nb of color3\n"));
	}
	if (cl[0] < 0)
		exit(printf("Error: invalid nb of color: {xxx,xxx,xxx}\n"));
	data->colors[k] = (0 << 24 | cl[0] << 16 | cl[1] << 8 | cl[2]);
}

void	check_colors(t_data *data,  int i, char *element, int len)
{
	int j;

	j = 0;
	while (element[j] && element[j] == ' ')
		j++;
	atSplit(data, element + j, i, len - j);
}

void	check_texture(t_data *data, int k,  char *element)
{
	int	i;
	int	len;

	i = 0;
	while (element[i] && element[i] == 32)
		i++;
	len = my_strlen(element, '\0');
	if (data->textures[k] || element[len - 1] != '\n')
		exit(printf("Error: Texture file: data < \n"));
	element[len - 1] = '\0';
	check_files(element + i, ".xpm");
	data->textures[k] = element + i;
}

short	element(t_data *data, char *element, int len)
{
	char	*tab[7] = {"NO ", "SO ", "EA ", "WE ", "C ", "F ", NULL};
	int		i;

	i = 0;
	while(tab[i] && strncmp(tab[i], element, strlen(tab[i])))
		i++;
	if (!tab[i])
		return (0);
	if (i < 4)
		check_texture(data, i, element + 2);
	else
	{
		check_colors(data, (5 - i), element + 1, len - 1);
		free(element);
	}
	return (1);
}

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

// short	is_valid_map(t_map *t, int i, char p)
// {
// 	if (!t->prev && t->line[i] != '1' && t->line[i] != ' ')
// 	{
// 		printf("here1\n");
// 		return (0);
// 	}
// 	if (!t->next && t->line[i] != '1' && t->line[i] != ' ')
// 	{
// 		printf("here2\n");
// 		return (0);
// 	}
// 	if (t->line[i] == '0' && (t->next->line[i] == ' ' || (t->prev && t->prev->line[i] == ' ') 
// 	|| (t->line[i + 1] == ' ' || t->line[i - 1] == ' ')))
// 	{
// 		printf("here3\n");
// 		return (0);
// 	}
// 	if ((t->line[i] != ' ' && t->line[i] != '1' && t->line[i] != 'N' 
// 		&& t->line[i] != 'S' && t->line[i] != 'E' && t->line[i] != 'W' && t->line[i] != '0'))
// 	{
// 		printf("here4\n");
// 		return (0);
// 	}
// 	if ((t->prev || t->next) && ((t->line[0] != ' ' && t->line[0] != '1') 
// 	|| (t->line[t->llen - 2] != ' ' && t->line[t->llen - 2] != '1')))
// 	{
// 		printf(">%s\n", t->line);
// 		return (0);
// 	}
// 	return (1);
// }

// int	check_lines(t_data *data)
// {
// 	static int		i;
// 	int		b;
// 	t_map	*t;

// 	t = data->map;
// 	while (t->next)
// 	{
// 		i = 0;
// 		while (i++ < t->llen - 2)
// 		{
// 			if (!is_valid_map(t, i, data->player))
// 				exit(printf("Invalid map1\n"));
// 			else if (t->line[i] == 'E' || t->line[i] == 'N'
// 				|| t->line[i] == 'S' || t->line[i] == 'W')
// 			{
// 				if (data->player != '0')
// 					exit(printf("error"));
// 				data->player = t->line[i];
// 			}
// 		}
// 		t = t->next;
// 	}
// 	if (data->player == '0')
// 		exit(printf("Invalid map2\n"));
// 	return (1);
// }

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
	// check_lines(data);
}

void	init_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	data->colors[0] = -1;
	data->colors[1] = -1;
	data->map = NULL;
	data->player = '0';
}

int main(int ac, char **av)
{
	t_data	*my_data;
	int		fd;

	if (ac != 2)
		return (printf("Invalid argument!!\n"));
	my_data = malloc(sizeof(t_data));
	init_data(my_data);
	fd = check_files(av[1], ".cub");
	parse_time(my_data, fd);

//-----------------------------test_parsing------------------------\\

	// for (int i = 0; i < 4; i++)
	// 	printf("textures => %s\n", my_data->textures[i]);
	//cl => 14443526 . 14753285
	//cl => 6 . 225
	printf("cl => %d . %d\n", my_data->colors[0], my_data->colors[1]);
	printf("cl => %d . %d . %d . %d\n", (my_data->colors[0]) & 0xFF,
			(my_data->colors[0]) >> 8 & 0xFF, (my_data->colors[0] >> 16) & 0xFF, (my_data->colors[0] >> 24) & 0xFF);
	printf("cl => %d . %d . %d . %d\n", (my_data->colors[1]) & 0xFF,
			(my_data->colors[1]) >> 8 & 0xFF, (my_data->colors[1] >> 16) & 0xFF, (my_data->colors[1] >> 24) & 0xFF);
	// t_map *temp = my_data->map;
	// for (; temp; temp = temp->next)
	// {
	// 	printf("map => %s . len => %d . prev => ", temp->line, temp->llen);
	// 	if (temp->prev)
	// 		printf("%s", temp->prev->line);
	// 	printf("\n");
	// }
	// system("leaks a.out");
}
