NAME        = miniRT
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
INCLUDES    = -I include -I $(MLX_DIR)
LIBS        = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRC_DIR     = src
OBJ_DIR     = obj

# Source Files
SRC_CORE    = $(SRC_DIR)/core/main.c \
              $(SRC_DIR)/core/utils.c \
              $(SRC_DIR)/core/mlx_utils.c

SRC_MATH    = $(SRC_DIR)/math/vec_utils.c

SRC_PARSER  = $(SRC_DIR)/parser/tokenizer.c \
              $(SRC_DIR)/parser/parser.c

SRC_RENDER  = $(SRC_DIR)/render/intersection.c \
              $(SRC_DIR)/render/shading.c \
              $(SRC_DIR)/render/camera.c \
              $(SRC_DIR)/render/render_scene.c

SRCS        = $(SRC_CORE) $(SRC_MATH) $(SRC_PARSER) $(SRC_RENDER)
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Rules
all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(MLX_LIB)
	@echo "Linking $(NAME)..."
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(MLX_LIB):
	@echo "Building MiniLibX..."
	@make -C $(MLX_DIR)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning executeable..."
	rm -f $(NAME)
	# Also remove test binaries if any
	rm -f test_math test_parser

re: fclean all

.PHONY: all clean fclean re
