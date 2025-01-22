/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:28:06 by mbirou            #+#    #+#             */
/*   Updated: 2025/01/22 10:51:19 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	*resize_map_line(int *old_line, int new_len, t_game *game, int iswmap)
{
	int	*new_line;
	int	i;

	new_line = calloc(sizeof(*new_line), new_len + 2);
	new_line[new_len + 1] = -1;
	i = -1;
	while (old_line[++i] != -1)
		new_line[i] = old_line[i];
	i --;
	while (++i < new_len + 1)
		new_line[i] = cd_put_first_slot(game, iswmap)
			- (33 + 15 * (iswmap == 1));
	free(old_line);
	return (new_line);
}

void	resize_maps(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.height)
	{
		game->map.map[i] = resize_map_line(game->map.map[i],
				game->map.width, game, 1);
		game->graphic.tmap[i] = resize_map_line(game->graphic.tmap[i],
				game->map.width, game, 0);
		game->graphic.fmap[i] = resize_map_line(game->graphic.fmap[i],
				game->map.width, game, 0);
		game->graphic.rmap[i] = resize_map_line(game->graphic.rmap[i],
				game->map.width, game, 0);
	}
}

int	check_map_borders(t_game *game)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (game->map.map[i][++ii + 1] != -1)
		if (game->map.map[i][ii] == 0)
			return (0);
	while (++i + 1 != game->map.height)
		if (game->map.map[i][0] == 0 || game->map.map[i][game->map.width] == 0)
			return (0);
	while (game->map.map[i][++ii + 1] != -1)
		if (game->map.map[i][ii] == 0)
			return (0);
	return (1);
}
