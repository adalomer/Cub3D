NAME = Cub3d

SRCS = get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c \
	   libft/libft.c \
	   main.c \
	   cub3d.c \
	   init.c \
	   draw.c \
	   raycasting.c \
	   events.c \
	   utils.c \
	   gc.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx_linux 
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	make -C minilibx_linux clean
	rm -f $(OBJS)

fclean: clean
	make -C minilibx_linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re