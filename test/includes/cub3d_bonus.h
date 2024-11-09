/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbirou <mbirou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:27:38 by mbirou            #+#    #+#             */
/*   Updated: 2024/11/09 18:55:16 by mbirou           ###   ########.fr       */
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

#include <emmintrin.h>

# include <string.h>
# include <pthread.h>

/*------------------ STRUCTURES --------------------*/

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_sprite_vars
{
	float	trsx;
	float	trsy;
	int		screenx;
	int		sp_height;
	int		sp_width;
	int		txty;
	int		txtx;
	int		y_op;
	float	x;
	float	y;
	float	stry;
	float	endy;
	float	strx;
	float	endx;
}			t_sprite_vars;


typedef struct	s_sprite
{
	float	x;
	float	y;
	float	distance;
	float	height;
	int		direction;
	int		tile;
	int		**txt;
}			t_sprite;

typedef struct t_inventory
{
	int					tile;
	struct t_inventory *next;
}						t_inventory;

typedef struct	s_textures
{
	int			**txts[94];
	int			**tmap;
	int			**fmap;
	int			**rmap;
	char		*paths[94];
	char		slots[94];
	t_sprite	**sprites;
	float		width;
	float		width_mod;
	float		height;
	float		up_op;
	int			tp_h;
	int			up;
	int			down;
	float		y_ratio;
	float		incr;
	float		dim;
}				t_textures;

typedef struct s_data_player
{
	float		x;
	float		y;
	float		view;
	float		height;
	float		pitch;
	float		speed;
	float		jump_coeff;
	float		jog_coeff;
	float		planex;
	float		planey;
	float		dirx;
	float		diry;
	t_inventory	*inventory;
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
	int	destroy;
	int	place;
	int	mouse;
}	t_keys;

typedef struct s_ray_info
{
	float	x;
	float	y;
	float	x_save;
	float	y_save;
	float	distance_save;
	float	t_x;
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
	int		*distances;
}			t_ray_info;

typedef struct s_t_info
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
}						t_t_info;

typedef struct s_game
{
	t_map			map;
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*fps;
	mlx_image_t		*gui;
	t_ray_info		rays;
	t_t_info		t_info;
	t_keys			keys;
	t_data_player	player;
	t_textures		graphic;
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
# define NORMAL_HEIGHT 0.05
# define JOG_HEIGHT 0.045

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
void		format_d_tab(char *paths[7]);
void		skip_direction(char *line, int *ii);
char		*format_d_line(char *line, int *ii);

// --tab_utils.c
char		**add_new_line(char *line, char **tab);

// --math.c
float		cd_clamp(float num, float min, float max);
float		cd_clamp_two(float num, float min, float max);

// --controllers.c
void		player_speed_controller(t_game *game);
void		player_height_controller(t_game *game);
void    	mouse_controller(t_game *game);

// --array_utils.c
int			cd_intlen(int *line);
int			*cd_strtoi_m(char *line, int line_len, int dif);
int			cd_array_len(int	**array);
int			**cd_add_new_array_line(int *line, int **array);

// -----keys-------------------------------------------------------------------
// --keys.c
void		cd_keys(mlx_key_data_t keydata, t_game *game);
void		cd_moove_forward(t_game *game);
void		cd_moove_backward(t_game *game);
void		cd_moove_left(t_game *game);
void		cd_moove_right(t_game *game);
void		cd_jump(t_game *game);
void		cd_moove(t_game *game);
void		cd_directions_conditions(mlx_key_data_t keydata, t_game *game);
void		cd_actions_conditions(mlx_key_data_t keydata, t_game *game);
void		cd_camera_conditions(mlx_key_data_t keydata, t_game *game);
void		cd_walk(t_game *game);

// --camera.h
void		cd_right(t_game *game, float amount);
void		cd_left(t_game *game, float amount);
void		cd_up(t_game *game, float amount);
void		cd_down(t_game *game, float amount);
void		cd_camera(t_game *game);

// --wall_edition.c
void		cd_edit_wall(t_game *game, float x, float y);
void		cd_inventory_switch(double xdelta, double ydelta, t_game *game);
void		cd_mouse_input(mouse_key_t button, action_t action,
	modifier_key_t mods, t_game *game);

// -----raycast----------------------------------------------------------------
// --raycast.c
void		cd_render(t_game *game);

// --draw_walls.c
void		cd_dim_color(t_game *game, int x, int y, float effect);
void		cd_draw_walls(t_game *game, t_ray_info *ray, int x);
void		cd_draw_c_f(t_game *game, int x);

// --draw_tiles.c
float		cd_get_p_rsqrt(t_game *game, float x2, float y2);
void		cd_draw_tiles(t_game *game, int x);

// --utils.c
mlx_image_t	*cd_slow_raycast(t_game *game, struct timeval start_time,
				int target_fps);
void		cd_modif_res(t_game *game, int moment, int force);

// --sprites.c
void		cd_sort_sprites(t_game *game);
void		cd_render_sprites(t_game * game);

// --sprite_list_utils.c
void		cd_add_sprite(t_game *game, float x, float y);
void		cd_remove_sprite(t_game *game, int target_i);

// -----minimap----------------------------------------------------------------
void		cd_minimap(t_game *game);
void		cd_put_texture(t_game *game, char *path, int x, int y);
void		cd_minimap_conditions(t_game *game, t_position *pos, int *i, int *ii);

// -----gui--------------------------------------------------------------------
// --gui_setup.c
void		cd_show_block_inventory(t_game *game);

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
// int			cd_is_floor_done(t_t_info *info);
// int			cd_check_game_status(t_t_info *info);
// void		cd_switch_floor_status(t_t_info *info);

#endif