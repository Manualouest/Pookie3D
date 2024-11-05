/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/05 10:49:55 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		if (game->player.coeff == -1 || game->player.height >= 0.4)
			game->player.coeff --;
		if (game->player.coeff > 0 && (int)game->player.coeff % 2)
		{
			game->player.coeff -= 2;
			game->player.height += game->player.coeff
				* game->mlx->delta_time / 25.;
		}
		else if (game->player.coeff > -51 && !((int)game->player.coeff % 2))
		{
			game->player.coeff -= 2;
			game->player.height += game->player.coeff
				* game->mlx->delta_time / 25.;
		}
		if (game->player.height <= NORMAL_HEIGHT)
		{
			game->player.height = NORMAL_HEIGHT;
			game->player.coeff = 41;
			game->keys.space = 0;
			game->graphic.width_mod = 1;
			game->graphic.width = 1920;
		}
	}
}
