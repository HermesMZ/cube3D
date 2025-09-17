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

OBJ_DIR = obj

LIBFT_DIR = libft
LIBMLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(LIBMLX_DIR)/libmlx_Linux.a

INCLUDES_DIR = include
INCLUDES = -I $(INCLUDES_DIR) -I $(LIBFT_DIR)/includes -I $(LIBMLX_DIR)

SRC = \
	main.c \

HOOKS_SRC = \
	hooks.c \

KEYS_SRC = \
	actions.c \
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
	player.c \

UTILS_SRC = \
	clean.c \
	debug.c \
	init.c \


SRC_ALL = \
	$(addprefix $(SRC_DIR)/, $(SRC)) \
	$(addprefix $(HOOKS_DIR)/, $(HOOKS_SRC)) \
	$(addprefix $(KEYS_DIR)/, $(KEYS_SRC)) \
	$(addprefix $(PARSING_DIR)/, $(PARSING_SRC)) \
	$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC_ALL))

all: $(LIBFT) $(LIBMLX) $(NAME) $(INCLUDES_DIR)/cub3D.h

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(MLX_LIBS) $(X_LIBS) -no-pie -o $(NAME)

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
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LIBMLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re