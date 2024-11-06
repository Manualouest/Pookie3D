/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:22:16 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 20:44:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	cd_get_smaller_index(t_game *game, int i, float o_min)
{
	float	cur_min;
	int		i_save;

	cur_min = o_min;
	while (game->graphic.sprites[++i])
	{
		if (game->graphic.sprites[i]->distance < cur_min)
		{
			cur_min = game->graphic.sprites[i]->distance;
			i_save = i;
		}
	}
}

void	cd_sort_sprites(t_game *game)
{
	int			i;
	int			ii;
	float		cur_min;
	t_sprite	*swp;

	if (!game->graphic.sprites || !game->graphic.sprites[0])
		return ;
	i = -1;
	while (game->graphic.sprites[++i])
	{
		cur_min = game->graphic.sprites[i]->distance;
		ii = i;
		while (game->graphic.sprites[++ii])
		{
			if (game->graphic.sprites[ii]->distance < cur_min)
				cur_min = game->graphic.sprites[ii]->distance;
		}
		if (game->graphic.sprites[i]->distance != cur_min)
		{
			swp = game->graphic.sprites[i];
			game->graphic.sprites[i] = game->graphic.sprites[i]
		}
	}
}

void	cd_render_sprites(t_game *game, float x)
{

}