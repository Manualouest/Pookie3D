/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:50:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/03 00:49:01 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	player_speed_controller(t_game *game)
{
	if (game->keys.shift == 1)
		game->data.player_speed = game->data.crouch;
	if (game->keys.ctrl == 1)
		game->data.player_speed = game->data.run;
	if (game->keys.shift == 0 && game->data.player_speed != game->data.walk
		&& game->keys.ctrl == 0)
		game->data.player_speed = game->data.walk;
}
void	player_height_controller(t_game *game)
{
	if (game->keys.shift == 1)
		game->map.player.height = game->data.crouch_height;
	if (game->keys.shift == 0 && game->map.player.height != game->data.normal_height)
		game->map.player.height = game->data.normal_height;
}
