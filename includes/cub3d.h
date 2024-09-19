/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:38 by mbirou            #+#    #+#             */
/*   Updated: 2024/09/19 17:49:42 by mbirou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------------- INCLUDES ----------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <unistd.h>
# include <MLX42/MLX42.h>
# include <libft.h>

/*------------------ STRUCTURES --------------------*/

typedef struct	s_textures
{
	int		**so;
	int		**no;
	int		**we;
	int		**ea;
	int		c;
	int 	f;
	char	*paths[7];
	int		width;
	int		height;
	int		dim_id;
}		t_textures;

typedef struct s_position
{
	float	x;
	float	y;
	float	view;
	float	height;
	float	pitch;
}	t_position;

typedef struct s_map
{
	char		**map;
	char		*path;
	int			height;
	int			width;
	int			fd;
	t_position	player;
}	t_map;

typedef struct s_ray_info
{
	float	x;
	float	y;
	float	t_x;
	float	angle;
	float	distance;
	float	wall_height;
	double	dx;
	double	dy;
	double	delta_dx;
	double	delta_dy;
	double	side_dx;
	double	side_dy;
	int		side;
	int		step_x;
	int		step_y;
}            t_ray_info;

typedef struct s_game
{
	t_map		map;
	mlx_t		*mlx;
	t_ray_info	rays;
	t_textures	graphic;		
}	t_game;

/*------------------- ENUM ----------------------*/

typedef enum e_ids
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}				t_ids;

/*---------------- ERROR MSG --------------------*/

# define CUB_ERR ".cub file required"
# define PNG_ERR ".png file required"
# define FORMAT_ERR "The map doesn't follow the game's format"
# define BAD_CHAR "Invalid character in map"
# define BAD_MAP "Map borders are invalid"

/*----------------- FONCTIONS -------------------*/

// -----map_maker-----
// map_maker_main.c
char	*cd_map_maker(void);

// -----init-----
// init_game.c
t_game	cd_init_structs(char *map_file);

// ------parser-------

void	parser(t_game *game);
void	get_infos(t_game *game);
void	scanner(char *line, t_game *game, int *true_line);
int		is_direction(char *line, int i, int *true_line, t_game *game);
int		is_rgb(char *line, int i, int *true_line, t_game *game);
void	cd_setup_map(char	*line, t_game *game);
void	cd_parse_map(t_game *game, t_map *map);
void	check_name_cub(char *path, t_game *game);
void	check_name_png(char *path, t_game *game);

// -----utils-----
// tab_utils.c
char	**add_new_line(char *line, char **tab);

// error.c
void	error_handler(char *ERR_MSG, t_game *game);
void	cd_free_all(t_game *game);

// img_to_int.c
void	cd_img_to_int(t_textures *graphic);
void	cd_set_txt_dimmension(t_textures *graphic, int id);


#endif