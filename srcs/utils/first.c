/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:09:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/14 17:27:28 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*error_ptr(char *str, void *ret)
{
	printf("Cube3d: %s\n", str);
	return (ret);
}

int	error_int(char *str, int ret)
{
	printf("Cube3d: %s\n", str);
	return (ret);
}

long long	get_now_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
