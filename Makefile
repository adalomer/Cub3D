NAME = Cub3d

SRCS = libs/get_next_line/get_next_line.c \
	   libs/get_next_line/get_next_line_utils.c \
	   libs/libft/libft.c \
	   parser/parser.c \
	   parser/parser_utils.c \
	   parser/map_checker.c \
	   main.c \
	   core/cub3d.c \
	   init.c \
	   core/draw.c \
	   raycasting.c \
	   core/events.c \
	   core/utils.c \
	   gc/gc.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C libs/minilibx-linux 
	$(CC) $(CFLAGS) $(OBJS) -Llibs/minilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iheaders -Ilibs/minilibx-linux -c $< -o $@

clean:
	make -C libs/minilibx-linux clean
	rm -f $(OBJS)

fclean: clean
	make -C libs/minilibx-linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re