/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-chi <sben-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/11 19:27:59 by sben-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "stdbool.h"

typedef struct s_image
{
	int		bits;
	int		len;
	int		endian;
	char	*address;
	void	*img;

	// for any size of xpm file
	int h_img;
	int w_img;
} t_image;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_image		*image;
} t_window;

typedef struct s_map
{
	char			*line;
	long long		llen;
	struct s_map	*next;
	struct s_map	*prev;
} t_map;

typedef	struct s_keys
{
	bool	esc;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	l_rotate;
	bool	r_rotate;
} t_keys;

typedef struct s_data
{
	int			colors[2];
	char		*textures[4];
	t_map		*map;
	size_t		max;
	size_t		lines;

	bool		*inter;
	bool		**map_arr;
	short		*dir;
	t_keys		*keys;
	double		*diff;
	double		*rays;
	double		teta;
	double		p[2];
	t_window	*win;
	t_window	*tst;	// 2D MAP (delete)
	
} t_data;

typedef struct s_segment
{
	short			b;
	short			add[2];
	long			color;
	long long		xi;
	long long		yi;
	long long		xf;
	long long		yf;
} t_segment;

#endif
