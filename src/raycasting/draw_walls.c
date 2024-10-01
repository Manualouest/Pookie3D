/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/01 11:41:24 by mbirou           ###   ########.fr       */
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
	ray->t_x = (ray->t_x - floor(ray->t_x)) * ((float)texture[0][0]);
	return (texture);
}

int	cd_get_color(t_game *game, float y, float y_max, int **texture)
{
	y = y * ((float)texture[0][1]) / y_max;
	return (texture[(int)y + 1][(int)game->rays.t_x]);
}

void	cd_draw_walls(t_game *game, t_ray_info *ray, int x)
{
	int		**texture;
	int		up;
	int		down;
	int		y;
	float	y_ratio;

	texture = cd_get_texture(game, ray);
	up = ((int)game->screen->height - 1) / 2. - ray->wall_height / 2.;
	down = ((int)game->screen->height - 1) / 2. + ray->wall_height / 2.;
	y_ratio = (((float)texture[0][1]) / (float)(down - up));
	y = -1;
	while (++y < up && y < (int)game->screen->height - 1)
		mlx_put_pixel(game->screen, x, y, game->graphic.f);
	y --;
	while (++y < down && y < (int)game->screen->height - 1)
		mlx_put_pixel(game->screen, x, y,
			texture[(int)((y - up + 1) * y_ratio)][(int)ray->t_x]);
	y --;
	while (++y < (int)game->screen->height - 1)
		mlx_put_pixel(game->screen, x, y, game->graphic.c);
}
