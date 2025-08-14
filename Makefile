
NAME		= cub3D

# Directories
SRC_DIR		= src
INC_DIR		= inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Source files
MAIN_SRC	= $(SRC_DIR)/main/main.c
MOVEMENT_SRC	= $(SRC_DIR)/movement/movement.c \
			  $(SRC_DIR)/movement/rotate.c \
			  $(SRC_DIR)/movement/keyhook.c
RENDERING_SRC	= $(SRC_DIR)/rendering/dda.c \
			  $(SRC_DIR)/rendering/draw.c \
			  $(SRC_DIR)/rendering/texture.c \
			  $(SRC_DIR)/rendering/render.c \
			  $(SRC_DIR)/rendering/helpers.c

SRCS		= $(MAIN_SRC) $(MOVEMENT_SRC) $(RENDERING_SRC)

# Libft source files (compile directly)
LIBFT_SRCS	= $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_bzero.c \
		  $(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_isalnum.c \
		  $(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_isascii.c \
		  $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_isprint.c \
		  $(LIBFT_DIR)/ft_itoa.c $(LIBFT_DIR)/ft_memchr.c \
		  $(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_memcpy.c \
		  $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_memset.c \
		  $(LIBFT_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/ft_putendl_fd.c \
		  $(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/ft_putstr_fd.c \
		  $(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_strchr.c \
		  $(LIBFT_DIR)/ft_strdup.c $(LIBFT_DIR)/ft_striteri.c \
		  $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strlcat.c \
		  $(LIBFT_DIR)/ft_strlcpy.c $(LIBFT_DIR)/ft_strlen.c \
		  $(LIBFT_DIR)/ft_strmapi.c $(LIBFT_DIR)/ft_strncmp.c \
		  $(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_strrchr.c \
		  $(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_substr.c \
		  $(LIBFT_DIR)/ft_tolower.c $(LIBFT_DIR)/ft_toupper.c

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
RED		= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

# Rules
all: $(MLX_DIR)/libmlx.a $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)Building MiniLibX...$(RESET)"
	@make -C $(MLX_DIR)

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(LIBFT_OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning everything...$(RESET)"
	@rm -f $(NAME)

re: fclean all

# Debugging rules
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: re

# Test with a simple map
test: $(NAME)
	@echo "$(GREEN)Running test...$(RESET)"
	@./$(NAME)

# Help
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  all     - Build the project"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove all generated files"
	@echo "  re      - Rebuild everything"
	@echo "  debug   - Build with debugging flags"
	@echo "  test    - Run the program"
	@echo "  help    - Show this help"

.PHONY: all clean fclean re debug test help
