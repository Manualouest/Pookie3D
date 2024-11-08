/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.F r>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:13:17 by malbrech          #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.F r       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

// len d'un tab
int	tab_len(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
		i ++;
	return (i);
}

// Recupere une string et l'ajoute dans un tableau de string existant
char	**add_new_line(char *line, char **tab)
{
	char		**new_tab;
	int			len_tab;
	int			i;

	len_tab = tab_len(tab);
	new_tab = malloc(sizeof(*new_tab) * (len_tab + 2));
	new_tab[len_tab + 1] = NULL;
	new_tab[len_tab] = line;
	i = -1;
	while (tab && ++i < len_tab)
		new_tab[i] = tab[i];
	if (tab)
		free(tab);
	return (new_tab);
}
