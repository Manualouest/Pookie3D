/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:21:02 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/30 17:27:31 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// Fonction qui gère les mouvements / exit le jeu 
void	cd_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
		// cd_terminate_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		game->map.player.x += cos(game->map.player.view) * 0.3;
		game->map.player.y += sin(game->map.player.view) * 0.3;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		game->map.player.x -= cos(game->map.player.view) * 0.3;
		game->map.player.y -= sin(game->map.player.view) * 0.3;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->map.player.view = cd_clamp(game->map.player.view - 0.03, 0., 2. * M_PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->map.player.view = cd_clamp(game->map.player.view + 0.03, 0., 2. * M_PI);
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
}
