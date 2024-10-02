/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/02 21:44:31 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	main(int argc, char **argv)
{
	t_game		game;
	char		*map_file;

	// if (argc == 1)
	// 	map_file = cd_map_maker();
	// else
		map_file = ft_strdup(argv[1]);
	if (!map_file)
		return (0);
	// printf("%s", map_file);
	if (argc > 2)
		return (0);
	game = cd_init_structs(map_file);
	game.screen = NULL;
	game.fps = NULL;
	parser(&game);
	
	cd_img_to_int(&game.graphic);

	// printf("paths:\n");
	// int	i = -1;
	// while (game.graphic.paths[++i])
	// 	printf("%s\n", game.graphic.paths[i]);
	
	// printf("map:\n");
	// i = -1;
	// while (game.map.map[++i])
	// 	printf("%s\n", game.map.map[i]);


	// game.mlx = mlx_init(1240, 720, "Pookie3d", false);
	game.mlx = mlx_init(1920, 1016, "Pookie3d", false);
	
	game.screen = mlx_new_image(game.mlx, 1920, 1016);
	mlx_image_to_window(game.mlx, game.screen, 0, 0);

	mlx_key_hook(game.mlx, (void (*))cd_keys, (void *)&game);
	
	mlx_loop_hook(game.mlx, cd_render, (void *)&game);
	mlx_loop(game.mlx);

	cd_free_all(&game);
	//launch_game(game);
	return (1);
}
