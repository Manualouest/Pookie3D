/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:21:02 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/26 12:42:41 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fonction qui gère les mouvements / exit le jeu 
void	cd_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		cd_terminate_game(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		cd_moove_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		cd_moove_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		cd_moove_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		cd_moove_right(game);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		cd_jump(game);
}
