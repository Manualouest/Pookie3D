/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <manutea.birou@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:38 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/04 18:04:32 by mbirou           ###   ########.fr       */
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

# include <string.h>
# include <pthread.h>

/*------------------ STRUCTURES --------------------*/

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct	s_textures
{
	int		**txts[95];
	int		**tmap;
	int		**fmap;
	int		**rmap;
	char	*paths[95];
	char	slots[95];
	float	width;
	float	width_mod;
	float	height;
	float	up_op;
	int		tp_h;
	int		up;
	int		down;
	float	y_ratio;
	float	dim;
	float	incr;
}			t_textures;

typedef struct s_data_player
{
	float	x;
	float	y;
	float	view;
	float	height;
	float	pitch;
	float	speed;
	float	coeff;
	float	planex;
	float	planey;
	float	dirx;
	float	diry;
}	t_data_player;

typedef struct s_map
{
	int			**map;
	char		*path;
	int			height;
	int			width;
	int			fd;
	float		fov;
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
	int	space;
	int	shift;
	int	ctrl;
	int	fps;
}	t_keys;

typedef struct s_ray_info
{
	float	x;
	float	y;
	float	t_x;
	// float	angle;
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

typedef struct s_f_c_info
{
	pthread_t			thread;
	float				dx0;
	float				dy0;
	float				dx1;
	float				dy1;
	float				mx;
	float				my;
	float				stepx;
	float				stepy;
	float				row_dst;
	float				mid;
	float				height;
	float				width;
	float				pos_x;
	float				pos_y;
	int					x;
	int					y;
	int					**floor_t;
	int					**roof_t;
	mlx_image_t			*img;
	int					floor_status;
	int					game_status;
	pthread_mutex_t		status_check;
}						t_f_c_info;

typedef struct s_game
{
	t_map			map;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*fps;
	t_ray_info		rays;
	t_f_c_info		c_f_info;
	t_textures		graphic;
	t_keys			keys;
	t_data_player	player;
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

/*---------------- DEFINE VALUES ----------------*/
// --Speeds
# define RUNNING_SPEED 6.
# define CROUCH_SPEED 2.
# define WALKING_SPEED 3.
# define CAMERA_SPEED 0.03
# define ROTATE_SPEED 0.0025

//--Heights
# define CROUCH_HEIGHT -0.1
# define NORMAL_HEIGHT 0

/*---------------- ERROR MSG --------------------*/

# define CUB_ERR ".cub file required"
# define PNG_ERR ".png file required"
# define FORMAT_ERR "The map doesn't follow the game's format: "
# define BAD_CHAR "Invalid character in map"
# define BAD_MAP "Map borders are invalid"
# define BAD_STEP "Step error"
# define BAD_TXT_NAME "Texture has an invalid definition"
# define BAD_MAPS "One of the texture maps is bigger than the wall map"

/*----------------- FONCTIONS -------------------*/

// -----map_maker--------------------------------------------------------------
// --map_maker_main.c
char		*cd_map_maker(void);

// -----init-------------------------------------------------------------------
// --init_game.c
t_game		cd_init_structs(char *map_file);
void		cd_init_keys(t_game *game);

// --init_single_struct.c
t_ray_info	cd_create_rays(void);


// ------parsing---------------------------------------------------------------
// --parser.c
void		parser(t_game *game);
void		get_infos(t_game *game);
void		scanner(char *line, t_game *game, int *true_line);
int			is_direction(char *line, int i, int *true_line, t_game *game);
int			is_rgb(char *line, int i, int *true_line, t_game *game);

// --map_handler.c
// void		cd_setup_map(char	*line, t_game *game);
// void		cd_parse_map(t_game *game, t_map *map);
void		cd_setup_map(char *line, t_game *game, int ***map);
void		cd_setup_txt_maps(char *line, t_game *game, int ***map, int step);

// --check.c
void		check_name_cub(char *path, t_game *game);
void		check_name_png(char *path, t_game *game);


// -----utils------------------------------------------------------------------

// --string_utils.c
void	format_d_tab(char *paths[7]);
void	skip_direction(char *line, int *ii);
char	*format_d_line(char *line, int *ii);

// --tab_utils.c
char	**add_new_line(char *line, char **tab);

// --math.c
float	cd_clamp(float num, float min, float max);
float	cd_clamp_two(float num, float min, float max);

// --controllers.c
void		player_speed_controller(t_game *game);
void		player_height_controller(t_game *game);
void    	mouse_controller(t_game *game);

// --array_utils.c
int		cd_intlen(int *line);
int		*cd_strtoi_m(char *line, int line_len, int dif);
int		cd_array_len(int	**array);
int		**cd_add_new_array_line(int *line, int **array);

// -----keys-------------------------------------------------------------------
// --keys.c
void	cd_keys(mlx_key_data_t keydata, t_game *game);
void	cd_moove_forward(t_game *game);
void	cd_moove_backward(t_game *game);
void	cd_moove_left(t_game *game);
void	cd_moove_right(t_game *game);
void	cd_jump(t_game *game);
void	cd_camera(t_game *game);
void	cd_moove(t_game *game);
void	cd_directions_conditions(mlx_key_data_t keydata, t_game *game);
void	cd_actions_conditions(mlx_key_data_t keydata, t_game *game);
void	cd_camera_conditions(mlx_key_data_t keydata, t_game *game);

// --wall_edition.c
// void		cd_edit_wall(t_game *game, char new_wall);


// -----raycast----------------------------------------------------------------
// --raycast.c
void		cd_render(t_game *game);

// --draw_walls.c
void		cd_reduce_color(t_game *game, int x, int y, float effect);
void		cd_draw_walls(t_game *game, t_ray_info *ray, int x);
void		cd_draw_c_f(t_game *game, int x);

// --draw_tiles.c
void		cd_draw_tiles(t_game *game, int x);

// -----main-------------------------------------------------------------------
// --error.c
void		cd_free_int_tab(int **tab);
void		error_handler(char *ERR_MSG, t_game *game);
void		cd_free_all(t_game *game);

// --img_to_int.c
int			**cd_extract_pixel(mlx_texture_t *txt, int is_flipped);
void		cd_img_to_int(t_textures *graphic);

// --thread_utils.c

void		cd_thread_init(t_game *game);
void		cd_thread_destroy(t_game *game);
// int			cd_is_floor_done(t_f_c_info *info);
// int			cd_check_game_status(t_f_c_info *info);
// void		cd_switch_floor_status(t_f_c_info *info);

#endif