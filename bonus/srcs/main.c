/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/16 14:32:12 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*argument_map(void *ptr, int action);


static int	verif_start_video(void)
{
	char	str[37];
	int	i;

	i = 0;
	ft_strncpy(str, "textures/main_menu/video/1/000.png\0", 36);
	while (i < 102)
	{
		str[27] = i / 100 + '0';
		str[28] = i / 10 % 10 + '0';
		str[29] = i % 10 + '0';
		if (access(str, R_OK) == -1 || access(str, F_OK) == -1)
			return (ft_putstr_fd("Error: Video file\n", 2));
		i++;
	}
	return (0);
}

static int	verif_file(t_map *map, char *file)
{
	int			i;
	const char	*lst[13] = {
		map->texture.north,
		map->texture.south,
		map->texture.east,
		map->texture.west,
		"textures/game/fire.png",
		"textures/game/player_back.png",
		"textures/game/player_front.png",
		"textures/game/player_left.png",
		"textures/game/player_right.png",
		"textures/inventory/fist.png",
		"textures/inventory/knife.png",
		"textures/inventory/weapon.png",
		"textures/main_menu/bg_main_menu.png",
	};

	i = -1;
	while (++i < 13)
	{
		if (access(lst[i], R_OK) == -1 || access(lst[i], F_OK) == -1)
			return (ft_putstr_fd("Error: Texture file not found\n", 2));
	}
	return (verif_start_video());
}

int	main(int ac, char **av)
{
	t_settings	*settings;
	t_map		*map;

	(void)ac;
	settings = parse_config_file(".config");
	if (!settings)
		return (1);
	map = parse_map(av[1], (int [2]){settings->width, settings->height});
	if (!map)
	{
		free(settings);
		return (1);
	}
	if (verif_file(map, av[1]))
	{
		free_map(map);
		free(settings);
		return (1);
	}
	argument_map(av[1], -1);
	graphics_part(map, settings);
}
