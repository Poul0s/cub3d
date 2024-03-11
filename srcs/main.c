/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:57:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/11 23:14:06 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_block map[4][5] = {
		{ WALL , WALL , WALL , WALL , END },
		{ WALL , FLOOR, FLOOR, WALL , END },
		{ WALL , WALL , FLOOR , WALL , END },
		{ EMPTY, WALL , WALL , WALL , END },
		NULL
	};
	(void)ac;
	(void)av;
	(void)map;
	ft_printf("Hello world !");
}