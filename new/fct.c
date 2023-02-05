#include "../cub3D.h"

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
