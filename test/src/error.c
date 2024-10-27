/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:05:39 by malbrech          #+#    #+#             */
/*   Updated: 2024/10/24 21:46:45 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cd_free_int_tab(int **tab)
{
	int	i;
	int	len;

	i = -1;
	len = tab[0][1] + 2;
	while (++i <= len)
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
	// cd_free_int_tab(game->graphic.so);
	// cd_free_int_tab(game->graphic.no);
	// cd_free_int_tab(game->graphic.we);
	// cd_free_int_tab(game->graphic.ea);
	// i = -1;
	// while (++i < 95)
	// {
	// 	if (**game->graphic.txts[i] != -1)
	// 	{
	// 		printf("i: %d\n", i);
	// 		cd_free_int_tab(game->graphic.txts[i]);
	// 	}
	// }
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
