/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:52:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/24 17:57:38 by mbirou           ###   ########.fr       */
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
	game->keys = keys;
}
