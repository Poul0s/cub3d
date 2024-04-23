/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_kit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:14:44 by psalame           #+#    #+#             */
/*   Updated: 2024/04/19 13:10:56 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game_connexion.h"

void	add_health_kit(t_server *srv, char *value, void *mlx)
{
	t_list			*node;
	t_health_kit	*kit;

	(void)mlx;
	node = malloc(sizeof(t_list) + sizeof(t_health_kit));
	if (!node)
		return ;
	kit = (void *)node + sizeof(t_list);
	node->content = kit;
	node->next = srv->kits;
	srv->kits = node;
	kit->id = ft_atoi(value);
	while (*value && *value++ != ',')
		;
	kit->pos = parse_vec3(&value);
}

static inline int	cmp_kit_id(void *kit, void *id)
{
	return (((t_health_kit *)kit)->id != (intptr_t) id);
}

void	remove_health_kit(t_server *srv, char *value, void *mlx)
{
	int	id;

	(void)mlx;
	id = ft_atoi(value);
	ft_lstremoveif(&srv->kits, (void *)(intptr_t) id, NULL, &cmp_kit_id);
}