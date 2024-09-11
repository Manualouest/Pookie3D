/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:33:08 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/11 10:02:05 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>



// fonction principale du parser
void	parser(t_game *game)

//fonction pout checker le type du fichier (.cub)
void	f_type(t_game *game)

// Recupere la map dans un tablau de str
char	**ft_split_map(t_game *game)
{
	int		fd;
	char	*buff;
	int		i;
	int		line;

	count = 0;
	fd = open(path, O_RDONLY);
	buff = get_next_line(fd);
	count++;
	if (buff == NULL)
		break ;
	while (buff[i])
	{
		i = 0;
		if(buff[i] == ' ' || buff[i] == '/t')
			i++;
		if(buff[i] == '1')
		{
				
		}	
		else
			break
	}
}

// Recupere les couleurs dans un tableau de str
// char	**ft_split_color(char *path, t_game *game)
// {
// 	int		fd;
// 	char	*buff;
// 	char	*buffer;

// 	buffer = ft_strdup("");
// 	fd = open(path, O_RDONLY);
// 	while (1)
// 	{
// 		buff = get_next_line(fd);
// 		if (buff == NULL)
// 			break ;
// 		// buffer = ft_strjoin(buffer, buff);
// 		// free(buff);
// 	}
// 	// free(buff);
// 	// game->full = ft_split(buffer, '\n');
// 	// game->check = ft_split(buffer, '\n');
// 	// free(buffer);
// }
