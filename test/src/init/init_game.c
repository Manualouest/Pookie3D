/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:57:40 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/27 21:55:24 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_init_player(t_map *map)
{
	t_position	player;

	player.x = -1;
	player.y = -1;
	player.view = -1;
	player.height = 0.5;
	player.pitch = 0;
	player.planex = 0.;
	player.planey = 0.66;
	map->player = player;
}

void	cd_init_map(t_game *game, char *map_file)
{
	t_map	map;

	map.map = NULL;
	map.path = map_file;
	map.fd = 0;
	map.height = 0;
	map.width = 0;
	map.fov = M_PI / 3.;
	cd_init_player(&map);
	game->map = map;
}

void	cd_init_rays(t_game *game)
{
	t_ray_info	rays;

	rays.x = 0;
	rays.y = 0;
	rays.t_x = 0;
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
	int			i;

	graphic.wmap = malloc(sizeof(int *));
	graphic.wmap[0] = malloc(sizeof(int));
	graphic.wmap[0][0] = -1;
	graphic.tmap = malloc(sizeof(int *));
	graphic.tmap[0] = malloc(sizeof(int));
	graphic.tmap[0][0] = -1;
	graphic.fmap = malloc(sizeof(int *));
	graphic.fmap[0] = malloc(sizeof(int));
	graphic.fmap[0][0] = -1;
	graphic.rmap = malloc(sizeof(int *));
	graphic.rmap[0] = malloc(sizeof(int));
	graphic.rmap[0][0] = -1;
	graphic.width = 1920;
	graphic.width_mod = 1;
	graphic.height = 1016;
	i = 0;
	while (++i < 95)
		graphic.slots[i] = 0;
	graphic.dim = 0;
	graphic.incr = 0;
	game->graphic = graphic;
}

t_game	cd_init_structs(char *map_file)
{
	t_game	game;

	cd_init_map(&game, map_file);
	cd_init_rays(&game);
	cd_init_graphic(&game);
	cd_init_keys(&game);
	return (game);
}
