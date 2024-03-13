/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:58:17 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/13 22:09:19 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_block {
	EMPTY,
	END,
	WALL,
	FLOOR
}	t_block;

typedef struct s_texture {
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_vec4 {
	float	x;
	float	y;
	float	z;
	float	h;
}	t_vec4;

typedef struct s_map {
	t_block		**blocks;

	t_texture	texture;
	t_vec4		playerPos;
}	t_map;

void	graphics_part(t_block map[30][100]);

t_map	*parse_map(char *filename);

// free utils
void	free_blocks(t_block **blocks);
void	free_map(t_map *map);

#endif