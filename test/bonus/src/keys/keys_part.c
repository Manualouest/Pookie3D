/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.F r>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:08:13 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/07 09:48:07 by mbirou           ###   ########.F r       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_moove_forward(t_game *game)
{
	float	testx;
	float	testy;
	if (game->keys.w != 0)
	{
		testx = game->player.x + game->player.dirx
			* game->player.speed * game->mlx->delta_time;
		testy = game->player.y + game->player.diry
			* game->player.speed * game->mlx->delta_time;
		if (game->map.map[(int)testy][(int)game->player.x])
		{
			if (game->map.map[(int)game->player.y][(int)testx])
				return ;
			game->player.x = testx;
			return ;
		}
		game->player.y = testy;
		if (game->map.map[(int)game->player.y][(int)testx])
			return ;
		game->player.x = testx;
	}
}
void	cd_moove_backward(t_game *game)
{
	float	testx;
	float	testy;
	if (game->keys.s != 0)
	{
		testx = game->player.x - game->player.dirx
			* game->player.speed * game->mlx->delta_time;
		testy = game->player.y - game->player.diry
			* game->player.speed * game->mlx->delta_time;
		if (game->map.map[(int)testy][(int)game->player.x])
		{
			if (game->map.map[(int)game->player.y][(int)testx])
				return ;
			game->player.x = testx;
			return ;
		}
		game->player.y = testy;
		if (game->map.map[(int)game->player.y][(int)testx])
			return ;
		game->player.x = testx;
	}
}

void	cd_moove_left(t_game *game)
{
	float	testx;
	float	testy;
	if (game->keys.a == 1)
	{
		testx = game->player.x - game->player.planex
			* game->player.speed * game->mlx->delta_time;
		testy = game->player.y - game->player.planey
			* game->player.speed * game->mlx->delta_time;
		if (game->map.map[(int)testy][(int)game->player.x])
		{
			if (game->map.map[(int)game->player.y][(int)testx])
				return ;
			game->player.x = testx;
			return ;
		}
		game->player.y = testy;
		if (game->map.map[(int)game->player.y][(int)testx])
			return ;
		game->player.x = testx;
	}
}

void	cd_moove_right(t_game *game)
{
	float	testx;
	float	testy;
	if (game->keys.d == 1)
	{
		testx = game->player.x + game->player.planex
			* game->player.speed * game->mlx->delta_time;
		testy = game->player.y + game->player.planey
			* game->player.speed * game->mlx->delta_time;
		if (game->map.map[(int)testy][(int)game->player.x])
		{
			if (game->map.map[(int)game->player.y][(int)testx])
				return ;
			game->player.x = testx;
			return ;
		}
		game->player.y = testy;
		if (game->map.map[(int)game->player.y][(int)testx])
			return ;
		game->player.x = testx;
	}
}

void	cd_camera(t_game *game)
{
	float	olddirx;
	float	oldplanex;

	if (game->keys.left == 1)
	{
		// game->player.view = cd_clamp(game->player.view - 1.F * game->mlx->delta_time, 0., 2.F * M_PI);
		olddirx = game->player.dirx;
    	game->player.dirx = game->player.dirx * cos(1.F * game->mlx->delta_time) - game->player.diry * sin(1.F * game->mlx->delta_time);
    	game->player.diry = olddirx * sin(1.F * game->mlx->delta_time) + game->player.diry * cos(1.F * game->mlx->delta_time);
    	oldplanex = game->player.planex;
    	game->player.planex = game->player.planex * cos(1.F * game->mlx->delta_time) - game->player.planey * sin(1.F * game->mlx->delta_time);
    	game->player.planey = oldplanex * sin(1.F * game->mlx->delta_time) + game->player.planey * cos(1.F * game->mlx->delta_time);
	}
	if (game->keys.right == 1)
	{
		// game->player.view = cd_clamp(game->player.view + 1.F * game->mlx->delta_time, 0., 2.F * M_PI);
		olddirx = game->player.dirx;
    	game->player.dirx = game->player.dirx * cos(-1.F * game->mlx->delta_time) - game->player.diry * sin(-1.F * game->mlx->delta_time);
    	game->player.diry = olddirx * sin(-1.F * game->mlx->delta_time) + game->player.diry * cos(-1.F * game->mlx->delta_time);
    	oldplanex = game->player.planex;
    	game->player.planex = game->player.planex * cos(-1.F * game->mlx->delta_time) - game->player.planey * sin(-1.F * game->mlx->delta_time);
    	game->player.planey = oldplanex * sin(-1.F * game->mlx->delta_time) + game->player.planey * cos(-1.F * game->mlx->delta_time);
	}
	if (game->keys.up == 1)
		game->player.pitch = cd_clamp_two(game->player.pitch + 1.F * game->mlx->delta_time, -0.75, 0.75);
	if (game->keys.down == 1)
		game->player.pitch = cd_clamp_two(game->player.pitch - 1.F * game->mlx->delta_time, -0.75, 0.75);
}
