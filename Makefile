NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -Iget_next_line

SRCS =  fdf.c hooks.c parcing_map.c put_line.c utils.c get_next_line/get_next_line.c\
get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

HEADERS = fdf.h get_next_line/get_next_line.h libft/libft.h

all: $(LIBFT) mlx $(NAME)

mlx:
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT_FLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re mlx
