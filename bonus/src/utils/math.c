/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:46:20 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/02 22:57:02 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float	cd_clamp(float num, float min, float max)
{
	while (num < min)
		num += max;
	while (num > max)
		num -= max;
	return (num);
}

float	cd_clamp_two(float num, float min, float max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

void	player_speed_controller(t_game *game)
{
	if (game->keys.shift == 1)
		game->speed.player_speed = game->speed.crouch;
	if (game->keys.ctrl == 1)
		game->speed.player_speed = game->speed.run;
	if (game->keys.shift == 0 && game->speed.player_speed != game->speed.walk)
		game->speed.player_speed = game->speed.walk;
}
