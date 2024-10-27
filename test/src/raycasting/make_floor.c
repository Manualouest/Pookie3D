/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:53:09 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/24 21:26:50 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
/* 
int	cd_is_floor_done(t_f_c_info *info)
{
	int	ret;

	pthread_mutex_lock(&info->status_check);
	ret = info->floor_status;
	pthread_mutex_unlock(&info->status_check);
	return (ret);
}

int	cd_check_game_status(t_f_c_info *info)
{
	int	ret;

	pthread_mutex_lock(&info->status_check);
	ret = info->game_status;
	pthread_mutex_unlock(&info->status_check);
	return (ret);
}

void	cd_switch_floor_status(t_f_c_info *info)
{
	pthread_mutex_lock(&info->status_check);
	info->floor_status = 1 - info->floor_status;
	pthread_mutex_unlock(&info->status_check);
}

// void	cd_put_floor(t_f_c_info *info)
// {
// 	float	y;
// 	float	x;
// 	int		tx;
// 	int		ty;

// 	y = -1;
// 	while (++y < info->height)
// 	{
// 		info->rowdst = (info->height) / 2. / (y - info->mid + 0.01);
// 		info->stepx = info->rowdst * (info->dirx1 - info->dirx0) / info->width;
// 		info->stepy = info->rowdst * (info->diry1 - info->diry0) / info->width;
// 		info->floorx = info->pos_x + info->rowdst * info->dirx0;
//       	info->floory = info->pos_y + info->rowdst * info->diry0;
// 		// printf("rowdst: %f, fstepx: %f, fstepy: %f, info->floorx: %f, info->floory: %f\n", info->rowdst, info->stepx, info->stepy, info->floorx, info->floory);
// 		x = -1;
// 		while (++x < info->width)
// 		{
// 			tx = ((float)info->floor_t[0][0] * (info->floorx - floor(info->floorx)));// / (info->floor[0][0]);
// 			ty = ((float)info->floor_t[0][1] * (info->floory - floor(info->floory)));// / (info->floor[0][1]);
// 			info->floorx += info->stepx;
// 			info->floory += info->stepy;
// 			// printf("tx: %d, ty: %d, info->floorx: %f, info->floory: %f\n", tx, ty, info->floorx, info->floory);
// 			mlx_put_pixel(info->floor, x, y, info->floor_t[tx + 1][ty]);
// 		}
// 	}
// }

void	cd_put_floor(t_f_c_info *info, int type, int **texture)
{
	uint32_t	color;
	float		floorx;
	float		floory;
	int			tx;
	int			ty;

	if (!type)
		return ;
	info->row_dst = info->height / 2.
		/ (info->y - info->mid + 0.01);
	floorx = type * info->pos_x + info->row_dst * info->dx0;
	floory = type * info->pos_y + info->row_dst * info->dy0;
	floorx += info->x * info->row_dst * info->stepx;
	floory += info->x * info->row_dst * info->stepy;
	tx = ((float)texture[0][0] * (floorx - floor(floorx)));
	ty = ((float)texture[0][1] * (floory - floor(floory)));
	color = cd_darken_color(texture[tx + 1][ty],
		info->mid / fabs(info->y - info->mid));
	mlx_put_pixel(info->img, info->x, info->y, color);
}

void	cd_floor_maker(t_f_c_info *info)
{
	while (cd_check_game_status(info))
	{
		while (cd_is_floor_done(info) && cd_check_game_status(info))
			usleep(10);
		info->y = -1;
		while (++info->y < info->height)
		{
			info->x = -1;
			if (info->y < info->mid)
			{
				while (++info->x < info->width)
					cd_put_floor(info, -1, info->floor_t);
			}
			else
			{
				while (++info->x < info->width)
					cd_put_floor(info, 1, info->floor_t);
			}
			if (!cd_check_game_status(info))
				return ;
		}
		cd_switch_floor_status(info);
	}
}
 */