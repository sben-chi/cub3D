#include "test.h"

void	atSplit(t_data *data, char *element, int k)
{
	int		i;
	int		div;
	int		nb;
	short	shift;
	
	i = my_strlen(element, '\0') - 1;
	div = 1;
	nb = 0;
	shift = 0;
	if (element[i] != '\n')
		exit(printf("Error: color: data < \n"));
	while (--i >= 0)
	{
		if (element[i] >= '0' && element[i] <= '9')
		{
			nb += (element[i] - 48) * div;
			div *= 10;
			if (i > 0)
				continue ;
		}
		printf(">> %d\n", nb);
		if (nb > 255)
			exit(printf("Error: invalid nb of color1\n"));
		data->colors[k] |= nb << shift;

		if ((shift > 16) || element[i - 1] == ',' || (element[i] != ',' && element[i] != '+' && (element[i] < '0' || element[i] > '9')))
			exit(printf("Error: invalid nb of color2\n"));
		shift += 8;
		nb = 0;
		div = 1;
	}
	if (shift < 16)
		exit(printf("Error: invalid nb of color: {xxx,xxx,xxx}\n"));
	data->colors[k] |= 0 << 24;
}

void	check_colors(t_data *data,  int i, char *element)
{
	int j;

	j = 0;
	while (element[j] && element[j] == ' ')
		j++;
	atSplit(data, element + j, i);
}

char	*check_texture(char *element)
{
	int	i;
	int	len;

	i = 0;
	while (element[i] && element[i] == 32)
		i++;
	len = my_strlen(element, '\0');
	if (element[len - 1] != '\n')
		exit(printf("Error: Texture file: data < \n"));
	element[len - 1] = '\0';
	check_files(element + i, ".xpm");
	return (element + i);
}

short	element(t_data *data, char *element)
{
	char	*tab[7] = {"NO ", "SO ", "EA ", "WE ", "C ", "F ", NULL};
	int		i;

	i = 0;
	while(tab[i] && strncmp(tab[i], element, strlen(tab[i])))
		i++;
	if (!tab[i])
		return (0);
	if (i < 4)
		data->textures[i] = check_texture(element + 2);
	else
	{
		check_colors(data, (5 - i), element + 1);
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

int	first_last_line(char *line, int len)
{
	int i;
	
	i = 0;
//	while (i < )
	return (0);
}

/*

F 220,100,6
C 225,30,5

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000010101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111*/


int	parseMap(t_data *data, char *line, int len)
{
	static t_map *map_last;

	line[len - 1] = '\0';
	add_back(&data->map, &map_last, new(line, len));
	return (1);
}

void parse_time(t_data *data, int fd)
{
	char	*line;
	int		llen;
	short	mapTime;

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
				mapTime = !element(data, line) && check_map(data);
			else
				free(line);
		}
		mapTime && parseMap(data, line, llen);
	}
}

void	init_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	data->colors[0] = 0;
	data->colors[1] = 0;
	data->map = NULL;
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

//	for (int i = 0; i < 4; i++)
//		printf("textures => %s\n", my_data->textures[i]);
	//cl => 14443526 . 14753285
	//cl => 6 . 225
	printf("cl => %d . %d\n", my_data->colors[0], my_data->colors[1]);
	printf("cl => %d . %d . %d . %d\n", (my_data->colors[0]) & 0xFF,
			(my_data->colors[0]) >> 8 & 0xFF, (my_data->colors[0] >> 16) & 0xFF, (my_data->colors[0] >> 24) & 0xFF);
//	t_map *temp = my_data->map;
//	for (; temp; temp = temp->next)
//		printf("map => %s . len => %d\n", temp->line, temp->llen);
//	system("leaks a.out");
}
