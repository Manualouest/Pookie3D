/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:21:02 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/01 17:21:32 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/* Trucs a implementer pour le bonus :

Define les vitesse du player:
WALK | SPRINT

Le jump et le sprint

*/

// Fonction qui gère les mouvements
void	cd_keys(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	cd_moove_forward(game);
	cd_moove_backward(game);
	cd_moove_left(game);
	cd_moove_right(game);
	cd_camera(game);
}
