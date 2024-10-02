/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:18:09 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/27 10:44:00 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//fonction pout checker le type du fichier (.cub)
void	check_name_cub(char *path, t_game *game)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (!(path[i - 1] == 'b' && path[i - 2] == 'u'
			&& path[i - 3] == 'c' && path[i - 4] == '.'))
	{
		error_handler(CUB_ERR, game);
	}
}

//fonction pout checker le type du fichier (.png)
void	check_name_png(char *path, t_game *game)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (!(path[i - 1] == 'g' && path[i - 2] == 'n'
			&& path[i - 3] == 'p' && path[i - 4] == '.'))
	{
		error_handler(PNG_ERR, game);
	}
}
