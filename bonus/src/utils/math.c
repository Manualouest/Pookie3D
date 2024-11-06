/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:46:20 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:32 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float	cd_clamp(float num, float min, float max)
{
	while (num < min)
		num += max;
	while (num > max)
		num -= max;
	return (num);
}

float	cd_clamp_two(float num, float min, float max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}
