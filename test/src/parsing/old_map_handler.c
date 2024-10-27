/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_map_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:01:16 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/24 18:45:11 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_setup_map(char	*line, t_game *game)
{
	int	i;

	i = -1;
	while (++i >= 0 && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& game->map.player.x == -1 && (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W'))
		{
			cd_set_orientation(game, line[i], i);
			line[i] = '0';
		}
		else if (line[i] != ' ' && line[i] != '0' && line[i] != '1')
			i = -2;
	}
	line[i] = 0;
	if (i > game->map.width)
		game->map.width = i;
	game->map.map = add_new_line(line, game->map.map);
	game->map.height += 1;
	if (i < 0)
		error_handler(BAD_CHAR, game);
}

char	*cd_resize_map_line(char *line, int line_len, int width)
{
	char	*new_line;

	new_line = ft_calloc(sizeof(char), width + 1);
	ft_strlcpy(new_line, line, line_len + 1);
	while (line_len < width)
	{
		new_line[line_len] = ' ';
		line_len ++;
	}
	free(line);
	return (new_line);
}

int	cd_check_edges(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
	{
		if (map->map[i][0] == '0' || map->map[i][map->width - 1] == '0')
			return (0);
	}
	i = -1;
	while (++i < map->width)
	{
		if (map->map[0][i] == '0' || map->map[map->height - 1][i] == '0')
			return (0);
	}
	return (1);
}

void	cd_parse_map(t_game *game, t_map *map)
{
	int	i;
	int	ii;

	i = -1;
	while (++i >= 0 && map->map[i])
	{
		ii = ft_strlen(map->map[i]);
		if (ii < map->width)
			map->map[i] = cd_resize_map_line(map->map[i], ii, map->width);
		ii = -1;
		while (i >= 0 && ++ii < map->width)
		{
			if (map->map[i][ii] == ' ' && (map->map[i - (i > 0)][ii] == '0'
				|| map->map[i + (!(!map->map[i + 1]))][ii] == '0'
				|| map->map[i][ii + (!(!map->map[i][ii + 1]))] == '0'
				|| map->map[i][ii - (ii > 0)] == '0'))
				i = -2;
			if (i >= 0 && map->map[i][ii] == ' ')
				map->map[i][ii] = '1';
		}
	}
	if (i < 0 || !cd_check_edges(map))
		error_handler(BAD_MAP, game);
}
