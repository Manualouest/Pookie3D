/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:57:40 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_init_player(t_game *game)
{
	t_data_player	player;

	player.x = -1;
	player.y = -1;
	player.view = -1;
	player.height = 0;
	player.pitch = 0;
	player.speed = WALKING_SPEED;
	player.jump_coeff = 41;
	player.jog_coeff = 52;
	player.planex = 0.;
	player.planey = 0.66;
	game->player = player;
}

void	cd_init_map(t_game *game, char *map_file)
{
	t_map	map;

	map.map = malloc(sizeof(int *));
	map.map[0] = malloc(sizeof(int));
	map.map[0][0] = -1;
	map.map = NULL;
	map.path = map_file;
	map.fd = 0;
	map.height = 0;
	map.width = 0;
	map.fov = M_PI / 3.;
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
	i = -1;
	while (++i < 94)
	{
		graphic.paths[i] = NULL;
		graphic.slots[i] = 0;
	}
	graphic.dim = 0;
	graphic.incr = 0;
	game->graphic = graphic;
}

t_game	cd_init_structs(char *map_file)
{
	t_game	game;

	cd_init_map(&game, map_file);
	cd_init_player(&game);
	cd_init_rays(&game);
	cd_init_graphic(&game);
	cd_init_keys(&game);
	return (game);
}
