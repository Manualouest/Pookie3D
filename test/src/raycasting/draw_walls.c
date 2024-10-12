/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/12 06:11:15 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	**cd_get_texture(t_game *game, t_ray_info *ray)
{
	int	**texture;

	if (ray->side == 0 && ray->dx > 0)
		texture = game->graphic.ea;
	else if (ray->side == 0 && ray->dx <= 0)
		texture = game->graphic.we;
	else if (ray->side == 1 && ray->dy > 0)
		texture = game->graphic.so;
	else
		texture = game->graphic.no;
	if (ray->side == 0)
		ray->t_x = game->map.player.y + ray->distance * ray->dy;
	else
		ray->t_x = game->map.player.x + ray->distance * ray->dx;
	ray->t_x = (int)((ray->t_x - floor(ray->t_x)) * ((float)texture[0][0]));
	return (texture);
}

void	cd_draw_floor(t_game *game, t_ray_info *ray, int x, int down)
{
	float	dist;
	float	weight;
	float	floorx;
	float	floory;
	int		ftextx;
	int		ftexty;
	int		y;

	y = down;
	while (++y < game->graphic.height)
	{
		dist = y - down;
		weight = dist / ray->wall_height;
		floorx = weight * floor(ray->x) + (1. - weight) * (float)game->map.player.x;
		floory = weight * floor(ray->y) + (1. - weight) * (float)game->map.player.y;
		ftextx = (int)(floorx * game->graphic.ea[0][0]) % game->graphic.ea[0][0];
		ftexty = (int)(floory * game->graphic.ea[0][1]) % game->graphic.ea[0][1];
		mlx_put_pixel(game->screen, x, y, game->graphic.ea[ftextx + 1][ftexty]);
	}
}



void	cd_draw_walls(t_game *game, t_ray_info *ray, int x)
{
	int		**texture;
	int		up;
	int		down;
	int		y;
	float	y_ratio;

	texture = cd_get_texture(game, ray);
	up = ((float)game->graphic.height - 1.) / 2. - ray->wall_height / 2.
		+ (((float)game->graphic.height - 1.) / 2.) * game->map.player.pitch;
	down = up + ray->wall_height;
	y_ratio = (((float)texture[0][1]) / (float)(down - up));
	y = -1;
	while (++y < up && y < down)
		mlx_put_pixel(game->screen, x, y, game->graphic.c);
	y --;
	while (++y < down && y < (int)game->graphic.height - 1)
		mlx_put_pixel(game->screen, x, y,
			texture[(int)ray->t_x + 1][(int)((float)(y - up) * y_ratio)]);
	y --;
	while (++y < (int)game->graphic.height - 1)
		mlx_put_pixel(game->screen, x, y, game->graphic.f);
	// cd_draw_floor(game, ray, x, down);
	// test(game);
}

void	cd_draw_c_f(t_game *game, int x)
{
	int	y;
	int	mid;

	y = -1;
	mid = (game->graphic.height ) / 2.
		+ (((float)game->graphic.height - 1.) / 2.) * game->map.player.pitch;
	while (++y < mid)
		mlx_put_pixel(game->screen, x, y, game->graphic.c);
	y --;
	while (++y < game->graphic.height)
		mlx_put_pixel(game->screen, x, y, game->graphic.f);
}
