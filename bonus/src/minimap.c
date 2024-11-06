/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:45:38 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
// a modifier encore une fois pour que ca fonctionne putain
void	cd_minimap_conditions(t_game *game, t_position *pos, int *i, int *ii)
{
	// char *str;
	// uint32_t purple;
	// str = "(128,0,128)";
	// purple = cd_create_rgba(str);
	if (game->map.map[*i][*ii] == 1)
		mlx_put_pixel(game->screen, pos->x, pos->y, 0x0000FFFF); /// y'a plus .c et .f dans graphic deso :p
	else if (game->map.map[*i][*ii] == 0)//                          stv je ferais un printer de texture pour toi bebou ;3
		mlx_put_pixel(game->screen, pos->x, pos->y, 0xFF0000FF);
	else if (game->map.map[*i][*ii] == 'N'
				|| game->map.map[*i][*ii] == 'W'
				|| game->map.map[*i][*ii] == 'E'
				|| game->map.map[*i][*ii] == 'S')
		mlx_put_pixel(game->screen, pos->x, pos->y, 0xFF0000FF);
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
	while (game->map.map[i])
	{
		ii = 0;
		while (game->map.map[i][ii])
		{
			cd_minimap_conditions(game, &pos, &i, &ii);
			ii++;
		}
		pos.x = 0;
		i++;
	}
}
