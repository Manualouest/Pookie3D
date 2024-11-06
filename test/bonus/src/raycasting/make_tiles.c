/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:53:09 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 19:59:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float	cd_get_p_rsqrt(t_game *game, float x2, float y2)
{
	__m128	num_sq;
	float	num;

	num = 0;
	num_sq = _mm_loadu_ps(&(float){((game->player.x - x2)
					* (game->player.x - x2))
				+ ((game->player.y - y2)
					* (game->player.y - y2))});
	_mm_storeu_ps(&num, _mm_rsqrt_ss(num_sq));
	return (num);
}

void	cd_draw_roof_floor(t_game *game, float y, float x, int type)
{
	float	floorx;
	float	floory;
	int		tile;
	int		tx;
	int		ty;

	game->t_info.row_dst = (game->graphic.height
			* (0.5 + game->player.height * type)) / (y - game->graphic.up_op);
	floorx = x * game->t_info.row_dst * game->t_info.stepx;
	floory = x * game->t_info.row_dst * game->t_info.stepy;
	floorx += type * game->player.x + game->t_info.row_dst
		* game->t_info.dx0;
	floory += type * game->player.y + game->t_info.row_dst
		* game->t_info.dy0;
	game->t_info.mx = cd_clamp_two(type * floorx, 0, game->map.width - 1);
	game->t_info.my = cd_clamp_two(type * floory, 0, game->map.height - 1);
	tile = game->graphic.fmap[(int)game->t_info.my][(int)game->t_info.mx];
	if (type == -1)
		tile = game->graphic.rmap[(int)game->t_info.my][(int)game->t_info.mx];
	tx = ((float)game->graphic.txts[tile][0][0] * (floorx - floor(floorx)));
	ty = ((float)game->graphic.txts[tile][0][1] * (floory - floor(floory)));
	mlx_put_pixel(game->screen, x, y, game->graphic.txts[tile][tx + 1][ty]);
	game->graphic.dim = cd_get_p_rsqrt(game, game->t_info.mx, game->t_info.my);
	cd_dim_color(game, x, y, game->graphic.dim);
}

// ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))


	// cd_dim_color(game, x, y, 1. / (sqrt(((game->player.x - game->t_info.mx) 
	// 	* (game->player.x - game->t_info.mx)) + ((game->player.y 
	// 	- game->t_info.my) * (game->player.y - game->t_info.my))) + 1));

	// _mm_storeu_ps(&game->graphic.dim, _mm_rsqrt_ss(_mm_loadu_ps(&(float){((game->player.x - game->t_info.mx) * (game->player.x - game->t_info.mx))
	// 	+ ((game->player.y - game->t_info.my) * (game->player.y - game->t_info.my))})));
	// cd_dim_color(game, x, y, game->graphic.dim);

void	cd_draw_tiles(t_game *game, int x)
{
	int		y;
	float	o_effect;
	float	o_incr;

	o_effect = game->graphic.dim;
	o_incr = (1. - o_effect) / game->graphic.up;
	y = game->graphic.up;
	while (--y > 0)
	{
		cd_draw_roof_floor(game, y, x, -1);
		o_effect += o_incr;
	}
	y = game->graphic.down - 1;
	o_effect = game->graphic.dim;
	o_incr = (1. - o_effect) / (960. - game->graphic.down);
	while (++y < game->graphic.height)
	{
		cd_draw_roof_floor(game, y, x, 1);
		o_effect += o_incr;
	}
}
