/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/15 19:38:13 by mbirou           ###   ########.fr       */
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

void	cd_draw_floor(t_game *game)
{
	float	y;
	float	x;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		tx;
	int		ty;
	int		mid;

	mid = ((float)game->graphic.height - 1.) / 2. + (((float)game->graphic.height - 1.) / 2.) * game->map.player.pitch;
	rayDirX0 = game->map.player.dirx - game->map.player.planex;
	rayDirY0 = game->map.player.diry - game->map.player.planey;
	rayDirX1 = game->map.player.dirx + game->map.player.planex;
	rayDirY1 = game->map.player.diry + game->map.player.planey;
	y = -1;
	while (++y < game->graphic.height)
	{
		rowDistance = ((float)game->graphic.height - 1.) / 2. / (y - (float)mid + 0.01);
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->graphic.width;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->graphic.width;
		floorX = game->map.player.x + rowDistance * rayDirX0;
      	floorY = game->map.player.y + rowDistance * rayDirY0;
		// printf("rowdist: %f, fstepx: %f, fstepy: %f, floorx: %f, floory: %f\n", rowDistance, floorStepX, floorStepY, floorX, floorY);
		x = -1;
		while (++x < game->graphic.width)
		{
			tx = ((float)game->graphic.ea[0][0] * (floorX - floor(floorX)));// / (game->graphic.ea[0][0] - 1);
			ty = ((float)game->graphic.ea[0][1] * (floorY - floor(floorY)));// / (game->graphic.ea[0][1] - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			// printf("tx: %d, ty: %d, floorX: %f, floorY: %f\n", tx, ty, floorX, floorY);
			mlx_put_pixel(game->screen, x, y, game->graphic.ea[tx + 1][ty]);
		}
	}
}

// void	cd_draw_roof_floor(t_game *game, int y, int x, int type)
// {
// 	float	row_dist;
// 	float	floorx;
// 	float	floory;
// 	int		tx;
// 	int		ty;

// 	if (!type)
// 		return ;
// 	row_dist = ((float)game->graphic.height - 1.) / 2.
// 		/ (y - (float)game->c_f_info.mid + 0.01);
// 	floorx = game->map.player.x + row_dist * game->c_f_info.dirx0;
// 	floory = game->map.player.y + row_dist * game->c_f_info.diry0;
// 	tx = ((float)game->graphic.ea[0][0] * (floorx - floor(floorx)));
// 	ty = ((float)game->graphic.ea[0][1] * (floory - floor(floory)));
// 	mlx_put_pixel(game->screen, x, y, game->graphic.ea[tx + 1][ty]);
// }

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
	game->c_f_info.mid = ((float)game->graphic.height - 1.) / 2.
		+ (((float)game->graphic.height - 1.) / 2.) * game->map.player.pitch;
	while (++y < up && y < down)
		mlx_put_pixel(game->screen, x, y, game->graphic.c);
		// cd_draw_roof_floor(game, y, x, 1);
	y --;
	while (++y < down && y < (int)game->graphic.height - 1)
		mlx_put_pixel(game->screen, x, y,
			texture[(int)ray->t_x + 1][(int)((float)(y - up) * y_ratio)]);
	y --;
	// while (++y < (int)game->graphic.height - 1)
	// 	mlx_put_pixel(game->screen, x, y, game->graphic.f);
	if (x == 0)
		cd_draw_floor(game);
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
