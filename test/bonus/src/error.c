/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:05:39 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	cd_free_int_img(int **tab)
{
	int	i;
	int	len;

	i = -1;
	len = tab[0][1] + 2;
	while (++i <= len)
		free(tab[i]);
	free(tab);
}

void	cd_free_int_tab(int **tab)
{
	int	i;

	i = -1;
	while (tab[++i][0] != -1)
		free(tab[i]);
	free(tab[i]);
	free(tab);
}

void	cd_free_all(t_game *game)
{
	int	i;

	i = -1;
	if (game->map.path)
		free(game->map.path);
	while (++i < 94)
	{
		if (game->graphic.slots[i] == 0)
			continue ;
		cd_free_int_img(game->graphic.txts[i]);
	}
	cd_free_int_tab(game->map.map);
	cd_free_int_tab(game->graphic.tmap);
	cd_free_int_tab(game->graphic.fmap);
	cd_free_int_tab(game->graphic.rmap);
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->fps)
		mlx_delete_image(game->mlx, game->fps);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	error_handler(char *ERR_MSG, t_game *game)
{
	ft_putstr_fd(ERR_MSG, 1);
	cd_free_all(game);
	(void)game;
	exit(0);
}
