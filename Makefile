NAME		= cub3D

# Directories
SRC_DIR		= src
INC_DIR		= inc
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

# Source files organized by category
MAIN_SRC	= $(SRC_DIR)/main/main.c \
		  $(SRC_DIR)/main/cub_init.c \
		  $(SRC_DIR)/main/mlx_init.c \
		  $(SRC_DIR)/main/player_init.c \
		  $(SRC_DIR)/main/direction.c \
		  $(SRC_DIR)/main/cleanup.c

MOVEMENT_SRC	= $(SRC_DIR)/movement/movement.c \
		  $(SRC_DIR)/movement/rotate.c \
		  $(SRC_DIR)/movement/keyhook.c

RENDERING_SRC	= $(SRC_DIR)/rendering/dda.c \
		  $(SRC_DIR)/rendering/draw.c \
		  $(SRC_DIR)/rendering/texture.c \
		  $(SRC_DIR)/rendering/render.c \
		  $(SRC_DIR)/rendering/helpers.c

PARSING_SRC	= $(SRC_DIR)/parsing/main_parsing.c \
		  $(SRC_DIR)/parsing/config_parsing_validation.c \
		  $(SRC_DIR)/parsing/map_parsing.c \
		  $(SRC_DIR)/parsing/map_validation_loops.c \
		  $(SRC_DIR)/parsing/parsing_helpers.c \
		  $(SRC_DIR)/parsing/parsing_utils.c \
		  $(SRC_DIR)/parsing/validation_helpers.c \
		  $(SRC_DIR)/parsing/file_reading.c

SRCS		= $(MAIN_SRC) $(MOVEMENT_SRC) $(RENDERING_SRC) $(PARSING_SRC)

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
		  $(LIBFT_DIR)/ft_tolower.c $(LIBFT_DIR)/ft_toupper.c \
		  $(LIBFT_DIR)/ft_strcmp.c $(LIBFT_DIR)/ft_atoll.c \
		  $(LIBFT_DIR)/ft_lstnew.c $(LIBFT_DIR)/ft_lstadd_front.c \
		  $(LIBFT_DIR)/ft_lstsize.c $(LIBFT_DIR)/ft_lstlast.c \
		  $(LIBFT_DIR)/ft_lstadd_back.c $(LIBFT_DIR)/ft_lstdelone.c \
		  $(LIBFT_DIR)/ft_lstclear.c $(LIBFT_DIR)/ft_lstiter.c \
		  $(LIBFT_DIR)/ft_lstmap.c $(LIBFT_DIR)/get_next_line.c \

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
YELLOW		= \033[0;33m
RESET		= \033[0m

# Rules
all: $(MLX_DIR)/libmlx.a $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)Building MiniLibX...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(LIBFT_OBJS)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Cleaning everything...$(RESET)"
	@rm -f $(NAME)

re: fclean all

# Debugging rules
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: re

# Test with the sample map
test: $(NAME)
	@echo "$(GREEN)Running test with sample map...$(RESET)"
	@./$(NAME) test.cub

# Create sample textures (simple colored XPM files)
textures:
	@echo "$(YELLOW)Creating sample textures...$(RESET)"
	@mkdir -p textures
	@echo '/* XPM */\nstatic char *north[] = {\n"64 64 2 1",\n". c #FF0000",\n"# c #800000",\n' > textures/north.xpm
	@for i in {1..64}; do echo -n '"' >> textures/north.xpm; for j in {1..64}; do if [ $$(($$i % 8)) -lt 4 ] && [ $$(($$j % 8)) -lt 4 ]; then echo -n '#'; else echo -n '.'; fi; done >> textures/north.xpm; echo '",' >> textures/north.xpm; done
	@echo '};' >> textures/north.xpm
	@cp textures/north.xpm textures/south.xpm && sed -i 's/FF0000/00FF00/g; s/800000/008000/g' textures/south.xpm
	@cp textures/north.xpm textures/east.xpm && sed -i 's/FF0000/0000FF/g; s/800000/000080/g' textures/east.xpm
	@cp textures/north.xpm textures/west.xpm && sed -i 's/FF0000/FFFF00/g; s/800000/808000/g' textures/west.xpm

# Create sample map
map:
	@echo "$(YELLOW)Creating sample map...$(RESET)"
	@echo 'NO ./textures/north.xpm' > test.cub
	@echo 'SO ./textures/south.xpm' >> test.cub
	@echo 'WE ./textures/west.xpm' >> test.cub
	@echo 'EA ./textures/east.xpm' >> test.cub
	@echo 'F 220,100,0' >> test.cub
	@echo 'C 135,206,235' >> test.cub
	@echo '' >> test.cub
	@echo '111111111111111111111111' >> test.cub
	@echo '100000000011000000000001' >> test.cub
	@echo '101100000111000000000001' >> test.cub
	@echo '100100000000000000000001' >> test.cub
	@echo '111111111011000001110000000000001' >> test.cub
	@echo '100000000011000001110111111111111' >> test.cub
	@echo '11110111111111011100000010001' >> test.cub
	@echo '11110111111111011101010010001' >> test.cub
	@echo '11000000110101011100000010001' >> test.cub
	@echo '10000000000000001100000010001' >> test.cub
	@echo '10000000000000001101010010001' >> test.cub
	@echo '11000001110101011111011110N0111' >> test.cub
	@echo '11110111 1110101 101111010001' >> test.cub
	@echo '11111111 1111111 111111111111' >> test.cub

# Setup everything for testing
setup: textures map
	@echo "$(GREEN)Setup complete! Run 'make test' to test the game.$(RESET)"

# Help
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  all      - Build the project"
	@echo "  clean    - Remove object files"
	@echo "  fclean   - Remove all generated files"
	@echo "  re       - Rebuild everything"
	@echo "  debug    - Build with debugging flags"
	@echo "  test     - Run the program with test.cub"
	@echo "  textures - Create sample XPM texture files"
	@echo "  map      - Create sample test.cub map file"
	@echo "  setup    - Create textures and map files"
	@echo "  help     - Show this help"

.PHONY: all clean fclean re debug test textures map setup help