/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:53:09 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/04 18:09:12 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_draw_roof_floor(t_game *game, float y, float x, int type)
{
	float	floorx;
	float	floory;
	int		tile;
	int		tx;
	int		ty;

	game->c_f_info.row_dst = (game->graphic.height * (0.5 + game->player.height * type))
		/ (y - game->graphic.up_op);
	floorx = x * game->c_f_info.row_dst * game->c_f_info.stepx;
	floory = x * game->c_f_info.row_dst * game->c_f_info.stepy;
	floorx += type * game->player.x + game->c_f_info.row_dst
				* game->c_f_info.dx0;
	floory += type * game->player.y + game->c_f_info.row_dst
				* game->c_f_info.dy0;
	game->c_f_info.mx = cd_clamp_two(type * floorx, 0, game->map.width - 1);
	game->c_f_info.my = cd_clamp_two(type * floory, 0, game->map.height - 1);
	tile = game->graphic.rmap[(int)game->c_f_info.my][(int)game->c_f_info.mx];
	tx = ((float)game->graphic.txts[tile][0][0] * (floorx - floor(floorx)));
	ty = ((float)game->graphic.txts[tile][0][1] * (floory - floor(floory)));
	mlx_put_pixel(game->screen, x, y, game->graphic.txts[tile][tx + 1][ty]);
	cd_reduce_color(game, x, y, 1. / (sqrt(((game->player.x - game->c_f_info.mx) * (game->player.x - game->c_f_info.mx))
		+ ((game->player.y - game->c_f_info.my) * (game->player.y - game->c_f_info.my))) + 1));
}

/* if (type == -1)
	{
		floorx += type * game->player.x + game->c_f_info.row_dst * game->c_f_info.dx0;
		floory += type * game->player.y + game->c_f_info.row_dst * game->c_f_info.dy0;
		tile = game->graphic.rmap[(int)cd_clamp_two(type * floory, 0, game->map.height - 1)][(int)cd_clamp_two(type * floorx, 0, game->map.width - 1)];
	}
	else
	{
		floorx += game->player.x + game->c_f_info.row_dst * game->c_f_info.dx0;
		floory += game->player.y + game->c_f_info.row_dst * game->c_f_info.dy0;
		tile = game->graphic.fmap[(int)cd_clamp_two(floory, 0, game->map.height - 1)][(int)cd_clamp_two(floorx, 0, game->map.width - 1)];
	} */

void	cd_draw_tiles(t_game *game, int x)
{
	int		y;
	float	o_effect;
	float	o_incr;

	o_effect = game->graphic.dim;
	// o_incr = game->graphic.incr * (game->player.height + 1);
	o_incr = (1. - o_effect) / game->graphic.up;
	y = game->graphic.up;
	while (--y > 0)
	{
		cd_draw_roof_floor(game, y, x, -1);
		// cd_reduce_color(game, x, y, o_effect);
		o_effect += o_incr;
		// o_incr -= 0.000008 * (game->player.height + 1);
	}
	y = game->graphic.down - 1;
	o_effect = game->graphic.dim;
	// o_incr = game->graphic.incr / (game->player.height + 1);
	o_incr = (1. - o_effect) / (960. - game->graphic.down);
	while (++y < game->graphic.height)
	{
		cd_draw_roof_floor(game, y, x, 1);
		// cd_reduce_color(game, x, y, o_effect);
		o_effect += o_incr;
		// o_incr -= 0.000008 / (game->player.height + 1);
	}
}
