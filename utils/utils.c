/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:19:38 by sben-chi          #+#    #+#             */
/*   Updated: 2023/02/12 13:45:13 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	my_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

t_map	*new(char *line, int len)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = line;
	new->llen = len;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

short	add_back(t_map **map, t_map **last, t_map *nnode)
{
	if (!nnode)
		return (1);
	if (*map)
		nnode->prev = *last;
	else
	{
		(*map) = nnode;
		(*last) = (*map);
	}	
	(*last)->next = nnode;
	(*last) = (*last)->next;
	return (1);
}

bool	put_error(char *s, size_t len)
{
	write(2, s, len);
	exit (1);
}

//	is protected (exit in case of error)
void	*my_calloc(size_t count, size_t size)
{
	void	*new;
	ssize_t	i;

	new = malloc(count * size);
	if (!new)
		put_error("allocation error\n", 17);
	i = -1;
	while (++i < (ssize_t)(count * size))
		((unsigned char *)new)[i] = 0;
	return (new);
}
