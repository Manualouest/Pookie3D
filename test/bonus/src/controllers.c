/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.F r>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:50:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.F r       */
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

void    mouse_controller(t_game *game)
{
	int	x;
	int	y;
	int	screen_center_x;
	int	screen_center_y;

	screen_center_x = game->graphic.height / 2;
	screen_center_y = game->graphic.width / 2;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	int delta_x = x - screen_center_x;
	int delta_y = y - screen_center_y;
	game->player.view += delta_x * ROTATE_SPEED;
	game->player.pitch = cd_clamp_two(game->player.pitch - delta_y * ROTATE_SPEED, -0.75, 0.85);
	mlx_set_mouse_pos(game->mlx, screen_center_x, screen_center_y);
}
