/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:23:18 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/12 06:13:58 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_init_ray_vars(t_game *game, t_ray_info *ray, float x)
{
	float	cam_x;

	ray->x = (int)game->map.player.x;
	ray->y = (int)game->map.player.y;
	cam_x = 2. * x / ((float)game->graphic.width - 1.);
	ray->dx = game->map.player.dirx + (game->map.player.planex * cam_x - game->map.player.planex);
	ray->dy = game->map.player.diry + (game->map.player.planey * cam_x - game->map.player.planey);
	// mlx_put_pixel(game->screen, (int)(ray->dx * 100 + game->graphic.width / 2.), (int)(ray->dy * 100 + game->graphic.height / 2.), 0xFF0000FF);
	ray->delta_dx = fabs(1. / ray->dx);
	ray->delta_dy = fabs(1. / ray->dy);
	ray->step_x = 1;
	ray->side_dx = (ray->x + 1. - game->map.player.x) * ray->delta_dx;
	if (ray->dx < 0)
	{
		ray->step_x = -1;
		ray->side_dx = (game->map.player.x - ray->x) * ray->delta_dx;
	}
	ray->step_y = 1;
	ray->side_dy = (ray->y + 1. - game->map.player.y) * ray->delta_dy;
	if (ray->dy < 0)
	{
		ray->step_y = -1;
		ray->side_dy = (game->map.player.y - ray->y) * ray->delta_dy;
	}
	ray->side = 0;
}

void	cd_ray_loop(t_game *game, t_ray_info *ray)
{
	while (ray->x > 0 && ray->x < game->map.width
		&& ray->y > 0 && ray->y < game->map.height
		&& game->map.map[(int)ray->y][(int)ray->x] == game->map.map[(int)game->map.player.y][(int)game->map.player.x]
		&& (ray->side_dx - ray->delta_dx) < (float)game->graphic.height / 2.
		&& (ray->side_dy - ray->delta_dy) < (float)game->graphic.height / 2.)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->y += ray->step_y;
			ray->side = 1;
		}
	}
	if (ray->side == 0)
		ray->distance = ray->side_dx - ray->delta_dx;
	else
		ray->distance = ray->side_dy - ray->delta_dy;
}

void	cd_cast_ray(t_game *game, t_ray_info *ray, int x)
{
	cd_init_ray_vars(game, ray, x);
	cd_ray_loop(game, ray);
	ray->wall_height = (float)game->graphic.height / ray->distance;
	if (ray->wall_height < 2)
		ray->wall_height = 0;
}

mlx_image_t	*cd_slow_raycast(t_game *game, struct timeval start_time,
				int target_fps)
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
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec * 1000000 + end_time.tv_usec;
	fps = ft_itoa(1000000 / abs(end - start + 1));
	img = mlx_put_string(game->mlx, fps, 5, -4);
	free(fps);
	return (img);
	mlx_delete_image(game->mlx, img);
}

void	cd_render(void *vgame)
{
	struct timeval	time;
	t_game	*game;
	int		x;

	gettimeofday(&time, NULL);
	game = (t_game *)vgame;
	if (game->fps)
		mlx_delete_image(game->mlx, game->fps);
	x = -1;
	while (++x < ((int)game->graphic.width - 1))
	{
		cd_cast_ray(game, &game->rays, x);
		if (game->rays.wall_height != 0)
			cd_draw_walls(game, &game->rays, x);
		else
			cd_draw_c_f(game, x);
	}
	cd_moove(game);
	game->fps = cd_slow_raycast(game, time, 1000);
}
