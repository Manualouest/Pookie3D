/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.F r>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:46 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.F r       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_mouse_input(mouse_key_t button, action_t action,
	modifier_key_t mods, t_game *game)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& !game->keys.place)
		game->keys.destroy = 1;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS
		&& !game->keys.destroy)
		game->keys.place = 1;
}

void	cd_edit_wall(t_game *game, float x, float y)
{
	float	distance;
	t_inventory	*tp_inv;

	distance = game->rays.distance_save;
	if (game->keys.destroy && (int)x != 0 && (int)x != game->map.width - 1
		&& (int)y != 0 && (int)y != game->map.height - 1 && distance < 5)
	{
		cd_add_sprite(game, x, y);
		game->map.map[(int)y][(int)x] = 0;
	}
	if (game->keys.place && distance < 5 && game->player.inventory
		&& !((int)x == (int)game->player.x && (int)y == (int)game->player.y))
	{
		game->graphic.tmap[(int)y][(int)x] = game->player.inventory->tile;
		tp_inv = game->player.inventory;
		game->player.inventory = tp_inv->next;
		free(tp_inv);
		game->map.map[(int)y][(int)x] = 1;
	}
	game->keys.place = 0;
	game->keys.destroy = 0;
}
