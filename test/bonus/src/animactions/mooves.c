/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:34:26 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/09 18:53:38 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void cd_jump(t_game *game)
{
    if (game->keys.space == 1)
    {
        if (game->player.height >= 0.4)
            game->player.jump_coeff = -1;
        if (game->player.jump_coeff == -1 || game->player.height >= 0.4)
            game->player.jump_coeff--;
        game->player.jump_coeff -= 2;
        if (game->player.jump_coeff > 0 && (int)game->player.jump_coeff % 2)
            game->player.height += game->player.jump_coeff
                * game->mlx->delta_time / 40.;
        else if (game->player.jump_coeff > -51 && !((int)game->player.jump_coeff % 2))
            game->player.height += game->player.jump_coeff
                * game->mlx->delta_time / 40.;
        if (game->player.height <= NORMAL_HEIGHT)
        {
            game->player.height = NORMAL_HEIGHT;
            game->player.jump_coeff = 41;
            cd_modif_res(game, 1, 0);
            game->keys.space = 0;
        }
    }
}

void	cd_walk(t_game *game)
{
	if (game->keys.w == 1
		&& !game->keys.shift
		&& !game->keys.space)
	{
		if (game->player.jog_coeff == -1)
			game->player.jog_coeff --;
		if (game->player.jog_coeff > 0 && (int)game->player.jog_coeff % 2)
		{
			game->player.jog_coeff -= 2;
			game->player.height += game->player.jog_coeff / 1000.;
		}
		else if (game->player.jog_coeff > -51 && !((int)game->player.jog_coeff % 2))
		{
			game->player.jog_coeff -= 2;
			game->player.height += game->player.jog_coeff / 1000.;
		}
		if (game->player.height <= NORMAL_HEIGHT)
		{
			game->player.height = NORMAL_HEIGHT;
			game->player.jog_coeff = 2;
		}
	}
}