/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:30:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 20:11:57 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../graphics.h"

void	keyboard_status(int key_code[2], bool *key, bool from, bool to)
{
	if (key_code[0] == key_code[1] && from == true && to == false)
		*key = false;
	else if (key_code[0] == key_code[1] && from == false && to == true)
		*key = true;
}

int	keyboard_down(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	keyboard_status((int [2]){key, 26}, &mlx->keyboard->w, false, true);
	keyboard_status((int [2]){key, 4}, &mlx->keyboard->a, false, true);
	keyboard_status((int [2]){key, 22}, &mlx->keyboard->s, false, true);
	keyboard_status((int [2]){key, 7}, &mlx->keyboard->d, false, true);
	keyboard_status((int [2]){key, 21}, &mlx->keyboard->r, false, true);
	keyboard_status((int [2]){key, 82}, &mlx->keyboard->up, false, true);
	keyboard_status((int [2]){key, 81}, &mlx->keyboard->down, false, true);
	keyboard_status((int [2]){key, 80}, &mlx->keyboard->left, false, true);
	keyboard_status((int [2]){key, 79}, &mlx->keyboard->right, false, true);
	keyboard_status((int [2]){key, 41}, &mlx->keyboard->esc, false, true);
	return (0);
}

int	keyboard_up(int key, void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	keyboard_status((int [2]){key, 26}, &mlx->keyboard->w, true, false);
	keyboard_status((int [2]){key, 4}, &mlx->keyboard->a, true, false);
	keyboard_status((int [2]){key, 22}, &mlx->keyboard->s, true, false);
	keyboard_status((int [2]){key, 7}, &mlx->keyboard->d, true, false);
	keyboard_status((int [2]){key, 21}, &mlx->keyboard->r, true, false);
	keyboard_status((int [2]){key, 82}, &mlx->keyboard->up, true, false);
	keyboard_status((int [2]){key, 81}, &mlx->keyboard->down, true, false);
	keyboard_status((int [2]){key, 80}, &mlx->keyboard->left, true, false);
	keyboard_status((int [2]){key, 79}, &mlx->keyboard->right, true, false);
	keyboard_status((int [2]){key, 41}, &mlx->keyboard->esc, true, false);
	return (0);
}

int	keyboard(t_mlx *mlx)
{
	if (mlx->keyboard->esc)
		window(0, (void *)mlx);
	if (mlx->actuel_menu == GAME)
		game_keyboard(mlx);
	return (0);
}
