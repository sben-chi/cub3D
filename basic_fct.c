#include "cub3D.h"

bool	put_error(char *s, size_t len)
{
	write(2, s, len);
	return (0);
}

//	is protected (exit in case of error)
void	*my_calloc(size_t count, size_t size)
{
	void	*new;
	size_t	i;

	new = malloc(count * size);
	if (!new)
		exit (put_error("allocation error\n", 17));
	i = -1;
	while (++i < count * size)
		((unsigned char *)new)[i] = 0;
	return (new);
}
