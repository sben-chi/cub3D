/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:24 by sben-chi          #+#    #+#             */
/*   Updated: 2023/02/11 17:15:39 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_color(t_data *data, char *element, int k, int len)
{
	int	i;
	int	cl[3];
	int	j;

	j = 4;
	i = -1;
	printf("> %d\n", k);
	while (--j > 0)
		cl[j - 1] = -1;
	while (++i < len)
	{
		i += (element[i] == '+');
		while (element[i] >= 48 && element[i] <= 57 && cl[j] <= 255)
			cl[j] = ((cl[j] + (cl[j] < 0)) * 10) + (element[i++] - 48);
		if (cl[j] > 255)
			exit(printf("Error: invalid nb of color1\n"));
		if (element[i] == ',' && j < 2)
			j++;
		else if (element[i] != '\n')
			exit(printf("Error: invalid nb of color2\n"));
	}
	if (cl[0] < 0 || cl[1] < 0 || cl[2] < 0)
		exit(printf("Error: invalid nb of color: {xxx,xxx,xxx}\n"));
	data->colors[k] = (0 << 24 | cl[0] << 16 | cl[1] << 8 | cl[2]);
}

void	check_colors(t_data *data, int i, char *element, int len)
{
	int	j;

	j = 0;
	if (data->colors[i] >= 0 || element[len - 2] != '\n')
		exit(printf("Error: color: data < \n"));
	while (element[j] && element[j] == ' ')
		j++;
	get_color(data, element + j, i, len - j - 2);
}

void	check_texture(t_data *data, int k, char *element, int len)
{
	int	i;

	i = 0;
	while (element[i] && element[i] == 32)
		i++;
	len = my_strlen(element);
	if (data->textures[k] || element[len - 1] != '\n')
		exit(printf("Error: Texture file\n"));
	element[len - 1] = '\0';
	check_files(element + i, ".xpm");
	data->textures[k] = element + i;
}

short	element(t_data *data, char *element, int len)
{
	static char	*tab[7] = {"NO ", "SO ", "EA ", "WE ", "C ", "F ", NULL};
	int			i;

	i = 0;
	while (tab[i] && strncmp(tab[i], element, strlen(tab[i])))
		i++;
	if (!tab[i])
		return (0);
	if (i < 4)
		check_texture(data, i, element + 2, len);
	else
	{
		check_colors(data, (i == 5), element + 1, len);
		free(element);
	}
	return (1);
}
