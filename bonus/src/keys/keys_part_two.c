/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/03 09:22:23 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		if (game->data.coeff == -1)
			game->data.coeff --;
		if (game->data.coeff > 0 && (int)game->data.coeff % 2)
		{
			game->data.coeff -= 2;
			game->map.player.height += game->data.coeff / 1000.;
		}
		else if (game->data.coeff > -51 && !((int)game->data.coeff % 2))
		{
			game->data.coeff -= 2;
			game->map.player.height += game->data.coeff / 1000.;
		}
		if (game->map.player.height <= game->data.normal_height)
		{
			game->map.player.height = game->data.normal_height;
			game->data.coeff = 41;
			game->keys.space = 0;
		}
	}
}
