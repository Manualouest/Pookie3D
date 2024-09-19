/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:18:09 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/18 17:28:07 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

//fonction pout checker le type du fichier (.cub)
void	check_name_cub(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (!(path[i - 1] == 'b' && path[i - 2] == 'u'
			&& path[i - 3] == 'c' && path[i - 4] == '.'))
	{
		error_handler(CUB);
		//ft_terminate_game(game);
	}
}

//fonction pout checker le type du fichier (.png)
void	check_name_png(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
		i++;
	if (!(path[i - 1] == 'g' && path[i - 2] == 'n'
			&& path[i - 3] == 'p' && path[i - 4] == '.'))
	{
		error_handler(CUB);
		//ft_terminate_game(game);
	}
}