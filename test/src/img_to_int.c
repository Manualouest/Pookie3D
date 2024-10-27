/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:45:54 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/25 10:52:20 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	cd_create_rgba(char	*color)
{
	int		r;
	int		g;
	int		b;
	int		a;
	char	**split_color;

	split_color = ft_split(color, ',');
	r = ft_atoi(split_color[0]);
	g = ft_atoi(split_color[1]);
	b = ft_atoi(split_color[2]);
	a = 0xFF;
	free(split_color[0]);
	free(split_color[1]);
	free(split_color[2]);
	free(split_color);
	return (r << 24 | g << 16 | b << 8 | a);
}

int	cd_get_pixel_color(mlx_texture_t *txt, int x, int y)
{
	int	pos;
	int	r;
	int	g;
	int	b;
	int	a;

	pos = (y * txt->width + x) * txt->bytes_per_pixel;
	r = txt->pixels[pos];
	g = txt->pixels[pos + 1];
	b = txt->pixels[pos + 2];
	a = txt->pixels[pos + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int	**cd_extract_pixel(mlx_texture_t *txt, int is_flipped)
{
	int	**pixels;
	int	i;
	int	ii;

	pixels = ft_calloc(sizeof(*pixels), txt->height + 2);
	pixels[0] = ft_calloc(sizeof(int *), 2);
	pixels[0][0] = (int)txt->width - 1;
	pixels[0][1] = (int)txt->height - 1;
	pixels[txt->width + 1] = ft_calloc(sizeof(int *), 1);
	pixels[txt->width + 1][0] = -1;
	i = 0;
	while (++i < (int)txt->width)
	{
		pixels[i] = ft_calloc(sizeof(*(pixels[i])), txt->height + 1);
		pixels[i][txt->height] = -1;
		ii = -1;
		while (++ii < (int)txt->height)
		{
			if (!is_flipped)
				pixels[i][ii] = cd_get_pixel_color(txt, i, ii);
			else
				pixels[i][ii] = cd_get_pixel_color(txt, pixels[0][0] - i, ii);
		}
	}
	return (pixels);
}

void	cd_img_to_int(t_textures *graphic)
{
	mlx_texture_t	*txt;
	int				i;

	i = -1;
	while (++i < 95)
	{
		if (graphic->slots[i] == 0)
			continue ;
		txt = mlx_load_png(graphic->paths[i]);
		graphic->txts[i] = cd_extract_pixel(txt, 0);
		free(graphic->paths[i]);
	}
}
