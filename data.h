/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imane <imane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/14 13:26:38 by imane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "stdbool.h"

# define STEP		16
# define TILE		64
# define WIDTH		1500
# define HEIGHT		900
# define BUFFER_SIZE 10000

typedef struct s_image
{
	int		len;
	int		bits;
	int		h_img;
	int		w_img;
	int		endian;
	char	*address;
	void	*img;
}	t_image;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_image		*image;
}	t_window;

typedef struct s_map
{
	char			*line;
	long long		llen;
	struct s_map	*next;
	struct s_map	*prev;
}	t_map;

typedef struct s_keys
{
	bool	up;
	bool	esc;
	bool	down;
	bool	left;
	bool	right;
	bool	l_rotate;
	bool	r_rotate;
}	t_keys;

typedef struct s_data
{
	int			colors[2];
	bool		*inter;
	bool		**map_arr;
	char		*textures[4];
	short		*dir;
	t_map		*map;
	size_t		max;
	size_t		lines;
	t_keys		*keys;
	double		*diff;
	double		*rays;
	double		teta;
	double		p[2];
	t_window	*win;
}	t_data;

#endif
