/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/09/11 09:54:47 by malbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game		game;
	char		*map_file;

	game.error = 0;
	if (argc == 1)
		map_file = cd_map_maker();
	else
		map_file = ft_strdup(argv[1]);
	if (!map_file)
		return (0);
	printf("%s", map_file);
	if (argc > 2)
		return (0);
	// parsing(&game, map_file);
	free(map_file);
	if (game.error == 0)
		return (0);
	// launch_game(game);
	return (1);
}
