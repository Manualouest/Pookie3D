/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:23:18 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/27 22:04:22 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_init_ray_vars(t_game *game, t_ray_info *ray, float x)
{
	float	cam_x;

	ray->x = (int)game->map.player.x;
	ray->y = (int)game->map.player.y;
	cam_x = 2. * x / (game->graphic.width);
	ray->dx = game->map.player.dirx + (game->map.player.planex * cam_x - game->map.player.planex) + 0.0000001;
	ray->dy = game->map.player.diry + (game->map.player.planey * cam_x - game->map.player.planey) + 0.0000001;
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
	while (ray->x >= 0 && ray->x < game->map.width
		&& ray->y >= 0 && ray->y < game->map.height
		&& game->graphic.wmap[(int)ray->y][(int)ray->x] == 0
		&& ((ray->side == 0 && ray->side_dx - ray->delta_dx < 33) //(game->graphic.height) * 0.5
		|| (ray->side == 1 && ray->side_dy - ray->delta_dy < 33)))	 //(game->graphic.height) * 0.5))
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
	ray->wall_height = game->graphic.height / ray->distance;
	if (ray->wall_height < 30)
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
void	cd_launch_floor(t_game *game)
{
	game->c_f_info.dx0 = game->map.player.dirx - game->map.player.planex;
	game->c_f_info.dy0 = game->map.player.diry - game->map.player.planey;
	game->c_f_info.dx1 = game->map.player.dirx + game->map.player.planex;
	game->c_f_info.dy1 = game->map.player.diry + game->map.player.planey;
	game->c_f_info.stepx = (game->c_f_info.dx1 - game->c_f_info.dx0)
		/ game->graphic.width;
	game->c_f_info.stepy = (game->c_f_info.dy1 - game->c_f_info.dy0)
		/ game->graphic.width;
	// game->c_f_info.pos_x = game->map.player.x;
	// game->c_f_info.pos_y = game->map.player.y;
	// game->c_f_info.height = game->graphic.height;
	// game->c_f_info.width = game->graphic.width;
	game->c_f_info.mid = (int)(game->graphic.height
		+ game->graphic.height * game->map.player.pitch) >> 1;
	// if (game->c_f_info.img)
	// 	mlx_delete_image(game->mlx, game->c_f_info.img);
	// game->c_f_info.img = mlx_new_image(game->mlx, game->graphic.width,
	// 	game->graphic.height);
	// pthread_mutex_lock(&game->c_f_info.status_check);
	// game->c_f_info.floor_status = 0;
	// pthread_mutex_unlock(&game->c_f_info.status_check);
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
	cd_launch_floor(game);
	game->graphic.up_op = (game->graphic.height 
		+ game->graphic.height * game->map.player.pitch) * 0.5;
	x = -1;
	mlx_resize_image(game->screen, game->graphic.width, game->graphic.height);
	while (++x < ((int)game->graphic.width))
	{
		cd_cast_ray(game, &game->rays, x);
		if (game->rays.wall_height > 0)
			cd_draw_walls(game, &game->rays, x);
		else
			cd_draw_c_f(game, x);
	}
	mlx_resize_image(game->screen, game->graphic.width * game->graphic.width_mod, game->graphic.height);
	cd_moove(game);
	game->fps = cd_slow_raycast(game, time, 10000);
}
