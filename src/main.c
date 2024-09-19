/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:54:35 by mbirou            #+#    #+#             */
/*   Updated: 2024/09/19 17:50:52 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game		game;
	char		*map_file;

	if (argc == 1)
		map_file = cd_map_maker();
	else
		map_file = ft_strdup(argv[1]);
	if (!map_file)
		return (0);
	printf("%s", map_file);
	if (argc > 2)
		return (0);
	game = cd_init_structs(map_file);
	parser(&game);
	
	printf("paths:\n");
	int	i = -1;
	while (game.graphic.paths[++i])
		printf("%s\n", game.graphic.paths[i]);
	
	printf("map:\n");
	i = -1;
	while (game.map.map[++i])
		printf("%s\n", game.map.map[i]);


	cd_free_all(&game);
	//launch_game(game);
	return (1);
}
