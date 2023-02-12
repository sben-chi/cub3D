/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:13:44 by irhesri           #+#    #+#             */
/*   Updated: 2023/02/12 17:26:27 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFFER_SIZE	10000

# define STEP		16
# define TILE		64
# define WIDTH		1500
# define HEIGHT		900

// PI FOR LINUX
// # define PI           3.14159265358979323846
// # define PI_2		PI / 2

// PI FOR MAC
# define PI			M_PI
# define PI_2		M_PI_2

// COLORS 	!COLORS SHOULD BE DIFFERENT
// # define WALL		0x52688F
// # define GRID		0x050A30
// # define FLOOR		0xE4F4F3
// # define RAYS		0x296090
// # define PLAYER_RAY	0x000000
// # define PLAYER		0x000000

// KEY CODES FOR LINUX
//  # define UP		65362
//  # define DOWN	65364
//  # define RIGHT	65363
//  # define LEFT	65361		
//  # define W		119		
//  # define S		115		
//  # define A		97		
//  # define D		100	
//  # define ESC		65307

// KEY CODES FOR MAC
# define UP		126
# define DOWN	125
# define RIGHT	124
# define LEFT	123
# define W		13		
# define S		1		
# define A		0	
# define D		2	
# define ESC	53	

#endif
