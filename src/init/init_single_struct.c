/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_single_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:52:56 by mbirou            #+#    #+#             */
/*   Updated: 2024/09/27 10:55:21 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray_info	cd_create_rays(void)
{
	t_ray_info	rays;

	rays.x = 0;
	rays.y = 0;
	rays.t_x = 0;
	rays.angle = 0;
	rays.distance = 0;
	rays.wall_height = 0;
	rays.dx = 0;
	rays.dy = 0;
	rays.delta_dx = 0;
	rays.delta_dy = 0;
	rays.side_dx = 0;
	rays.side_dy = 0;
	rays.side = 0;
	rays.step_x = 0;
	rays.step_y = 0;
	return (rays);
}