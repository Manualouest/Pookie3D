/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:16:56 by malbrech          #+#    #+#             */
/*   Updated: 2024/09/27 10:42:52 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	format_d_tab(char **paths)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (paths[i])
	{
		while (paths[i][ii])
		{
			skip_direction(paths[i], &ii);
			if (paths[i][ii] == ' ' || paths[i][ii] == '\t')
				ii++;
			else
				format_d_line(paths[i], &ii);
		}
		i++;
	}
}

void	skip_direction(char *line, int *ii)
{
	if (line[*ii] == 'N' && line[*ii + 1] == 'O')
		*ii += 2;
	if (line[*ii] == 'S' && line[*ii + 1] == 'O')
		*ii += 2;
	if (line[*ii] == 'W' && line[*ii + 1] == 'E')
		*ii += 2;
	if (line[*ii] == 'E' && line[*ii + 1] == 'A')
		*ii += 2;
}

void	format_d_line(char *line, int *ii)
{
	int		new_size;
	int		i;
	char	*

	new_size = 0;
	i = *ii;
	while (line[*ii] != ' ' && line[*ii]  != '\t' && line[*ii])
	{
		new_size += 1;
		*ii += 1;
	}
	
}
