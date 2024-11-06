/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:51:40 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_thread_init(t_game *game)
{
	mlx_texture_t	*txt;

	// game->t_info = malloc(sizeof(*game->t_info));
	pthread_mutex_init(&game->t_info.status_check, NULL);
	txt = mlx_load_png("./pngs/test.png");
	game->t_info.floor_t = cd_extract_pixel(txt, 0);
	game->t_info.roof_t = cd_extract_pixel(txt, 0);
	mlx_delete_texture(txt);
	game->t_info.floor_status = 1;
	game->t_info.game_status = 1;
	game->t_info.img = NULL;
	// pthread_create(&game->t_info.thread, NULL, (void (*))cd_floor_maker,
	// 	&game->t_info);
}

void	cd_thread_destroy(t_game *game)
{
	pthread_mutex_lock(&game->t_info.status_check);
	game->t_info.game_status = 0;
	pthread_mutex_unlock(&game->t_info.status_check);
	pthread_join(game->t_info.thread, NULL);
	pthread_mutex_destroy(&game->t_info.status_check);
	cd_free_int_tab(game->t_info.floor_t);
	if (game->t_info.img)
		mlx_delete_image(game->mlx, game->t_info.img);
}

