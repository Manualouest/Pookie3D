/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/03 07:21:40 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		if (game->map.player.height < game->data.jump_height
			&& game->map.player.height >= game->data.normal_height)
		{
			game->data.coeff = game->data.coeff * 0.8;
			game->map.player.height 
				= cd_clamp_two(pow((game->map.player.height), 2) * game->data.coeff + 0.1,
				0.2, 0.4);
		}
		if (game->map.player.height > game->data.normal_height
			&& game->map.player.height <= game->data.jump_height)
		{
			game->data.coeff = game->data.coeff * 0.8;
			game->map.player.height 
				= cd_clamp_two(pow((game->map.player.height), 2) * game->data.coeff + 0.1,
				0.2, 0.4);
			if (game->map.player.height <= game->data.normal_height)
			{
				game->map.player.height = game->data.normal_height;
				game->keys.space = 0;
			}
		}
	}
}
