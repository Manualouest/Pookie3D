/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:50:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/03 16:13:09 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	player_speed_controller(t_game *game)
{
	if (game->keys.shift == 1)
		game->player.speed = CROUCH_SPEED;
	if (game->keys.ctrl == 1)
		game->player.speed = RUNNING_SPEED;
	if (game->keys.shift == 0 && game->player.speed != WALKING_SPEED
		&& game->keys.ctrl == 0)
		game->player.speed = WALKING_SPEED;
}
void	player_height_controller(t_game *game)
{
	if (game->keys.shift == 1 && !game->keys.space)
		game->player.height = CROUCH_HEIGHT;
	if (game->keys.shift == 0 && game->player.height != NORMAL_HEIGHT
		&& !game->keys.space)
		game->player.height = NORMAL_HEIGHT;
}

// void    mouse_controller(t_game *game)
// {
//     int    x;
//     int    y;
//     int    screen_center_x = SCREEN_W / 2;  // Le centre de l'écran en X
//     int    screen_center_y = SCREEN_H / 2;  // Le centre de l'écran en Y

//     // Récupérer la position actuelle de la souris
//     mlx_get_mouse_pos(data->mlx, data->win, &x, &y);

//     // Calcul de la différence entre la position actuelle de la souris et le centre de l'écran
//     int delta_x = x - screen_center_x;
//     int delta_y = y - screen_center_y;

//     // Mettre à jour l'angle du joueur en fonction de delta_x
//     data->player->angle += delta_x * ROTATE_SPEED;

//     // Vous pouvez aussi faire un traitement pour delta_y si vous avez un axe de pitch (haut-bas)

//     // Recentrer la souris au milieu de l'écran
//     mlx_set_mouse_pos(data->mlx, data->win, screen_center_x, screen_center_y);
// }
