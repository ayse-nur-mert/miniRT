NAME    := miniRT

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I. -I./parser -I./minilibx-linux

MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
LDFLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

OBJ_DIR := obj

SRCS    := \
    main.c \
    render_scene.c \
    render_color.c \
    render_mlx.c \
    render_lighting.c \
    render_intersections.c \
    vector_intersection.c \
    intersect_cylinder.c \
    intersect_plane.c \
    intersect_sphere.c \
    intersect_utils.c \
    vector_math1.c \
    vector_math2.c \
    vector_math3.c \
    vector_math4.c \
    scene.c \
    scene_cleanup.c \
    parser/get_next_line.c \
    parser/get_next_line_utils.c \
    parser/get_next_line_utils2.c \
    parser/parse_file.c \
    parser/validate_file_content.c \
    parser/parse_line_object.c \
    parser/parse_line_light.c \
    parser/parse_line_camera_ambient.c \
    parser/parse_utils.c \
    parser/parse_utils2.c \
	parser/parse_split_ws.c \
	parser/vec3_checks.c \
	parser/ft_convert.c

OBJS    := $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "miniRT compiled successfully."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

clean:
	@rm -rf $(OBJ_DIR)
	@-$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re