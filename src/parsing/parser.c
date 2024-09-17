/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:33:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/17 09:49:50 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// fonction principale du parser
void		parser(t_game *game)
{
	check_name(game->map.path);
	get_infos(game);
}

//fonction pout checker le type du fichier (.cub)
void	check_name(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (!(path[i - 1] == 'b' && path[i - 2] == 'u'
			&& path[i - 3] == 'c' && path[i - 4] == '.'))
	{
		error_handler(CUB);
		ft_terminate_game(game);
	}
}

// Recupere les infos depuis la map
void	get_infos(t_game *game)
{
	char *buff;
	
	game->map.fd = open(game->map.path, O_RDONLY);
	buff = get_next_line(game->map.fd);
	while(1)
	{
		scanner(buff, game);
		if (buff == NULL)
			break ;
		free(buff);
		buff = get_next_line(game->map.fd);
	}
	free(buff);
}

// Scan les lignes de la map 1 par une
void	scanner(char *line, t_game *game)
{
	int	i;
	
	while(line[i])
	{
		if (line[i] == ' ')
			i++;
		if 
		i++;
	}
}

// Recupere une string et l'ajoute dans un tableau de string existant
void	
