/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:33:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/18 16:09:01 by malbrech         ###   ########.fr       */
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
	
	game.map.fd = open(game.map.path, O_RDONLY);
	buff = get_next_line(game.map.fd);
	i = 0;
	while(i >= 0)
	{
		scanner(buff, game.graphic);
		if (buff == NULL)
			break ;
		free(buff);
		buff = get_next_line(game.map.fd);
		i++;
	}
	free(buff);
}

// Scan les lignes de la map 1 par une pour recuperer les informations
void	scanner(char *line, t_textures *graphic)
{
	int	i;
	
	i = 0;
	while(line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if(is_direction(line, i))
			break ;
		if(is_rgb(line, i))
			break ;
	}
}

// Conditions pour les directions
int	is_direction(char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		add_new_line(line, graphic.paths[0]);
		return (1);
	}
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		add_new_line(line, graphic.paths[1]);
		return (1);
	}
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		add_new_line(line, graphic.paths[2]);
		return (1);
	}
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		add_new_line(line, graphic.paths[3]);
		return (1);
	}
	return (0);
}

// Conditions pour les couleurs rgb
void	is_rgb(char *line, int i)
{
	if (line[i] == 'C')
	{
		add_new_line(line, graphic.paths[4]);
		return (1);
	}
	if (line[i] == 'F')
	{
		add_new_line(line, graphic.paths[5]);
		return (1);
	}
	return (0);
}
