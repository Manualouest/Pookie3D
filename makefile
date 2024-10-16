# valgrind --suppressions=ms.supp --leak-check=full --show-leak-kinds=all ./minishell

NAME = cub3D

B_NAME = pookie3d

CFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -Iincludes/ -I$(LIBMLX)/include
LIBFT = includes/libft/libft.a

# MLX
LIBMLX = ./MLX42
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Mandatory
SRC_DIR = src/
SRC_NAME = main.c\
			error.c\
			img_to_int.c

SRC_NAME += parsing/parser.c\
			parsing/check.c\
			parsing/map_handler.c

SRC_NAME += utils/tab_utils.c\
			utils/string_utils.c\
			utils/math.c

SRC_NAME += init/init_game.c\
			init/init_game_part.c

SRC_NAME += keys/keys.c\
			keys/keys_part.c

SRC_NAME += raycasting/raycast.c\
			raycasting/draw_walls.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJ_DIR = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))

# Bonus

B_SRC_DIR = bonus/src/

B_SRC_NAME = main.c\
			error.c\
			controllers.c\
			img_to_int.c\
			minimap.c

B_SRC_NAME += parsing/parser.c\
			parsing/check.c\
			parsing/map_handler.c

B_SRC_NAME += animactions/mooves.c

B_SRC_NAME += map_maker/map_maker_main.c\
			map_maker/input_handler.c\
			map_maker/map_editor.c\
			map_maker/vars_setup.c\
			map_maker/map_setup.c\
			map_maker/utils.c\
			map_maker/img_utils.c\
			map_maker/setup_screens.c\
			map_maker/rand_gen.c

B_SRC_NAME += utils/tab_utils.c\
			utils/string_utils.c\
			utils/math.c

B_SRC_NAME += init/init_game.c\
			init/init_game_part.c

B_SRC_NAME += keys/keys.c\
			keys/keys_part.c

B_SRC_NAME += raycasting/raycast.c\
			raycasting/draw_walls.c

B_SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))


B_OBJ_DIR = b_obj/
B_OBJ_NAME = $(B_SRC_NAME:.c=.o)
B_OBJ = $(patsubst %, $(B_OBJ_DIR)%, $(B_OBJ_NAME))


# Compilation

all: MLX $(NAME)

MLX :
	@if ls | grep -q "MLX42"; then \
		clear; \
		echo "\033[32;47;1m** MLX42 already exist **\033[1;m"; \
	else \
		git clone https://github.com/codam-coding-college/MLX42.git; \
		cmake ./MLX42 -B ./MLX42/build; \
		make -C ./MLX42/build --no-print-directory -j4; \
		make --directory ./MLX42/build; \
	fi

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) $< $(INCLUDES) -c -o $@

$(B_OBJ_DIR)%.o:$(B_SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) $< $(INCLUDES) -c -o $@

$(LIBFT) :
	@ $(MAKE) -C includes/libft all --no-print-directory

$(NAME): MLX $(LIBFT) $(OBJ)
	@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBFT) $(LIBS)
	@echo "\033[32;47;1m** FINISH **\033[1;m"

bonus: MLX  $(LIBFT) $(B_OBJ)
	@gcc -o $(B_NAME) $(CFLAGS) $(B_OBJ) $(INCLUDES) $(LIBFT) $(LIBS)
	@echo "\033[32;47;1m** FINISH BONUS **\033[1;m"

clean:
	@ $(MAKE) -C includes/libft clean --no-print-directory
	rm -rf $(OBJ_DIR) $(B_OBJ_DIR)

fclean: clean
	@ $(MAKE) -C includes/libft fclean --no-print-directory
	rm -f $(NAME) $(B_NAME)

re: fclean all

end: 
	rm -rf MLX42

bruh: fclean bonus
