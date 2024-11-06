/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:11:33 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

mlx_image_t	*cd_slow_raycast(t_game *game, struct timeval start_time,
				int target_fps, int get_img)
{
	mlx_image_t		*img;
	struct timeval	end_time;
	char			*fps;
	int				start;
	int				end;

	gettimeofday(&end_time, NULL);
	start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	while (1000000 / abs(end - start + 1) > target_fps)
	{
		gettimeofday(&end_time, NULL);
		end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	}
	if (!get_img)
		return (NULL);
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	fps = ft_itoa(1000000 / abs(end - start + 1));
	img = mlx_put_string(game->mlx, fps, 5, -4);
	free(fps);
	return (img);
}

void	cd_modif_res(t_game *game, int moment)
{
	if (game->keys.a || game->keys.d || game->keys.w || game->keys.s
		|| game->keys.up || game->keys.down || game->keys.left
		|| game->keys.right || game->keys.space)
	{
		if (!moment)
		{
			game->graphic.width_mod = 3;
			game->graphic.width = 640;
		}
		else
		{
			game->graphic.width_mod = 1;
			game->graphic.width = 1920;
		}
	}
}
