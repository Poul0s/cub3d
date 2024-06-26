/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:11:43 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:17 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"
#include "../../../graphics/graphics.h"
#define SHOOT_DIST_DECR 1500
#define CUT_DIST_DECR 5000

static void	play_sound_dist(char *sound_path, int decr)
{
	char		*sound_volume;
	char		*cmd;

	if (decr > USHRT_MAX)
		return ;
	sound_volume = ft_itoa(USHRT_MAX - decr);
	cmd = ft_strjoin("paplay --volume=", sound_volume);
	free(sound_volume);
	if (cmd)
		cmd = ft_strfjoin(cmd, " ");
	if (cmd)
		cmd = ft_strfjoin(cmd, sound_path);
	if (cmd)
		cmd = ft_strfjoin(cmd, " &");
	if (cmd)
		system(cmd);
	free(cmd);
}

static void	take_damage(t_mlx *mlx, int damage, int from_player)
{
	t_online_player	*ply;

	mlx->player->health -= damage;
	if (mlx->player->health < 0)
		mlx->player->health = 0;
	ft_dprintf(mlx->game_server.sockfd, "setHealth:%d;", mlx->player->health);
	system("paplay --volume=20000 ./sounds/game/take_damage.wav &");
	if (mlx->player->health == 0)
	{
		ply = get_player_from_source(mlx->game_server.online_player,
				from_player);
		if (ply)
			ft_dprintf(mlx->game_server.sockfd,
				"sendMessage: killed by %s;", ply->player_name);
		else
			ft_dprintf(mlx->game_server.sockfd,
				"sendMessage: killed by (%d);", from_player);
		ft_dprintf(mlx->game_server.sockfd, "addHealthKit:;");
	}
}

void	act_shoot(t_server *srv, char *value, void *mlxRaw)
{
	int			from_player;
	int			got_touch;
	t_vec3		origin;
	float		dist;
	t_mlx		*mlx;

	(void)srv;
	mlx = mlxRaw;
	from_player = ft_atoi(value);
	while (*value++ != ',')
		;
	got_touch = ft_atoi(value);
	while (*value++ != ',')
		;
	origin = parse_vec3(&value);
	dist = get_distance_between_2dcoords(origin, mlx->map->player_pos);
	play_sound_dist("./sounds/game/weapon_fire.wav", dist * SHOOT_DIST_DECR);
	if (got_touch && mlx->player->health > 0)
		take_damage(mlx, 33, from_player);
}

void	act_cut(t_server *srv, char *value, void *mlxRaw)
{
	int			from_player;
	int			got_touch;
	t_vec3		origin;
	float		dist;
	t_mlx		*mlx;

	(void)srv;
	mlx = mlxRaw;
	from_player = ft_atoi(value);
	while (*value++ != ',')
		;
	got_touch = ft_atoi(value);
	while (*value++ != ',')
		;
	origin = parse_vec3(&value);
	dist = get_distance_between_2dcoords(origin, mlx->map->player_pos);
	play_sound_dist("./sounds/game/cut_hit.wav", dist * CUT_DIST_DECR);
	if (got_touch && mlx->player->health > 0)
		take_damage(mlx, mlx->player->health, from_player);
}
