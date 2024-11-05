/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/04 17:41:16 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	**cd_get_texture(t_game *game, t_ray_info *ray)
{
	int	**texture;

	texture = game->graphic.txts[game->graphic.tmap[(int)ray->y][(int)ray->x]];
	if (ray->side == 0)
		ray->t_x = game->player.y + ray->distance * ray->dy;
	else
		ray->t_x = game->player.x + ray->distance * ray->dx;
	ray->t_x = (int)((ray->t_x - floor(ray->t_x)) * ((float)texture[0][0]));
	game->graphic.up = game->graphic.up_op - ((int)ray->wall_height >> 1)
			+ ray->wall_height * game->player.height;
	game->graphic.down = game->graphic.up + ray->wall_height;
	game->graphic.y_ratio = (((float)texture[0][1])
		/ (float)(game->graphic.down - game->graphic.up));
	return (texture);
}

void	cd_reduce_color(t_game *game, int x, int y, float effect)
{
	int	pos;

	pos = (int)(y * game->graphic.width + x) << 2;
	game->screen->pixels[pos] *= effect;
	game->screen->pixels[pos + 1] *= effect;	
	game->screen->pixels[pos + 2] *= effect;
}

float	cd_start_dim(t_game *game)
{
	float	effect;

	effect = 1. / (sqrt(pow(game->player.x - game->rays.x, 2)
			+ pow(game->player.y - game->rays.y, 2)) + 1.);
	return (effect);
}

void	cd_draw_walls(t_game *game, t_ray_info *ray, int x)
{
	int	**texture;
	int	y;

	texture = cd_get_texture(game, ray);
	y = game->graphic.up - 1;
	if (y < -1)
		y = -1;
	game->graphic.dim = cd_start_dim(game);
	while (++y < game->graphic.down && y < game->graphic.height)
	{
		mlx_put_pixel(game->screen, x, y,
			texture[(int)ray->t_x + 1][(int)(
					(float)(y - game->graphic.up) * game->graphic.y_ratio)]);
		cd_reduce_color(game, x, y, game->graphic.dim);
	}
	cd_draw_tiles(game, x);
}

void	cd_draw_c_f(t_game *game, int x)
{
	int	y;

	y = -1;
	game->graphic.up = game->graphic.up_op - 15
		+ 30 * game->player.height;
	game->graphic.down = game->graphic.up + 30;
	game->graphic.dim = 0.028792;
	game->graphic.incr = 0.003946;// / (game->player.height + 1);
	y = game->graphic.up - 1;
	if (y < -1)
		y = -1;
	while (++y < game->graphic.down && y < (int)game->graphic.height)
		mlx_put_pixel(game->screen, x, y, 0x000000FF);
	cd_draw_tiles(game, x);
}
