/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:52:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/01 19:12:01 by malbrech         ###   ########.fr       */
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