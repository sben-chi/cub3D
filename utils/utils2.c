/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:42 by sben-chi          #+#    #+#             */
/*   Updated: 2023/02/12 13:55:36 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


int	check_files(char *s1, char *s2)
{
	int	i;
	int	j;
	int	len;
	int	fd;

	len = strlen(s1);
	i = len - 1;
	j = 3;
	while (i > len - 5)
	{
		if (s1[i--] != s2[j--] || i < 0)
			exit(printf("your file's extension is wrong\n"));
	}
	fd = open(s1, O_RDONLY);
	if (fd < 0)
		exit(printf("No such file or directory\n"));
	return (fd);
}

bool	**get_map_arr(t_map *map, size_t lines, size_t max)
{
	bool	**arr;
	ssize_t	i;
	ssize_t	j;

	i = -1;
	arr = my_calloc(lines + 1, sizeof(bool *));
	while (++i < (ssize_t)(lines))
	{
		j = -1;
		arr[i] = my_calloc(max + 1, sizeof(bool));
		while (map->line[++j])
			arr[i][j] = (map->line[j] == '1');
		map = map->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*cat_copy(char *s1, char *s2, size_t len)
{
	char	*t;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !*s2)
		return (NULL);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	while (s1 && (s1)[j])
		t[i++] = s1[j++];
	if (s1)
		free (s1);
	j = 0;
	while (i <= ((int)len - 1))
		t[i++] = s2[j++];
	t[i] = '\0';
	i = 0;
	while (s2[j])
		(s2)[i++] = (s2)[j++];
	(s2)[i] = '\0';
	return (t);
}

char	*t_return(int fd, size_t a, char *buff, size_t *t_len)
{
	char	*t;

	t = NULL;
	*t_len = 0;
	while (buff[a] != '\n')
	{
		if (buff[a] == '\0')
		{
			*t_len += a;
			t = cat_copy(t, buff, *t_len);
			a = read(fd, buff, BUFFER_SIZE);
			if (a <= 0)
				return (t);
			buff[a] = '\0';
			a = -1;
		}
		a++;
	}
	*t_len += a + 1;
	return (cat_copy(t, buff, *t_len));
}

char	*get_next_line(int fd, size_t *t_len)
{
	static char	*buff;
	char		*t;

	if (fd <= -1)
		return (NULL);
	if (!buff)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		buff[0] = '\0';
	}
	t = t_return(fd, 0, buff, t_len);
	if (!*buff)
	{
		free (buff);
		buff = NULL;
	}
	return (t);
}
