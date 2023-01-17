#include "test.h"

void	atSplit(t_data *data, char *element, int k)
{
	int		i;
	int		div;
	int		j;
	
	i = my_strlen(element, '\0') - 1;
	div = 1;
	j = 0;
	if (element[i] != '\n')
		exit(printf("Error: color: data < \n"));
	j = 2;
	while (--i >= 0)
	{
		if (element[i] == ',')
		{
			if (data->colors[k][j] < 0 || data->colors[k][j] > 255)
				exit(printf("Error: invalid nb of color1\n"));
			j--;
			div = 1;
		}
		else if (element[i] >= '0' && element[i] <= '9')
		{
			if (data->colors[k][j] < 0)
				data->colors[k][j] = 0;
			data->colors[k][j] += (element[i] - 48) * div;
			div *= 10;
		}
		if ((j < 0) || (element[i] != ',' && element[i] != '+' && (element[i] < '0' || element[i] > '9')))
			exit(printf("Error: invalid nb of color2\n"));
	}
	if (data->colors[k][0] < 0)
		exit(printf("Error: invalid nb of color: {xxx,xxx,xxx}\n"));
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
	i = -1;
	while (++i < 2)
	{
		j = 0;
		while (j++ < 3)
			if (data->colors[i][j] == -1)
				exit(printf("Error: wrong elemet\n"));
	}
	return (1);
}

int	parseMap(t_data *data, char *line)
{
	static t_map *map_last;

	add_back(&data->map, &map_last, new(line));
	return (1);
}

void parse_time(t_data *data, int fd)
{
	char	*line;
	short	mapTime;

	line = NULL;
	mapTime = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!mapTime)
		{
			if (line[0] != '\n')
				mapTime = !element(data, line) && check_map(data);
			else
				free(line);
		}
		mapTime && parseMap(data, line);
	}
}

void	init_data(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			data->colors[i][j] = -1;
	}
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

	for (int i = 0; i < 4; i++)
		printf("textures => %s\n", my_data->textures[i]);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			printf("colors => %d\n", my_data->colors[i][j]);
	t_map *temp = my_data->map;
	for (; temp; temp = temp->next)
		printf("map => %s", temp->line);
	system("leaks a.out");
}
