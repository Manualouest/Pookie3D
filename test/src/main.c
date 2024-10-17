/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/17 19:53:31 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game		game;
	char		*map_file;

	if (argc == 1)
		map_file = cd_map_maker();
	else
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
	

	// mlx_texture_t	*txt = mlx_load_png("./pngs/test.png");
	// game.c_f_info.floor_t = cd_extract_pixel(txt, 0);
	// mlx_delete_texture(txt);

	// pthread_mutex_init(&game.c_f_info.status_check, NULL);
	// game.c_f_info.floor_status = 1;
	// game.c_f_info.game_status = 1;
	// game.c_f_info.floor = NULL;
	// pthread_create(&game.c_f_info.floor_maker, NULL, (void (*))cd_floor_maker,
	// 	&game.c_f_info);

	game.mlx = mlx_init(game.graphic.width, game.graphic.height, "Pookie3d", true);
	
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	game.screen = mlx_new_image(game.mlx, game.graphic.width, game.graphic.height);
	mlx_image_to_window(game.mlx, game.screen, 0, 0);
	game.screen->instances[0].z = 2;
	mlx_key_hook(game.mlx, (void (*))cd_keys, (void *)&game);
	
	mlx_loop_hook(game.mlx, cd_render, (void *)&game);
	mlx_loop(game.mlx);

	// pthread_mutex_lock(&game.c_f_info.status_check);
	// (&game.c_f_info)->game_status = 0;
	// pthread_mutex_unlock(&game.c_f_info.status_check);
	// pthread_join(game.c_f_info.floor_maker, NULL);

	cd_free_all(&game);
	//launch_game(game);
	return (1);
}
