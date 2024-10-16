/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:45:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/16 16:16:54 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

//a modifier pour faire la minimap
void	cd_minimap_conditions(t_game *game, t_position pos, int *i, int *j)
{
	if (game->full[*i][*j] == '1')
		ft_put_texture(game, "./texture/WOODA.png", pos.x, pos.y);
	else if (game->full[*i][*j] == '0')
		ft_put_texture(game, "./texture/Grass.png", pos.x, pos.y);
	else if (game->full[*i][*j] == 'C')
	{
		ft_put_texture(game, "./texture/Grass.png", pos.x, pos.y);
		ft_put_texture(game, "./texture/Coins.png", pos.x, pos.y);
	}
	else if (game->full[*i][*j] == 'P')
		ft_put_texture(game, "./texture/Grass.png",
			game->map.player.x, game->map.player.y);
	else if (game->full[*i][*j] == 'E')
		ft_put_texture(game, "./texture/exit.png", pos.x, pos.y);
}

//Fonction qui va faire la mini map
void	cd_minimap(t_game *game)
{
	int			i;
	int			ii;
	t_position	pos;

	pos.x = 0;
	pos.y = 0;
	i = 0;
	while (game->map.map[i] != 0)
	{
		ii = 0;
		while (game->map.map[i][ii] != 0)
		{
			cd_map_conditions(game, pos, &i, &ii);
			pos.x += 64;
			j++;
		}
		pos.x = 0;
		pos.y += 64;
		i++;
	}
}
