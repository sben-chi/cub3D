#include "../cub3D.h"

static void	draw_grid(t_image *img, long long x, long long y, long color)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	while (++i < TILE)
	{
		j = -1;
		while (++j < TILE)
		{
			dst = img->address + (y * img->size + (x + j) * img->bit / 8);
			if (color != FLOOR && (j == 0 || i == 0 || i == 63 || j == 63))
				*(unsigned int *) dst = GRID;
			else
				*(unsigned int *) dst = color;
		}
		y++;
	}
}

void	draw_map(t_image *img, t_data *data)
{
	int		i;
	int		j;
	t_map	*map;

	i = -1;
	map = data->map;
	while (++i < data->lines)
	{
		j = -1;
		while (map->line[++j])
		{
			if (map->line[j] == '1')
				draw_grid(img, j * TILE, i * TILE, WALL);
			else if (map->line[j] != ' ' && map->line[j] != '\n')
				draw_grid(img, j * TILE, i * TILE, FLOOR);
		}
		map = map->next;
	}
}
