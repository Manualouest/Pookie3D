/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:57:40 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/18 13:51:01 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_init_player(t_map *map)
{
	t_position	player;

	player.x = 0;
	player.y = 0;
	player.view = 0;
	player.height = 0;
	player.pitch = 0;
	map->player = player;
}

void	cd_init_map(t_game *game)
{
	t_map	map;

	map.map = NULL;
	map.color = NULL;
	map.path = NULL;
	map.fd = 0;
	cd_init_player(&map);
	game->map = map;
}

void	cd_init_rays(t_game *game)
{
	t_ray_info	rays;

	rays.x = 0;
	rays.y = 0;
	rays.t_x = 0;
	rays.angle = 0;
	rays.distance = 0;
	rays.wall_height = 0;
	rays.dx = 0;
	rays.dy = 0;
	rays.delta_dx = 0;
	rays.delta_dy = 0;
	rays.side_dx = 0;
	rays.side_dy = 0;
	rays.side = 0;
	rays.step_x = 0;
	rays.step_y = 0;
	game->rays = rays;
}

void	cd_init_graphic(t_game *game)
{
	t_textures	graphic;

	graphic.no = 0;
	graphic.so = 0;
	graphic.we = 0;
	graphic.ea = 0;
	graphic.f = 0;
	graphic.c = 0;
}

t_game	cd_init_structs(void)
{
	t_game	game;

	game.error = 0;
	cd_init_map(&game);
	cd_init_rays(&game);
	cd_init_graphic(&game);
	return (game);
}