/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:28:13 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/08 18:01:08 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_put_block(t_game *game, int **txt)
{
	int	x;
	int	y;
	int	txtx;
	int	txty;

	y = -1;
	while (++y < 120)
	{
		x = -1;
		while (++x < 120)
		{
			if ((y <= 10 || y >= 110) && (y <= 10 || y >= 110))
			{
				mlx_put_pixel(game->gui, x + 896, y + 1790, 0x808080FF);
				continue;
			}
			txtx = (x - 20) * (txt[0][0] / 100);
			txty = (y - 20) * (txt[0][1] / 100);
			mlx_put_pixel(game->gui, x + 896, y + 1790, txt[txtx + 1][txty]);
		}
	}
}

void	cd_show_block_inventory(t_game *game)
{
	int			i;
	// char		*nb_blocks;
	t_inventory	*tp_inv;

	mlx_resize_image(game->gui, 1, 1);
	mlx_put_pixel(game->gui, 0, 0, 0);
	mlx_resize_image(game->gui, game->graphic.width, game->graphic.height);
	if (game->nb_block)
		mlx_delete_image(game->mlx, game->nb_block);
	i = 0;
	tp_inv = game->player.inventory;
	while (tp_inv)
	{
		tp_inv = tp_inv->next;
		i ++;
	}
	// nb_blocks = ft_itoa(i);
	// mlx_put_string(game->mlx, nb_blocks, 1790, 896);
	// free(nb_blocks);
	// if (i > 0)
	// 	printf("tile : %d\n", game->player.inventory->tile);
	// if (i > 0)
	// 	cd_put_block(game, game->graphic.txts[game->player.inventory->tile]);
}
