/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/27 21:56:00 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	
	// int	j = -1;
	// int	jj;
	// while (game.graphic.fmap[++j][0] != -1)
	// {
	// 	jj = -1;
	// 	printf("y: %d||", j);
	// 	while (game.graphic.fmap[j][++jj] != -1)
	// 		printf("%d", game.graphic.fmap[j][jj]);
	// 	printf("||\n");
	// }
	// return (0);	
	// cd_thread_init(&game);

	game.mlx = mlx_init(game.graphic.width, game.graphic.height, "Pookie3d", true);
	
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	game.screen = mlx_new_image(game.mlx, game.graphic.width, game.graphic.height);
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	// mlx_resize_image(game.screen, game.graphic.width, game.graphic.height);
	// game.screen->instances[0].z = 2;
	mlx_key_hook(game.mlx, (void (*))cd_keys, (void *)&game);
	
	mlx_loop_hook(game.mlx, cd_render, (void *)&game);
	mlx_loop(game.mlx);


	// cd_thread_destroy(&game);

	cd_free_all(&game);
	//launch_game(game);
	return (1);
}
