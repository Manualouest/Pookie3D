/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:00:37 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/27 21:48:23 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	**cd_get_texture(t_game *game, t_ray_info *ray)
{
	int	**texture;

	texture = game->graphic.txts[game->graphic.tmap[(int)ray->y][(int)ray->x]];
	if (ray->side == 0)
		ray->t_x = game->map.player.y + ray->distance * ray->dy;
	else
		ray->t_x = game->map.player.x + ray->distance * ray->dx;
	ray->t_x = (int)((ray->t_x - floor(ray->t_x)) * ((float)texture[0][0]));
	game->graphic.up = game->graphic.up_op - ((int)ray->wall_height >> 1);
	game->graphic.down = game->graphic.up + ray->wall_height;
	game->graphic.y_ratio = (((float)texture[0][1])
		/ (float)(game->graphic.down - game->graphic.up));
	return (texture);
}

// void	cd_draw_floor(t_game *game)
// {
// 	float	y;
// 	float	x;
// 	float	rayDirX0;
// 	float	rayDirY0;
// 	float	rayDirX1;
// 	float	rayDirY1;
// 	float	rowDistance;
// 	float	floorStepX;
// 	float	floorStepY;
// 	float	floorX;
// 	float	floorY;
// 	int		tx;
// 	int		ty;
// 	int		mid;

// 	mid = (game->graphic.height) / 2. + ((game->graphic.height) / 2.) * game->map.player.pitch;
// 	rayDirX0 = game->map.player.dirx - game->map.player.planex;
// 	rayDirY0 = game->map.player.diry - game->map.player.planey;
// 	rayDirX1 = game->map.player.dirx + game->map.player.planex;
// 	rayDirY1 = game->map.player.diry + game->map.player.planey;
// 	y = -1;
// 	while (++y < game->graphic.height)
// 	{
// 		rowDistance = (game->graphic.height) / 2. / (y - (float)mid + 0.01);
// 		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->graphic.width;
// 		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->graphic.width;
// 		floorX = game->map.player.x + rowDistance * rayDirX0;
//       	floorY = game->map.player.y + rowDistance * rayDirY0;
// 		// printf("rowdist: %f, fstepx: %f, fstepy: %f, floorx: %f, floory: %f\n", rowDistance, floorStepX, floorStepY, floorX, floorY);
// 		x = -1;
// 		while (++x < game->graphic.width)
// 		{
// 			tx = ((float)game->graphic.ea[0][0] * (floorX - floor(floorX)));// / (game->graphic.ea[0][0]);
// 			ty = ((float)game->graphic.ea[0][1] * (floorY - floor(floorY)));// / (game->graphic.ea[0][1]);
// 			floorX += floorStepX;
// 			floorY += floorStepY;
// 			// printf("tx: %d, ty: %d, floorX: %f, floorY: %f\n", tx, ty, floorX, floorY);
// 			mlx_put_pixel(game->screen, x, y, game->graphic.ea[tx + 1][ty]);
// 		}
// 	}
// }

int	cd_darken_color(uint32_t color, float amount)
{
	uint32_t	darkened;
	uint32_t	rgb;

	rgb = color >> 8;
	amount *= 0.1;
	// darkened = ((int)fmax((rgb >> 16) - 0x10 * amount, 0x00) << 16) +
	// 	((int)fmax(((rgb & 0xff00) >> 8) - 0x10 * amount, 0x00) << 8) +
	// 	(int)fmax(((rgb & 0xff) - 0x10 * amount), 0x00);

	darkened = (int)cd_clamp_two((rgb >> 16) - 0x10 * amount, 0, 0xFF) << 16;
	darkened += (int)cd_clamp_two(((rgb & 0xff00) >> 8) - 0x10 * amount, 0, 0xFF) << 8;
	darkened += (int)cd_clamp_two((rgb & 0xff) - 0x10 * amount, 0, 0xFF);
	// printf("1: %X, 2:%X, 3:%X\n", color, darkened, rgb);
	return (darkened << 8 | (color & 0xff));
	// int	r;
	// int	g;
	// int	b;

	// r = ((color >> 24) & 0xFF) & (int)(0xFF * amount);
	// g = ((color >> 16) & 0xFF) & (int)(0xFF * amount);
	// b = ((color >> 8) & 0xFF) & (int)(0xFF * amount);
	// // printf("1: %d, 2: %d\n", color, (r << 24 | g << 16 | b << 8 | (color & 0xFF)));
	// return (r << 24 | g << 16 | b << 8 | (color & 0xFF));
}

int	cd_dim_color(t_game *game, int color)
{
	uint32_t	darkened;
	uint32_t	rgb;

	rgb = color >> 8;
	darkened = (int)((rgb >> 16) * game->graphic.dim) << 16;
	darkened += (int)(((rgb & 0xff00) >> 8) * game->graphic.dim) << 8;
	darkened += (int)((rgb & 0xff) * game->graphic.dim);
	return (darkened << 8 | (color & 0xff));
}

void	cd_draw_roof_floor(t_game *game, float y, float x, int type)
{
	float	floorx;
	float	floory;
	int		tile;
	int		tx;
	int		ty;

	game->c_f_info.row_dst = (game->graphic.height)
		/ ((y - game->c_f_info.mid) * 2.);
	floorx = x * game->c_f_info.row_dst * game->c_f_info.stepx;
	floory = x * game->c_f_info.row_dst * game->c_f_info.stepy;
	if (type == -1)
	{
		floorx += -game->map.player.x + game->c_f_info.row_dst * game->c_f_info.dx0;
		floory += -game->map.player.y + game->c_f_info.row_dst * game->c_f_info.dy0;
		tile = game->graphic.rmap[(int)cd_clamp_two(-floory, 0, game->map.height - 1)][(int)cd_clamp_two(-floorx, 0, game->map.width - 1)];
	}
	else
	{
		floorx += game->map.player.x + game->c_f_info.row_dst * game->c_f_info.dx0;
		floory += game->map.player.y + game->c_f_info.row_dst * game->c_f_info.dy0;
		tile = game->graphic.fmap[(int)cd_clamp_two(floory, 0, game->map.height - 1)][(int)cd_clamp_two(floorx, 0, game->map.width - 1)];
	}
	tx = ((float)game->graphic.txts[tile][0][0] * (floorx - floor(floorx)));
	ty = ((float)game->graphic.txts[tile][0][1] * (floory - floor(floory)));
	mlx_put_pixel(game->screen, x, y, game->graphic.txts[tile][tx + 1][ty]);
}
	// mlx_put_pixel(game->screen, x, y, cd_darken_color(game->graphic.txts[tile][tx + 1][ty], game->c_f_info.mid / fabs(y - game->c_f_info.mid)));
	// uint32_t color = game->graphic.ea[tx + 1][ty];
	// uint32_t color = cd_darken_color(game->graphic.ea[tx + 1][ty], game->c_f_info.mid / fabs(y - game->c_f_info.mid));
	// mlx_put_pixel(game->screen, x, y, game->graphic.ea[tx + 1][ty]);

void	cd_reduce_color(t_game *game, int x, int y, float effect)
{
	int		pos;

	pos = (int)(y * game->graphic.width + x) << 2;
	game->screen->pixels[pos] *= effect;
	game->screen->pixels[pos + 1] *= effect;	
	game->screen->pixels[pos + 2] *= effect;
}

void	cd_start_dim(float *effect_ptr, float *incr_ptr, t_game *game)
{
	float	effect;
	float	incr;
	int		step;
	int		i;
	int		diff;

	effect = 1;
	incr = 0.00001;
	step = -1;
	diff = game->graphic.height - game->rays.wall_height;
	if (diff < 0)
	{
		*effect_ptr = effect;
		*incr_ptr = incr;
		return ;
	}
	diff >>= 1;
	i = -1;
	while (++i != diff)
	{
		effect += incr * step;
		incr -= 0.000008 * step;
	}
	*effect_ptr = effect;
	*incr_ptr = incr;
}

void	cd_draw_tiles(t_game *game, int x)
{
	int		y;
	float	o_effect;
	float	o_incr;

	o_effect = game->graphic.dim;
	o_incr = game->graphic.incr;
	y = game->graphic.up;
	while (--y > 0)
	{
		cd_draw_roof_floor(game, y, x, -1);
		cd_reduce_color(game, x, y, o_effect);
		o_effect += o_incr;
		o_incr -= 0.000008;
	}
	y = game->graphic.down - 1;
	o_effect = game->graphic.dim;
	o_incr = game->graphic.incr;
	while (++y < game->graphic.height)
	{
		cd_draw_roof_floor(game, y, x, 1);
		cd_reduce_color(game, x, y, o_effect);
		o_effect += o_incr;
		o_incr -= 0.000008;
	}
}

void	cd_draw_walls(t_game *game, t_ray_info *ray, int x)
{
	int		**texture;
	int		y;

	texture = cd_get_texture(game, ray);
	y = game->graphic.up - 1;
	if (y < -1)
		y = -1;
	cd_start_dim(&game->graphic.dim, &game->graphic.incr, game);
	while (++y < game->graphic.down && y < game->graphic.height)
	{
		mlx_put_pixel(game->screen, x, y,
			texture[(int)ray->t_x + 1][(int)(
					(float)(y - game->graphic.up) * game->graphic.y_ratio)]);
		cd_reduce_color(game, x, y, game->graphic.dim);
	}
	cd_draw_tiles(game, x);
	// cd_dim_slice(game, x, game->graphic.up, game->graphic.down);
}
	/* while (++y < game->graphic.height)
	{
		if (y < game->graphic.up)
		{
			cd_draw_roof_floor(game, y, x, -1);
			game->graphic.dim -= game->graphic.incr;
			game->graphic.incr += 0.000008;
		}
		else if (y < game->graphic.down)
			mlx_put_pixel(game->screen, x, y, texture[(int)ray->t_x + 1][(int)
				((float)(y - game->graphic.up) * game->graphic.y_ratio)]);
		else if (y > game->graphic.down)
		{
			cd_draw_roof_floor(game, y, x, 1);
			game->graphic.dim += game->graphic.incr;
			game->graphic.incr -= 0.000008;
		}
		cd_reduce_color(game, x, y, game->graphic.dim);
	} */

void	cd_draw_c_f(t_game *game, int x)
{
	int	y;

	y = -1;
	game->graphic.up = game->graphic.up_op - 15;
	game->graphic.down = game->graphic.up + 30;
	game->graphic.dim = 0.028792;
	game->graphic.incr = 0.003946;
	y = game->graphic.up - 1;
	if (y < -1)
		y = -1;
	while (++y < game->graphic.down && y < (int)game->graphic.height)
		mlx_put_pixel(game->screen, x, y, 0x000000FF);
	cd_draw_tiles(game, x);
}
