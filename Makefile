

# Cub3D Project Makefile

# Name of the executable
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g
MLX_FLAGS = -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib"

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
MLX_DIR = ~/MLX42
# you need to fix this path

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/parsing/*.c)
SRCS += $(wildcard $(SRC_DIR)/rays_casting/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Include paths
INCLUDES =  -I$(INC_DIR)  -I$(LIBFT_DIR)/include -I/Users/$(USER)/MLX42/include/MLX42

# Rules
all: $(NAME)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/rays_casting

# Compile MinilibX
$(MLX_DIR)/build/libmlx42.a:
	@echo "Compiling MinilibX..."
	@$(MAKE) -C $(MLX_DIR)

# Compile libft
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the executable
$(NAME): $(OBJS) $(MLX_DIR)/build/libmlx42.a $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_DIR)/build/libmlx42.a $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

# 	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLXHEADERS)  $(OBJ_FILES) $(LIBFT) $(MLX) -o $(NAME)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
# 	i don't recommend cleaning MinilibX
	@echo "Object files cleaned!$(MAKE)"
# ----- don't forget to check this $(MAKE) -----

# Clean all generated files
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Executable cleaned!"

# Rebuild the project
re: fclean all

# Run the program
run: all
	./$(NAME) maps/default.cub

# Debug with valgrind (memory leak check)
debug: CFLAGS += -g
debug: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/default.cub

.PHONY: all clean fclean re run debug
