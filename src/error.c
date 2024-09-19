/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:05:39 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/19 17:49:11 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_free_int_tab(int **tab)
{
	int	i;

	i = -1;
	while (tab != 0 && tab[i][0] != -1)
		free(tab[i]);
	free(tab);
}

void	cd_free_all(t_game *game)
{
	int	i;

	i = -1;
	while (game->map.map && game->map.map[++i])
		free(game->map.map[i]);
	if (game->map.map)
		free(game->map.map);
	if (game->map.path)
		free(game->map.path);
	cd_free_int_tab(game->graphic.so);
	cd_free_int_tab(game->graphic.no);
	cd_free_int_tab(game->graphic.we);
	cd_free_int_tab(game->graphic.ea);
	i = -1;
}

void	error_handler(char *ERR_MSG, t_game *game)
{
	ft_putstr_fd(ERR_MSG, 1);
	cd_free_all(game);
	(void)game;
	exit(0);
}
