/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:42 by sben-chi          #+#    #+#             */
/*   Updated: 2023/01/17 13:41:44 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*cat_copy(char *s1, char *s2, int len)
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
	while (i <= (len - 1))
		t[i++] = s2[j++];
	t[i] = '\0';
	i = 0;
	while (s2[j])
		(s2)[i++] = (s2)[j++];
	(s2)[i] = '\0';
	return (t);
}

char	*t_return(int fd, int a, char *buff)
{
	char	*t;
	int		t_len;

	t = NULL;
	t_len = 0;
	while (buff[a] != '\n')
	{
		if (buff[a] == '\0')
		{
			t_len += a;
			t = cat_copy(t, buff, t_len);
			a = read(fd, buff, BUFFER_SIZE);
			if (a <= 0)
				return (t);
			buff[a] = '\0';
			a = -1;
		}
		a++;
	}
	t_len += a + 1;
	return (cat_copy(t, buff, t_len));
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*t;

	if (fd <= -1 || fd >= OPEN_MAX)
		return (NULL);
	if (!buff)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		buff[0] = '\0';
	}
	t = t_return(fd, 0, buff);
	if (!*buff)
	{
		free (buff);
		buff = NULL;
	}
	return (t);
}
