NAME		= cub3D

# Directories
SRC_DIR		= src
INC_DIR		= inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Source files (just filenames, paths added automatically)
MAIN_SRC	= main.c cub_init.c mlx_init.c player_init.c direction.c cleanup.c \
		  door_init.c door_manage.c

MOVEMENT_SRC	= movement.c rotate.c keyhook.c

RENDERING_SRC	= dda.c draw.c texture.c render.c helpers.c \
		  door_render.c door_utils.c door_draw.c

PARSING_SRC	= main_parsing.c config_parsing_validation.c map_parsing.c \
		  map_floodfill.c map_validation_loops.c parsing_helpers.c \
		  parsing_utils.c validation_helpers.c file_reading.c position_lst.c

MINIMAP_SRC = minimap.c draw_minimap.c minimap_border.c minimap_direction.c \
			minimap_player.c minimap_utils.c 
# Create full paths for source files
MAIN_SRCS	= $(addprefix $(SRC_DIR)/main/, $(MAIN_SRC))
MOVEMENT_SRCS	= $(addprefix $(SRC_DIR)/movement/, $(MOVEMENT_SRC))
RENDERING_SRCS	= $(addprefix $(SRC_DIR)/rendering/, $(RENDERING_SRC))
PARSING_SRCS	= $(addprefix $(SRC_DIR)/parsing/, $(PARSING_SRC))
MINIMAP_SRCS	= $(addprefix $(SRC_DIR)/minimap/, $(MINIMAP_SRC))

SRCS		= $(MAIN_SRCS) $(MOVEMENT_SRCS) $(RENDERING_SRCS) $(PARSING_SRCS) $(MINIMAP_SRCS)

# Libft source files
LIBFT_SRC	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
		  ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
		  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		  ft_strcmp.c ft_atoll.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		  ft_lstiter.c ft_lstmap.c get_next_line.c

LIBFT_SRCS	= $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRC))

# Object files
OBJS		= $(SRCS:.c=.o)
LIBFT_OBJS	= $(LIBFT_SRCS:.c=.o)

# Compiler and flags
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors for output
GREEN		= \033[0;32m
BLUE		= \033[0;34m
RESET		= \033[0m

# Rules
all: $(MLX_DIR)/libmlx.a $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(BLUE)Compiling cub3D...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ cub3D compiled successfully!$(RESET)"

$(MLX_DIR)/libmlx.a:
	@make -C $(MLX_DIR) > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(LIBFT_OBJS)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(GREEN)✓ Clean completed!$(RESET)"

fclean: clean
	@echo "$(BLUE)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re