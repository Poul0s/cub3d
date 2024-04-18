/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:36:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 13:17:50 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

char	*open_solo_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Solo");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *)ptr;
	mlx->actuel_menu = GAME;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2, mlx->stg->height / 2);
	return (NULL);
}

char	*open_multiplayer_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Multiplayer");
	if (action == 2)
		return ((char *) 1);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = MULTIPLAYER_MENU;
	return (NULL);
}

char	*open_settings_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Settings");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = OPTIONS;
	return (NULL);
}

char	*open_main_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Back");
	if (action == 2)
		return ((char *) 2);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = MAIN_MENU;
	return (NULL);
}

char	*set_ip_address_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.ip[0] == 0)
			return ("IP");
		else
			return (mlx->game_server.ip);
	}
	if (action == 2)
		return ((char *) 3);
	return (NULL);
}

char	*set_port_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.port_str[0] == 0)
			return ("PORT");
		else
			return (mlx->game_server.port_str);
	}
	if (action == 2)
		return ((char *) 4);
	return (NULL);
}

char	*set_pseudo_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.player_name[0] == 0)
			return ("PSEUDO");
		else
			return (mlx->game_server.player_name);
	}
	if (action == 2)
		return ((char *) 5);
	return (NULL);
}

char	*connect_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Connect");
	if (action == 2)
		return ((char *) 6);
	mlx = ptr;
	connect_to_server(&(mlx->game_server));
	if (mlx->game_server.status != CONNECTED)
		print_network_err(mlx->game_server.status);
	else
	{
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2,  mlx->stg->height / 2);
		mlx->actuel_menu = GAME;
		mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2, mlx->stg->height / 2);
		dprintf(mlx->game_server.sockfd, "initPlayer:%s,%.2f,%.2f,%.2f,%.2f,%.2f;",
			mlx->game_server.player_name, mlx->map->player_pos.x, mlx->map->player_pos.y,
			mlx->map->player_pos.z, mlx->map->cam_dir.x, mlx->map->cam_dir.y);
	}
	return (NULL);
}

char	*exit_button(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Exit");
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	window(0, mlx);
	return (NULL);
}