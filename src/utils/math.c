/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:46:20 by mbirou            #+#    #+#             */
/*   Updated: 2024/09/30 13:48:18 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	cd_clamp(float num, float min, float max)
{
	while (num < min)
		num += max;
	while (num > max)
		num -= max;
	return (num);
}
