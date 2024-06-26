/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 20:16:17 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	inventory(t_mlx *mlx, void *img, int need_free);

int	window(int event, void *mlx_ptr)
{
	t_mlx	*mlx;

	if (event == 0)
	{
		mlx = (t_mlx *)mlx_ptr;
		destroy_textures(mlx);
		raycasting(mlx, 1);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free_all_graphics(mlx);
		exit(0);
	}
	return (0);
}

void	graphics_part(t_map *map)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	if (init(mlx, map))
	{
		ft_printf("Cube3d: Error init()\n");
		return ;
	}
	mlx->mlx = mlx_init();
	if (load_textures(mlx))
	{
		free(mlx);
		return ;
	}
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx_on_event(mlx->mlx, mlx->win, MLX_WINDOW_EVENT, window, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYDOWN, &keyboard_down, (void *)mlx);
	mlx_on_event(mlx->mlx, mlx->win, MLX_KEYUP, &keyboard_up, (void *)mlx);
	mlx_loop_hook(mlx->mlx, update, mlx);
	mlx_loop(mlx->mlx);
}
