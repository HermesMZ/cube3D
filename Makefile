NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_LIBS = -Lminilibx-linux -lmlx_Linux -lm
X_LIBS = -lXext -lX11

SRC_DIR = src
HOOKS_DIR = $(SRC_DIR)/hooks
KEYS_DIR = $(SRC_DIR)/keys
PARSING_DIR = $(SRC_DIR)/parsing
UTILS_DIR = $(SRC_DIR)/utils
RAYCASTION_DIR = $(SRC_DIR)/raycasting
MANDATORY_DIR = $(SRC_DIR)/mandatory
BONUS_DIR = $(SRC_DIR)/bonus

OBJ_DIR = obj

LIBFT_DIR = libft
LIBMLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(LIBMLX_DIR)/libmlx_Linux.a

INCLUDES_DIR = include
INCLUDES = -I $(INCLUDES_DIR) -I $(LIBFT_DIR)/includes -I $(LIBMLX_DIR)

HOOKS_SRC = \
	hooks.c \

KEYS_SRC = \
	actions.c \
	check_moves.c \
	handlers.c \
	moves.c \
	strafe.c \

PARSING_SRC = \
	check_file.c \
	check_map.c \
	file.c \
	map_utils.c \
	map.c \
	parsing.c \

UTILS_SRC = \
	clean_mlx.c \
	clean.c \
	debug.c \

RAYCASTION_SRC = \
	map_background.c \
	draw_column.c \
	init_ray.c \

MANDATORY_SRC = \
	init.c \
	main.c \
	player.c \
	raycasting.c \

BONUS_SRC = \
	init_bonus.c \
	main_bonus.c \
	mouse_bonus.c \
	raycasting_bonus.c \
	render_2D_bonus.c \
	player_bonus.c \



SRC_ALL = \
	$(addprefix $(MANDATORY_DIR)/, $(MANDATORY_SRC)) \
	$(addprefix $(HOOKS_DIR)/, $(HOOKS_SRC)) \
	$(addprefix $(KEYS_DIR)/, $(KEYS_SRC)) \
	$(addprefix $(PARSING_DIR)/, $(PARSING_SRC)) \
	$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
	$(addprefix $(RAYCASTION_DIR)/, $(RAYCASTION_SRC)) \
	
SRC_BONUS = \
	$(addprefix $(BONUS_DIR)/, $(BONUS_SRC)) \
	$(addprefix $(HOOKS_DIR)/, $(HOOKS_SRC)) \
	$(addprefix $(KEYS_DIR)/, $(KEYS_SRC)) \
	$(addprefix $(PARSING_DIR)/, $(PARSING_SRC)) \
	$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
	$(addprefix $(RAYCASTION_DIR)/, $(RAYCASTION_SRC)) \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC_ALL))
OBJS_BONUS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC_BONUS))

all: $(LIBFT) $(LIBMLX) $(NAME) $(INCLUDES_DIR)/cub3D.h

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX) $(INCLUDES_DIR)/cub3D.h
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(MLX_LIBS) $(X_LIBS) -no-pie -o $(NAME)
	@touch .mandatory
	@rm -f .bonus

bonus: .bonus

.bonus: $(LIBFT) $(LIBMLX) $(OBJS_BONUS) $(INCLUDES_DIR)/cub3D_bonus.h
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(LIBMLX) $(MLX_LIBS) $(X_LIBS) -no-pie -o $(NAME)
	@touch .bonus
	@rm -f .mandatory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Construction de libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	@echo "Construction de libmlx.a..."
	@$(MAKE) -C $(LIBMLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f .bonus .mandatory
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIBMLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re