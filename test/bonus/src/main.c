/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.F r>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.F r       */
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
	game.nb_block = NULL;
	parser(&game);
	
	cd_img_to_int(&game.graphic);

	game.mlx = mlx_init(game.graphic.width, game.graphic.height, "Pookie3d", true);
	
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	game.screen = mlx_new_image(game.mlx, game.graphic.width, game.graphic.height);
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	game.gui = mlx_new_image(game.mlx, game.graphic.width, game.graphic.height);
	mlx_image_to_window(game.mlx, game.gui, 0, 0);
	// mlx_resize_image(game.screen, game.graphic.width, game.graphic.height);
	// game.screen->instances[0].z = 2;
	mlx_key_hook(game.mlx, (void (*))cd_keys, (void *)&game);
	mlx_mouse_hook(game.mlx, (void (*))cd_mouse_input, (void *)&game);
	mlx_loop_hook(game.mlx, (void (*))cd_render, (void *)&game);
	mlx_loop(game.mlx);


	cd_free_all(&game);
	//launch_game(game);
	return (1);
}
