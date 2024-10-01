/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:08:13 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/01 17:33:44 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_moove_forward(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->map.player.x += cos(game->map.player.view) * 0.3;
		game->map.player.y += sin(game->map.player.view) * 0.3;
	}
}
void	cd_moove_backward(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->map.player.x -= cos(game->map.player.view) * 0.3;
		game->map.player.y -= sin(game->map.player.view) * 0.3;
	}
}

void	cd_moove_left(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->map.player.x -= cos(game->map.player.view + 0.5 * M_PI) * 0.3;
		game->map.player.y -= sin(game->map.player.view + 0.5 * M_PI) * 0.3;
	}
}

void	cd_moove_right(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.3;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.3;
	}
}

void	cd_camera(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->map.player.view = cd_clamp(game->map.player.view - 0.03, 0., 2. * M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->map.player.view = cd_clamp(game->map.player.view + 0.03, 0., 2. * M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch + 0.05, -0.5, 0.5);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch - 0.05, -0.5, 0.5);
}
