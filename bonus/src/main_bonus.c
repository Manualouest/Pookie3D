/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:34:12 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/26 17:14:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_init_mlx(t_game *game)
{
	game->mlx = mlx_init(game->graphic.width,
			game->graphic.height, "Pookie3d", true);
	if (!game->mlx)
		error_handler("MLX failed", game, NULL);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->screen = mlx_new_image(game->mlx, game->graphic.width,
			game->graphic.height);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	game->gui = mlx_new_image(game->mlx, game->graphic.width,
			game->graphic.height);
	mlx_image_to_window(game->mlx, game->gui, 0, 0);
	mlx_key_hook(game->mlx, (void (*))cd_keys, (void *)game);
	mlx_mouse_hook(game->mlx, (void (*))cd_mouse_input, (void *)game);
	mlx_scroll_hook(game->mlx, (void (*))cd_inventory_switch, (void *)game);
	mlx_loop_hook(game->mlx, (void (*))cd_render, (void *)game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_file;

	if (argc != 2)
	{
		ft_putstr_fd(PARAM_ERROR, 2);
		return (0);
	}
	map_file = ft_strdup(argv[1]);
	if (!map_file)
		return (0);
	game = cd_init_structs(map_file);
	parser(&game);
	if (game.map.fd != -1)
		close(game.map.fd);
	cd_img_to_int(&game, &game.graphic);
	game.graphic.pic_frame = 0;
	game.player.o_x = game.player.x;
	game.player.o_y = game.player.y;
	cd_init_mlx(&game);
	mlx_loop(game.mlx);
	cd_free_all(&game);
	return (1);
}
