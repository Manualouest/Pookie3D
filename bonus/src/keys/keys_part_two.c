/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:20:43 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/02 23:20:54 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_jump(t_game *game)
{
	if (game->keys.space == 1)
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.1;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.1;
	}
}