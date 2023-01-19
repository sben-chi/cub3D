#include "test.h"

int my_strlen(char *s, char limit)
{
    int i;

    i = 0;
    while (s[i] != limit)
        i++;
    return (i);
}

int check_files(char *s1, char *s2)
{
    int     i;
    int     j;
    int     len;
    int     fd;

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

t_map	*new(char *line, int len)
{
	t_map	*new;

	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = line;
	new->llen = len;
	new->next = NULL;
	new->prev  = NULL;
	return (new);
}

int	add_back(t_map **map, t_map **last, t_map *nnode)
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
