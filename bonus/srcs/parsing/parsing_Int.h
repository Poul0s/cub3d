/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_Int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 23:02:37 by psalame           #+#    #+#             */
/*   Updated: 2024/03/13 16:44:17 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define WHITESPACE_CHARS " \a\b\t\v\f\n\r"

// todo add -fshort-enums in makefile

typedef enum e_map_line_type {
	LTYPE_DATA,
	LTYPE_EMPTY,
	LTYPE_MAP
}	t_map_line_type;


typedef struct s_vec2 {
	size_t	x;
	size_t	y;
}	t_vec2;

typedef enum e_map_error_type {
	MAP_NO_ERROR,
	MAP_ERROR_ALLOC,
	MAP_INVALID_IDENTIFIER,
	MAP_INVALID_COLOR,
	MAP_DUPLICATE_PARAMETER,
	MAP_INVALID_CHARACTER,
	MAP_DUPLICATE_PLAYER_POS,
	MAP_CAN_EXIT
}	t_map_error_type;

bool				parse_lines(int fd, t_map *map_data);
t_map_error_type	add_map_line(char *line, t_list **map_lines);
t_map_error_type	check_map_param(char *line, t_map *map_data, t_list **map_lines);
t_map_error_type	check_map_lines(t_map *map, t_list *lines);
t_map_error_type	set_map_blocks(t_map *map, t_list *lines);

#endif