/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:08:13 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/12 06:10:44 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_moove_forward(t_game *game)
{
	if (game->keys.w == 1)
	{
		game->map.player.x += game->map.player.dirx * 0.1;
		game->map.player.y += game->map.player.diry * 0.1;
	}
}
void	cd_moove_backward(t_game *game)
{
	if (game->keys.s == 1)
	{
		game->map.player.x -= game->map.player.dirx * 0.1;
		game->map.player.y -= game->map.player.diry * 0.1;
	}
}

void	cd_moove_left(t_game *game)
{
	if (game->keys.a == 1)
	{
		game->map.player.x -= (game->map.player.planex) * 0.1;
		game->map.player.y -= (game->map.player.planey) * 0.1;
	}
}

void	cd_moove_right(t_game *game)
{
	if (game->keys.d == 1)
	{
		game->map.player.x += (game->map.player.planex) * 0.1;
		game->map.player.y += (game->map.player.planey) * 0.1;
	}
}

void	cd_camera(t_game *game)
{
	float	olddirx;
	float	oldplanex;

	if (game->keys.left == 1)
	{
		// game->map.player.view = cd_clamp(game->map.player.view - 0.03, 0., 2. * M_PI);
		olddirx = game->map.player.dirx;
    	game->map.player.dirx = game->map.player.dirx * cos(0.03) - game->map.player.diry * sin(0.03);
    	game->map.player.diry = olddirx * sin(0.03) + game->map.player.diry * cos(0.03);
    	oldplanex = game->map.player.planex;
    	game->map.player.planex = game->map.player.planex * cos(0.03) - game->map.player.planey * sin(0.03);
    	game->map.player.planey = oldplanex * sin(0.03) + game->map.player.planey * cos(0.03);
	}
	if (game->keys.right == 1)
	{
		// game->map.player.view = cd_clamp(game->map.player.view + 0.03, 0., 2. * M_PI);
		olddirx = game->map.player.dirx;
    	game->map.player.dirx = game->map.player.dirx * cos(-0.03) - game->map.player.diry * sin(-0.03);
    	game->map.player.diry = olddirx * sin(-0.03) + game->map.player.diry * cos(-0.03);
    	oldplanex = game->map.player.planex;
    	game->map.player.planex = game->map.player.planex * cos(-0.03) - game->map.player.planey * sin(-0.03);
    	game->map.player.planey = oldplanex * sin(-0.03) + game->map.player.planey * cos(-0.03);
	}
	if (game->keys.up == 1)
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch + 0.03, -0.75, 0.75);
	if (game->keys.down == 1)
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch - 0.03, -0.75, 0.75);
}
