/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:06:53 by psalame           #+#    #+#             */
/*   Updated: 2024/04/10 16:50:18 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "./parsing_Int.h"

static t_map_error_type	parse_map_char(t_map *map, char c, t_ivec2 pos, int screen_res[2])
{
	if (ft_isspace(c))
		map->blocks[pos.y][pos.x].type = EMPTY;
	else if (c == '0')
		map->blocks[pos.y][pos.x].type = FLOOR;
	else if (c >= '1' && c <= '9')
	{
		map->blocks[pos.y][pos.x].type = WALL;
		map->blocks[pos.y][pos.x].data.wall = c - '0';
	}
	else if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
	{
		map->blocks[pos.y][pos.x].type = FLOOR;
		if (map->playerPos.x != -1.0f)
			return (MAP_DUPLICATE_PLAYER_POS);
		map->playerPos.x = pos.x;
		map->playerPos.y = pos.y;
		map->playerPos.z = 0.0f;
		if (c == 'N')
		{
			map->camDir.y = -1;
			map->camPlane.x = (float)screen_res[0] / (float)screen_res[1] - 1;
		}
		else if (c == 'S')
		{
			map->camDir.y = 1;
			map->camPlane.x = -((float)screen_res[0] / (float)screen_res[1] - 1);
		}
		else if (c == 'E')
		{
			map->camDir.x = 1;
			map->camPlane.y = (float)screen_res[0] / (float)screen_res[1] - 1;
		}
		else
		{
			map->camDir.x = -1;
			map->camPlane.y = -((float)screen_res[0] / (float)screen_res[1] - 1);
		}
	}
	else if (c == 'D')
		map->blocks[pos.y][pos.x].type = DOOR;
	return (MAP_NO_ERROR);
}

t_map_error_type	set_map_blocks(t_map *map, t_list *lines, int screen_res[2])
{
	size_t				y;
	size_t				x;
	char				*line;
	t_map_error_type	res;

	y = 0;
	res = MAP_NO_ERROR;
	while (map->blocks[y])
	{
		x = 0;
		line = lines->content;
		while (line[x] && map->blocks[y][x].type != END)
		{
			res = parse_map_char(map, line[x], (t_ivec2) {x, y}, screen_res);
			if (res != MAP_NO_ERROR)
				return (res);
			x++;
		}
		y++;
		lines = lines->next;
	}
	return (res);
}
