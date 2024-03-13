/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:01:53 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/13 22:17:39 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mlx.h"
# include "cub3d.h"

# define WIDTH 1900
# define HEIGHT 950

typedef struct s_mouse
{
	bool	pressed;
	int		x;
	int		y;
}	t_mouse;

typedef struct s_mlx
{
	t_map	*map;
	void    *mlx;
	void    *win;
	void	*img;
}   t_mlx;


/* ------ map.c ------------------------------------------------------------ */
void	larg_map(t_mlx *mlx);

/* ------ free_all.c ------------------------------------------------------- */
void	free_all_graphics(t_mlx *mlx);

#endif