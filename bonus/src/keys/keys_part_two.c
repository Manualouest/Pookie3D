/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/02 21:42:11 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_sneak(t_game *game)
{
	if (game->keys.shift == 1)
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.1;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.1;
	}
}

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.1;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.1;
	}
}

void	cd_sprint(t_game *game)
{
	if (game->keys.ctrl == 1)
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.1;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.1;
	}
}