/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:51:40 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/24 21:35:00 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_thread_init(t_game *game)
{
	mlx_texture_t	*txt;

	// game->c_f_info = malloc(sizeof(*game->c_f_info));
	pthread_mutex_init(&game->c_f_info.status_check, NULL);
	txt = mlx_load_png("./pngs/test.png");
	game->c_f_info.floor_t = cd_extract_pixel(txt, 0);
	game->c_f_info.roof_t = cd_extract_pixel(txt, 0);
	mlx_delete_texture(txt);
	game->c_f_info.floor_status = 1;
	game->c_f_info.game_status = 1;
	game->c_f_info.img = NULL;
	// pthread_create(&game->c_f_info.thread, NULL, (void (*))cd_floor_maker,
	// 	&game->c_f_info);
}

void	cd_thread_destroy(t_game *game)
{
	pthread_mutex_lock(&game->c_f_info.status_check);
	game->c_f_info.game_status = 0;
	pthread_mutex_unlock(&game->c_f_info.status_check);
	pthread_join(game->c_f_info.thread, NULL);
	pthread_mutex_destroy(&game->c_f_info.status_check);
	cd_free_int_tab(game->c_f_info.floor_t);
	if (game->c_f_info.img)
		mlx_delete_image(game->mlx, game->c_f_info.img);
}

