/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/15 10:12:33 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		if (game->player.coeff == -1)
			game->player.coeff --;
		if (game->player.coeff > 0 && (int)game->player.coeff % 2)
		{
			game->player.coeff -= 2;
			game->player.height += game->player.coeff / 1000.;
		}
		else if (game->player.coeff > -51 && !((int)game->player.coeff % 2))
		{
			game->player.coeff -= 2;
			game->player.height += game->player.coeff / 1000.;
		}
		if (game->player.height <= NORMAL_HEIGHT)
		{
			game->player.height = NORMAL_HEIGHT;
			game->player.coeff = 41;
			game->keys.space = 0;
		}
	}
}
