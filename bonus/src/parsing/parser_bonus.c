/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:22:09 by mbirou            #+#    #+#             */
/*   Updated: 2025/01/21 17:37:58 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	get_infos(t_game *game);
void	scanner(char *line, t_game *game, int *step);
int		cd_is_step(char *line, t_game *game, int *step, char *o_line);
int		cd_add_texture(t_game *game, char *line, char *o_line);

void	parser(t_game *game)
{
	int	i;

	check_name_cub(game->map.path, game);
	get_infos(game);
	if (cd_array_len(game->map.map) != cd_array_len(game->graphic.tmap)
		|| cd_array_len(game->map.map) != cd_array_len(game->graphic.fmap)
		|| cd_array_len(game->map.map) != cd_array_len(game->graphic.rmap)
		|| cd_array_len(game->map.map) <= 0)
		error_handler(BAD_MAPS, game, NULL);
	i = -1;
	while (game->map.map[++i][0] != -1)
	{
		if (cd_intlen(game->map.map[i]) != cd_intlen(game->graphic.tmap[i])
			|| cd_intlen(game->map.map[i]) != cd_intlen(game->graphic.fmap[i])
			|| cd_intlen(game->map.map[i]) != cd_intlen(game->graphic.rmap[i]))
			error_handler(BAD_MAPS, game, NULL);
	}
}

void	get_infos(t_game *game)
{
	char	*buff;
	int		i;
	int		step;

	step = 0;
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd == -1)
		error_handler(NO_FILE, game, NULL);
	buff = get_next_line(game->map.fd);
	i = 1;
	while (i)
	{
		if (buff == NULL)
			break ;
		if (buff[0] == '\n' && step > 1)
			error_handler(FORMAT_ERR, game, buff);
		if (buff[0] != '\n')
			scanner(buff, game, &step);
		free(buff);
		buff = get_next_line(game->map.fd);
		i++;
	}
	if (buff)
		free(buff);
	resize_maps(game);
}

void	scanner(char *line, t_game *game, int *step)
{
	int	i;

	i = 0;
	while (*step <= 1 && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (i > 0 && line[i - 1] == '\n')
		return ;
	if (cd_is_step(&line[i], game, step, line))
		return ;
	if (*step == 1 && cd_add_texture(game, &line[i], line))
		return ;
	if (*step == 2)
		cd_setup_map(line, game, &game->map.map);
	else if (*step == 3)
		cd_setup_txt_maps(line, game, &game->graphic.tmap, *step);
	else if (*step == 4)
		cd_setup_txt_maps(line, game, &game->graphic.fmap, *step);
	else if (*step == 5)
		cd_setup_txt_maps(line, game, &game->graphic.rmap, *step);
	else
		error_handler(FORMAT_ERR, game, line);
}

int	cd_is_step(char *line, t_game *game, int *step, char *o_line)
{
	if ((*step == 0 && !ft_strcmp(line, "textures:\n"))
		|| (*step == 1 && !ft_strcmp(line, "wmap:\n"))
		|| (*step == 2 && !ft_strcmp(line, "tmap:\n"))
		|| (*step == 3 && !ft_strcmp(line, "fmap:\n"))
		|| (*step == 4 && !ft_strcmp(line, "rmap:\n")))
	{
		game->graphic.tp_h = 0;
		*step += 1;
		return (1);
	}
	else if (!ft_strcmp(line, "textures:\n") || !ft_strcmp(line, "wmap:\n")
		|| !ft_strcmp(line, "tmap:\n") || !ft_strcmp(line, "fmap:\n")
		|| !ft_strcmp(line, "rmap:\n"))
		error_handler(BAD_STEP, game, o_line);
	return (0);
}

int	cd_add_texture(t_game *game, char *line, char *o_line)
{
	int		i;
	char	*n_line;

	if (line[0] < 33 || line[0] > 126 || !line[1] || line[1] != ' '
		|| line[0] == 'S' || line[0] == 'N' || line[0] == 'W' || line[0] == 'E')
		error_handler(BAD_TXT_NAME, game, o_line);
	i = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\t')
		i --;
	if (game->graphic.p[line[0] - 33] != NULL)
		error_handler(DUP_ERROR, game, o_line);
	n_line = ft_substr(line, 2, i - 2);
	game->graphic.p[line[0] - 33] = n_line;
	check_name_png(n_line, game, line);
	game->graphic.slots[line[0] - 33] = 1;
	return (1);
}
