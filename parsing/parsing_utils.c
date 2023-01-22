/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:06:24 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/22 14:06:25 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	getColor(t_data *data, char *element, int k, int len)
{
	int		div;
	int		cl[3];
	int		j;

	div = 1;
	j = -2;
	while(++j < 2)
		cl[j + 1] = -1;
	while (--len >= 0)
	{
		if (element[len] == ',' && j > 0)
			div = (j-- >= 0);
		else if (element[len] >= '0' && element[len] <= '9')
		{
			cl[j] += (element[len] - 48) * div + (cl[j] < 0);
			div *= 10;
			if (cl[j] > 255)
				exit(printf("Error: invalid nb of color1\n"));
		}
		else if (element[len] != '+')
			exit(printf("Error: invalid nb of color2\n"));
	}
	if (cl[0] < 0 || cl[1] < 0 || cl[2] < 0)
		exit(printf("Error: invalid nb of color: {xxx,xxx,xxx}\n"));
	data->colors[k] = (0 << 24 | cl[0] << 16 | cl[1] << 8 | cl[2]);
}

void	check_colors(t_data *data,  int i, char *element, int len)
{
	int j;

	j = 0;
	if (data->colors[i] >= 0 || element[len - 2] != '\n')
		exit(printf("Error: color: data < \n"));
	while (element[j] && element[j] == ' ')
		j++;
	getColor(data, element + j, i, len - j - 2);
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
		check_colors(data, (5 - i), element + 1, len);
		free(element);
	}
	return (1);
}
