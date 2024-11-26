/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:33:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/26 16:45:53 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_infos(t_game *game)
{
	char	*buff;
	int		i;
	int		true_line;

	true_line = 0;
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd == -1)
		error_handler(NO_FILE, game, NULL);
	buff = get_next_line(game->map.fd);
	i = 1;
	while (buff != NULL)
	{
		if (buff == NULL)
			break ;
		if (buff[0] == '\n' && true_line > 6)
			error_handler(FORMAT_ERR, game, buff);
		else
			scanner(buff, game, &true_line);
		buff = get_next_line(game->map.fd);
		i++;
	}
	if (game->map.height > 0)
		cd_parse_map(game, &game->map);
	if (game->map.height <= 0 || game->map.player.x == -1)
		error_handler(FORMAT_ERR, game, NULL);
}

void	scanner(char *line, t_game *game, int *true_line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (*true_line < 6 && is_direction(line, i, game, true_line))
			return ;
		else if (*true_line < 6 && is_rgb(line, i, game, true_line))
			return ;
		else if (*true_line >= 6 && (line[i] == '0' || line[i] == '1'))
		{
			*true_line += 1;
			cd_setup_map(line, game);
			return ;
		}
		else if (line[i] != '\n')
			error_handler(FORMAT_ERR, game, line);
	}
	if (line[i] == '\n')
	{
		free(line);
		return ;
	}
}

int	is_no_so(char *line, int i, t_game *game, int *true_line)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		if (game->graphic.paths[NO] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[NO] = line;
		*true_line += 1;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		if (game->graphic.paths[SO] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[SO] = line;
		*true_line += 1;
	}
	else
		return (0);
	return (1);
}

int	is_direction(char *line, int i, t_game *game, int *true_line)
{
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		if (game->graphic.paths[WE] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[WE] = line;
		*true_line += 1;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		if (game->graphic.paths[EA] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[EA] = line;
		*true_line += 1;
	}
	else
		return (is_no_so(line, i, game, true_line));
	return (1);
}

int	is_rgb(char *line, int i, t_game *game, int *true_line)
{
	if (line[i] == 'C')
	{
		if (game->graphic.paths[C] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[C] = line;
		*true_line += 1;
	}
	else if (line[i] == 'F')
	{
		if (game->graphic.paths[F] != NULL)
			error_handler(DUP_ERROR, game, line);
		game->graphic.paths[F] = line;
		*true_line += 1;
	}
	else
		return (0);
	return (1);
}
