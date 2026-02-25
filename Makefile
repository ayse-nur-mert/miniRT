NAME	:= miniRT

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -I. -I./parser -I./minilibx-linux

MLX_DIR	:= minilibx-linux
MLX_LIB	:= $(MLX_DIR)/libmlx.a
LDFLAGS	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRCS	:= \
	main.c \
	render_scene.c \
	vector_intersection.c \
	intersections.c \
	vector_math1.c \
	vector_math2.c \
	vector_math3.c \
	vector_math4.c \
	scene.c \
	parser/get_next_line.c \
	parser/get_next_line_utils.c \
	parser/parse_file.c \
	parser/validate_file_content.c \
	parser/parse_line_object.c \
	parser/parse_line_light.c \
	parser/parse_line_camera_ambient.c \
	parser/parse_utils.c \
	parser/parse_utils2.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)



$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
