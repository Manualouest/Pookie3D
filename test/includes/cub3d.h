/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrech <malbrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:38 by mbirou            #+#    #+#             */
/*   Updated: 2024/10/28 16:12:58 by malbrech         ###   ########.fr       */
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

typedef struct	s_textures
{
	int		**txts[95];
	int		**wmap;
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

typedef struct s_position
{
	float	x;
	float	y;
	float	view;
	float	height;
	float	pitch;
	float	planex;
	float	planey;
	float	dirx;
	float	diry;
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
	float				stepx;
	float				stepy;
	float				floorx;
	float				floory;
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
	t_map		map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*fps;
	t_ray_info	rays;
	t_f_c_info	c_f_info;
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
void	cd_camera(t_game *game);
void	cd_moove(t_game *game);
void	cd_keys_conditions(mlx_key_data_t keydata, t_game *game);
void	cd_camera_conditions(mlx_key_data_t keydata, t_game *game);

// --wall_edition.c
// void		cd_edit_wall(t_game *game, char new_wall);


// -----raycast----------------------------------------------------------------
// --raycast.c
void		cd_render(void *vgame);

// --draw_walls.c
void		cd_draw_floor(t_game *game);
int			cd_darken_color(uint32_t color, float amount);
void		cd_draw_walls(t_game *game, t_ray_info *ray, int x);
void		cd_draw_c_f(t_game *game, int x);

// --floor_maker.c
void		cd_launch_threads(t_game *game);
int			cd_is_floor_done(t_f_c_info *info);
void		cd_floor_maker(t_f_c_info *info);

// -----main-------------------------------------------------------------------
// --error.c
void		cd_free_int_tab(int **tab);
void		error_handler(char *ERR_MSG, t_game *game);
void		cd_free_all(t_game *game);

// --img_to_int.c
int			**cd_extract_pixel(mlx_texture_t *txt, int is_flipped);
void		cd_img_to_int(t_textures *graphic);
int			cd_create_rgba(char	*color);

// --thread_utils.c

void		cd_thread_init(t_game *game);
void		cd_thread_destroy(t_game *game);
// int			cd_is_floor_done(t_f_c_info *info);
// int			cd_check_game_status(t_f_c_info *info);
// void		cd_switch_floor_status(t_f_c_info *info);

#endif