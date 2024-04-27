/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keyboard_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:17:14 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"
#include <time.h>

#define MOVE_TIME_US 33333.33

void	move_player(t_mlx *mlx, float deltaX, float deltaY)
{
	float				add_val;
	t_vec3				*ply_pos;
	t_block				block;

	ply_pos = &(mlx->map->player_pos);
	add_val = deltaX * mlx->map->cam_dir.x - deltaY * mlx->map->cam_dir.y;
	block = mlx->map->blocks[(int)ply_pos->y][(int)(ply_pos->x + add_val)];
	if (block.type != WALL && (block.type != DOOR || block.data.door == true))
		ply_pos->x += add_val;
	add_val = deltaX * mlx->map->cam_dir.y + deltaY * mlx->map->cam_dir.x;
	block = mlx->map->blocks[(int)(ply_pos->y + add_val)][(int)ply_pos->x];
	if (block.type != WALL && (block.type != DOOR || block.data.door == true))
		ply_pos->y += add_val;
	if (mlx->game_server.status == CONNECTED)
		dprintf(mlx->game_server.sockfd, "setPos:%.2f,%.2f,%.2f;",
			ply_pos->x, ply_pos->y, ply_pos->z);
}

void	interract_block(t_mlx *mlx)
{
	t_raydata	*front_ray;

	front_ray = raycast(mlx, mlx->stg->width / 2, true, mlx->map->player_pos);
	if (front_ray->found && front_ray->dist < 2
		&& (mlx->center_sprite.e_type == NONE
			|| mlx->center_sprite.depth >= front_ray->dist))
	{
		if (front_ray->block->type == DOOR)
		{
			front_ray->block->data.door = !front_ray->block->data.door;
			if (mlx->game_server.status == CONNECTED)
				ft_dprintf(mlx->game_server.sockfd, "setDoorState:%d,%d,%d;",
					front_ray->block->data.door, (int) front_ray->pos.x,
					(int) front_ray->pos.y);
		}
	}
	else if (mlx->center_sprite.e_type == SPRT_HEALTH_KIT
		&& mlx->center_sprite.depth < 6)
	{
		mlx->player->health = 100;
		if (mlx->game_server.status == CONNECTED)
			ft_dprintf(mlx->game_server.sockfd, "takeHealthKit:%d;",
				mlx->center_sprite.u_data.kit->id);
	}
}

static inline bool	is_moving_diag(t_mlx *mlx)
{
	return ((is_key_down(mlx->keyboard, KEY_W)
			&& is_key_down(mlx->keyboard, KEY_A))
		|| (is_key_down(mlx->keyboard, KEY_W)
			&& is_key_down(mlx->keyboard, KEY_D))
		|| (is_key_down(mlx->keyboard, KEY_S)
			&& is_key_down(mlx->keyboard, KEY_A))
		|| (is_key_down(mlx->keyboard, KEY_S)
			&& is_key_down(mlx->keyboard, KEY_D)));
}

void	game_keyboard(t_mlx *mlx)
{
	static long long	last_move;
	float				add;
	float				add_x;
	float				add_y;

	add = 0.12;
	if (get_now_time() - last_move < MOVE_TIME_US)
		return ;
	last_move = get_now_time();
	if (is_moving_diag(mlx))
		add = add / 1.5;
	add_x = (is_key_down(mlx->keyboard, KEY_W)
			- is_key_down(mlx->keyboard, KEY_S)) * add;
	add_y = (is_key_down(mlx->keyboard, KEY_D)
			- is_key_down(mlx->keyboard, KEY_A)) * add;
	if (add_x || add_y)
		move_player(mlx, add_x, add_y);
	if (is_key_down(mlx->keyboard, KEY_UP))
		mlx->just_try += 25;
	if (is_key_down(mlx->keyboard, KEY_DOWN))
		mlx->just_try -= 25;
	if (is_key_just_down(mlx->keyboard, KEY_E))
		interract_block(mlx);
}
