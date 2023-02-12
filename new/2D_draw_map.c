#include "../cub3D.h"

static void	draw_player(t_image *img, long long x, long long y, long color)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			dst = img->address + (y * img->len + (x + j) * img->bits / 8);
			*(unsigned int *) dst = color;
		}
		y++;
	}
}

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
			dst = img->address + (y * img->len + (x + j) * img->bits / 8);
			if (color != FLOOR && (j == 0 || i == 0 || i == 63 || j == 63))
				*(unsigned int *) dst = GRID;
			else
				*(unsigned int *) dst = color;
		}
		y++;
	}
}

void	draw_map(t_data *data, t_image *img)
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
	draw_player(img, data->p[0] - 2, data->p[1] - 2, PLAYER);
}
