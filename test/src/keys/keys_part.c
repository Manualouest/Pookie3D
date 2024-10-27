/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:08:13 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/24 23:12:33 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_moove_forward(t_game *game)
{
	float	xcheck;
	float	ycheck;
	if (game->keys.w == 1)
	{
		xcheck = game->map.player.x + game->map.player.dirx * 3. * game->mlx->delta_time;
		ycheck = game->map.player.y + game->map.player.diry * 3. * game->mlx->delta_time;
		if (!game->graphic.wmap[(int)ycheck][(int)xcheck])
		{
			game->map.player.x = xcheck;
			game->map.player.y = ycheck;
		}
	}
}
void	cd_moove_backward(t_game *game)
{
	float	xcheck;
	float	ycheck;
	if (game->keys.s == 1)
	{
		xcheck = game->map.player.x - game->map.player.dirx * 3. * game->mlx->delta_time;
		ycheck = game->map.player.y - game->map.player.diry * 3. * game->mlx->delta_time;
		if (!game->graphic.wmap[(int)ycheck][(int)xcheck])
		{
			game->map.player.x = xcheck;
			game->map.player.y = ycheck;
		}
	}
}

void	cd_moove_left(t_game *game)
{
	float	xcheck;
	float	ycheck;
	if (game->keys.a == 1)
	{
		xcheck = game->map.player.x - (game->map.player.planex) * 3. * game->mlx->delta_time;
		ycheck = game->map.player.y - (game->map.player.planey) * 3. * game->mlx->delta_time;
		if (!game->graphic.wmap[(int)ycheck][(int)xcheck])
		{
			game->map.player.x = xcheck;
			game->map.player.y = ycheck;
		}
	}
}

void	cd_moove_right(t_game *game)
{
	float	xcheck;
	float	ycheck;
	if (game->keys.d == 1)
	{
		xcheck = game->map.player.x + (game->map.player.planex) * 3. * game->mlx->delta_time;
		ycheck = game->map.player.y + (game->map.player.planey) * 3. * game->mlx->delta_time;
		if (!game->graphic.wmap[(int)ycheck][(int)xcheck])
		{
			game->map.player.x = xcheck;
			game->map.player.y = ycheck;
		}
	}
}

void	cd_camera(t_game *game)
{
	float	olddirx;
	float	oldplanex;

	if (game->keys.left == 1)
	{
		// game->map.player.view = cd_clamp(game->map.player.view - 1. * game->mlx->delta_time, 0., 2. * M_PI);
		olddirx = game->map.player.dirx;
    	game->map.player.dirx = game->map.player.dirx * cos(1. * game->mlx->delta_time) - game->map.player.diry * sin(1. * game->mlx->delta_time);
    	game->map.player.diry = olddirx * sin(1. * game->mlx->delta_time) + game->map.player.diry * cos(1. * game->mlx->delta_time);
    	oldplanex = game->map.player.planex;
    	game->map.player.planex = game->map.player.planex * cos(1. * game->mlx->delta_time) - game->map.player.planey * sin(1. * game->mlx->delta_time);
    	game->map.player.planey = oldplanex * sin(1. * game->mlx->delta_time) + game->map.player.planey * cos(1. * game->mlx->delta_time);
	}
	if (game->keys.right == 1)
	{
		// game->map.player.view = cd_clamp(game->map.player.view + 1. * game->mlx->delta_time, 0., 2. * M_PI);
		olddirx = game->map.player.dirx;
    	game->map.player.dirx = game->map.player.dirx * cos(-1. * game->mlx->delta_time) - game->map.player.diry * sin(-1. * game->mlx->delta_time);
    	game->map.player.diry = olddirx * sin(-1. * game->mlx->delta_time) + game->map.player.diry * cos(-1. * game->mlx->delta_time);
    	oldplanex = game->map.player.planex;
    	game->map.player.planex = game->map.player.planex * cos(-1. * game->mlx->delta_time) - game->map.player.planey * sin(-1. * game->mlx->delta_time);
    	game->map.player.planey = oldplanex * sin(-1. * game->mlx->delta_time) + game->map.player.planey * cos(-1. * game->mlx->delta_time);
	}
	if (game->keys.up == 1)
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch + 1. * game->mlx->delta_time, -0.75, 0.75);
	if (game->keys.down == 1)
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch - 1. * game->mlx->delta_time, -0.75, 0.75);
}
