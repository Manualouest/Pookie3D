/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:38 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/22 13:25:44 by mbirou           ###   ########.fr       */
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

typedef struct s_textures
{
	int		**so;
	int		**no;
	int		**we;
	int		**ea;
	int		c;
	int		f;
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
	float		fov;
	t_position	player;
}	t_map;

typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	up;
	int	down;
	int	left;
	int	right;
}	t_keys;

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
	float	effect;
}			t_ray_info;

typedef struct s_game
{
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*fps;
	t_ray_info	rays;
	t_textures	graphic;
	t_keys		keys;	
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

# define CUB_ERR ".cub file required\n"
# define PNG_ERR ".png file required\n"
# define FORMAT_ERR "The file doesn't follow the game's format\n"
# define BAD_CHAR "Invalid character in map\n"
# define BAD_MAP "Map borders are invalid\n"
# define MLX_ERROR "Mlx didn't work properly\n"
# define BAD_COLOR "Color is not well formated\n"
# define PNG_NOT_FOUND "Could not find the png given.\n"
# define PARAM_ERROR "Bad number of parameters\n"
# define NO_FILE "File could not be found\n"
# define MALLOC_FAIL "A malloc has failed\n"
# define DUP_ERROR "There is duplicate definition\n"

/*----------------- FONCTIONS -------------------*/

// -----map_maker--------------------------------------------------------------
// --map_maker_main.c
char	*cd_map_maker(void);

// -----init-------------------------------------------------------------------
// --init_game.c
t_game	cd_init_structs(char *map_file);
void	cd_init_keys(t_game *game);

// --init_single_struct.c
int		**cd_get_empty_tab(void);
void	cd_init_graphic(t_game *game);

// ------parsing---------------------------------------------------------------
// --parser.c
void	get_infos(t_game *game);
void	scanner(char *line, t_game *game, int *true_line);
int		is_direction(char *line, int i, t_game *game, int *true_line);
int		is_rgb(char *line, int i, t_game *game, int *true_line);

// --map_handler.c
void	cd_setup_map(char	*line, t_game *game);
void	cd_parse_map(t_game *game, t_map *map);

// --check.c
void	check_name_cub(char *path, t_game *game);
void	check_name_png(char *txt, t_game *game);

// -----utils------------------------------------------------------------------
// --string_utils.c
void	format_d_tab(char *paths[7], t_game *game);

// --tab_utils.c
int		tab_len(char **tab);
char	**add_new_line(char *line, char **tab);

// --math.c
float	cd_clamp(float num, float min, float max);
float	cd_clamp_two(float num, float min, float max);

// -----keys-------------------------------------------------------------------
// --keys.c
void	cd_keys(mlx_key_data_t keydata, t_game *game);
void	cd_moove_forward(t_game *game);
void	cd_moove_backward(t_game *game);
void	cd_moove_left(t_game *game);
void	cd_moove_right(t_game *game);
void	cd_camera(t_game *game);
void	cd_moove(t_game *game);
void	cd_keys_conditions(mlx_key_data_t keydata, t_game *game);
void	cd_camera_conditions(mlx_key_data_t keydata, t_game *game);

// -----raycast----------------------------------------------------------------
// --raycast.c
void	cd_render(void *vgame);

// --draw_walls.c
void	cd_draw_walls(t_game *game, t_ray_info *ray, int x);
void	cd_draw_c_f(t_game *game, int x);

// -----main-------------------------------------------------------------------
// --error.c
void	cd_free_int_tab(int **tab);
void	cd_free_all(t_game *game);
void	error_handler(char *ERR_MSG, t_game *game, char *line);

// --img_to_int.c
void	cd_img_to_int(t_textures *graphic, t_game *game);

#endif