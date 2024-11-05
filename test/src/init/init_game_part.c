/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:52:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/31 17:17:34 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	keys.fps = 1;
	game->keys = keys;
}
