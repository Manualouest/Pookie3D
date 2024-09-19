/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:33:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/19 13:24:43 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// fonction principale du parser
void		parser(t_game *game)
{
	check_name(game->map.path);
	get_infos(game);
}

// Recupere les infos depuis la map
void	get_infos(t_game *game)
{
	char	*buff;
	int		i;
	int	true_line;
	
	true_line = 0;
	game.map.fd = open(game.map.path, O_RDONLY);
	buff = get_next_line(game.map.fd);
	i = 1;
	while (i)
	{
		scanner(buff, game);
		if (buff == NULL)
			break ;
		free(buff);
		buff = get_next_line(game.map.fd);
		i++;
	}
	free(buff);
}

// Scan les lignes de la map 1 par une pour recuperer les informations
void	scanner(char *line, t_game *game, int *true_line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (is_direction(line, i, true_line, game))
			break ;
		else if (is_rgb(line, i, true_line, game))
			break ;
		else if ((line[i] == '0' || line[i] == '1') && true_line >= 6)
		{
			cd_setup_map(line, game);
			break ;
		}
		else
		{
			error_handler(FORMAT_ERR, game)
			break;
		}
	}
}

// Conditions pour les directions
int	is_direction(char *line, int i, int *true_line, t_game *game)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		add_new_line(line, game.graphic.paths[NO]);
		*true_line += 1;
		return (1);
	}
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		add_new_line(line, game.graphic.paths[SO]);
		*true_line += 1;
		return (1);
	}
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		add_new_line(line, game.graphic.paths[WE]);
		*true_line += 1;
		return (1);
	}
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		add_new_line(line, game.graphic.paths[EA]);
		*true_line += 1;
		return (1);
	}
	return (0);
}

// Conditions pour les couleurs rgb
void	is_rgb(char *line, int i, int *true_line, t_game *game)
{
	if (line[i] == 'C')
	{
		add_new_line(line, game.graphic.paths[C]);
		*true_line += 1;
		return (1);
	}
	if (line[i] == 'F')
	{
		add_new_line(line, game.graphic.paths[F]);
		*true_line += 1;
		return (1);
	}
	return (0);
}
