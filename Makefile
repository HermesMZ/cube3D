NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_LIBS = -Lminilibx-linux -lmlx_Linux -lm
X_LIBS = -lXext -lX11

SRC_DIR = src
OBJ_DIR = obj

LIBFT_DIR = libft
LIBMLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(LIBMLX_DIR)/libmlx_Linux.a

INCLUDES_DIR = include
INCLUDES = -I $(INCLUDES_DIR) -I $(LIBFT_DIR)/includes -I $(LIBMLX_DIR)

SRC = \
	main.c \

SRC_ALL = \
	$(addprefix $(SRC_DIR)/, $(SRC)) \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC_ALL))

all: $(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX) $(MLX_LIBS) $(X_LIBS) -no-pie -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Construction de libft.a..."
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX):
	@echo "Construction de libmlx.a..."
	@git clone git@github.com:42paris/minilibx-linux.git
	@$(MAKE) -C $(LIBMLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re