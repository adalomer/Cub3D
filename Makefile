NAME = Cub3d

LIBFT = libs/libft/libft.a
LIBFT_DIR = libs/libft

SRCS = libs/get_next_line/get_next_line.c \
	   libs/get_next_line/get_next_line_utils.c \
	   parser/parser.c \
	   parser/parser_utils.c \
	   parser/parser_identifier.c \
	   parser/parser_map_utils.c \
	   parser/map_checker.c \
	   main.c \
	   file_utils.c \
	   core/cub3d.c \
	   init.c \
	   core/draw.c \
	   core/draw2.c \
	   core/draw3.c \
	   raycasting/raycasting.c \
	   raycasting/raycasting_utils.c \
	   raycasting/raycasting_dda.c \
	   core/events.c \
	   core/utils.c \
	   core/utils2.c \
	   core/texture_loader.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = libs/minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "✅ Cub3D compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -Iheaders -I$(MLX_DIR) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -f $(OBJS)
	@echo "🧹 Object files cleaned"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "🗑️  All files cleaned"

re: fclean all

.PHONY: all clean fclean re

.PHONY: all clean fclean re