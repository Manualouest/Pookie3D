/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:00:54 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/25 00:13:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_set_orientation(t_game *game, char o, int i)
{
	if (o == 'N')
	{
		game->map.player.dirx = 0;
		game->map.player.diry = 1;
	}
	else if (o == 'S')
	{
		game->map.player.dirx = 0;
		game->map.player.diry = -1;
	}
	else if (o == 'W')
	{
		game->map.player.dirx = -1;
		game->map.player.diry = 0;
	}
	else
	{
		game->map.player.dirx = 1;
		game->map.player.diry = 0;
	}
	game->map.player.planex = 0.9549296585499998935 * game->map.player.diry;
	game->map.player.planey = 0.9549296585499998935 * game->map.player.dirx;
	game->map.player.x = i + 0.5;
	game->map.player.y = game->map.height + 0.5;
}

char	cd_put_first_slot(t_game *game, int is_wmap)
{
	int	i;

	if (is_wmap == 1)
		return ('1');
	i = -1;
	while (++i < 95)
	{
		if (game->graphic.slots[i])
			return ((char)(i + 32));
	}
	return (' ');
}

int	cd_is_floor(t_game *game, char *line, int i, int map_kind)
{
	if (map_kind != 3)
		return (0);
	// printf("line[i]: %c, i: %d, wmap line: %d\n", line[i], i, game->graphic.wmap[game->graphic.tp_h][i]);
	if (line[i] == '0' && !game->graphic.wmap[game->graphic.tp_h][i])
		return (1);
	return (0);
}

int	cd_parse_line(char **line, t_game *game, int map_kind)
{
	int	i;

	i = -1;
	while (line[0][++i] && line[0][i] != '\n')
	{
		if (line[0][i] == ' ')
			line[0][i] = cd_put_first_slot(game, map_kind);
		if (!game->graphic.slots[(int)line[0][i] - 32])
		{
			if (map_kind != 1 && !cd_is_floor(game, line[0], i, map_kind))
				return (-1);
			else if ((line[0][i] == 'N' || line[0][i] == 'S'
				|| line[0][i] == 'E' || line[0][i] == 'W')
				&& game->map.player.x == -1)
			{
				cd_set_orientation(game, line[0][i], i);
				line[0][i] = '0';
			}
		}
	}
	if (line[0][i] && line[0][i] == '\n')
		line[0][i] = 0;
	return (i);
}

void	cd_setup_map(char *line, t_game *game, int ***map)
{
	int	line_len;

	line_len = cd_parse_line(&line, game, 1);
	if (line_len == -1)
		error_handler(BAD_CHAR, game);
	map[0] = cd_add_new_array_line(cd_strtoi_m(line, line_len, '0'), map[0]);
	game->map.height ++;
	if (line_len > game->map.width)
		game->map.width = line_len;
}

void	cd_setup_txt_maps(char *line, t_game *game, int ***map, int step)
{
	int	line_len;

	line_len = cd_parse_line(&line, game, step);
	if (line_len == -1)
		error_handler(BAD_CHAR, game);
	game->graphic.tp_h ++;
	if (line_len > game->map.width || game->graphic.tp_h > game->map.height)
		error_handler(BAD_MAPS, game);
	map[0] = cd_add_new_array_line(cd_strtoi_m(line, line_len, ' '), map[0]);
}