/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:50:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/03 17:03:01 by malbrech         ###   ########.fr       */
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
// Il reste le vertical a gerer attention fonction incomplete
void    mouse_controller(t_game *game)
{
	int	x;
	int	y;
	int	screen_center_x = SCREEN_W / 2;
	int	screen_center_y = SCREEN_H / 2;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	int delta_x = x - screen_center_x;
	int delta_y = y - screen_center_y;
	game->player.view += delta_x * ROTATE_SPEED;
	mlx_set_mouse_pos(game->mlx, screen_center_x, screen_center_y);
}
