/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:52:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/03 00:50:06 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_init_keys(t_game *game)
{
	t_keys keys;

	keys.w = 0;
	keys.s = 0;
	keys.a = 0;
	keys.d = 0;
	keys.up = 0;
	keys.down = 0;
	keys.left = 0;
	keys.right = 0;
	keys.space = 0;
	keys.shift = 0;
	keys.ctrl = 0;
	game->keys = keys;
}

void	cd_init_data_infos(t_game *game)
{
	t_data_infos	data;

	data.run = 0.15;
	data.crouch = 0.03;
	data.walk = 0.1;
	data.player_speed = 0.1;
	data.crouch_height = -0.1;
	data.normal_height = 0.2;
	data.jump_height = 0.3;
	game->data = data;
}
