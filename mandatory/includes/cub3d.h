/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:58:17 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/20 15:34:35 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <SDL2/SDL.h>

typedef struct s_mlx	t_mlx;

typedef enum e_block
{
	EMPTY,
	END,
	WALL,
	FLOOR
}	t_block;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	h;
}	t_vec4;

typedef struct s_map
{
	t_block		**blocks;
	size_t		width;
	size_t		height;

	t_texture	texture;
	t_vec4		player_pos;
}	t_map;

/* --- main_graphics.c ----------------------------------------------------- */
void		graphics_part(t_map *map);

/* --- parse_file.c -------------------------------------------------------- */
t_map		*parse_map(char *filename);

/* --- free_map.c ---------------------------------------------------------- */
void		free_blocks(t_block **blocks);
void		free_map(t_map *map);

/* --- utils.c ------------------------------------------------------------- */
void		*error_ptr(char *str, void *ret);
int			error_int(char *str, int ret);

#endif