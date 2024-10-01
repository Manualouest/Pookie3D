/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:21:02 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/01 16:12:31 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// Fonction qui gère les mouvements / exit le jeu 
void	cd_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
		// cd_terminate_game(game);
	cd_moove_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->map.player.x -= cos(game->map.player.view) * 0.3;
		game->map.player.y -= sin(game->map.player.view) * 0.3;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->map.player.x -= cos(game->map.player.view + 0.5 * M_PI) * 0.3;
		game->map.player.y -= sin(game->map.player.view + 0.5 * M_PI) * 0.3;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->map.player.x += cos(game->map.player.view + 0.5 * M_PI) * 0.3;
		game->map.player.y += sin(game->map.player.view + 0.5 * M_PI) * 0.3;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->map.player.view = cd_clamp(game->map.player.view - 0.03, 0., 2. * M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->map.player.view = cd_clamp(game->map.player.view + 0.03, 0., 2. * M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch + 0.05, -0.5, 0.5);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->map.player.pitch = cd_clamp_two(game->map.player.pitch - 0.05, -0.5, 0.5);
}

	// if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	// 	cd_moove_forward(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	// 	cd_moove_backward(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	// 	cd_moove_left(game);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	// 	cd_moove_right(game);
	// if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	// 	cd_jump(game);

void	cd_moove_forward(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->map.player.x += cos(game->map.player.view) * 0.3;
		game->map.player.y += sin(game->map.player.view) * 0.3;
	}
}