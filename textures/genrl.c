#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = (!s * -1);
	while (s && s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*p;
	size_t	i;

	total = size * count;
	p = (char *)malloc(total);
	i = -1;
	while (++i < total)
		p[i] = 0;
	return ((void *)p);
}