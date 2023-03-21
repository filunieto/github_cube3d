/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyHook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramire <anramire@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:18:24 by anramire          #+#    #+#             */
/*   Updated: 2023/03/21 20:05:47 by anramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game/Game.h"


void	key_advance_and_back_aux(void *param)
{
	t_game *game = (t_game*)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		player_advance(game->map, game->player, 1);
		paint(game);

	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		player_advance(game->map, game->player, -1);
		paint(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		rotate(game->player, -1);
		paint(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		rotate(game->player, 1);
		paint(game);
	}
}
