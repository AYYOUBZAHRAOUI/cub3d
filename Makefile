# compiler and flags
CC = cc 
FLAGS = -Wall -Werror -Wextra # i need more flags for the minilibx

# folders
OBJ_DIR = obj
SRC_DIR = src
INCL_DIR = include
LIBFT_DIR = libft

# source files
SRC_FILES = $(wildcard $(SRC_DIR)/*c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

NAME = cub3d
LIBFT = $(LIBFT_DIR)/libft.a


# don't forget to check libft will ubdate when one file in libft change
# Target
all: $(LIBFT) $(NAME)

# Rule create libft
$(LIBFT): 
	@make -C $(LIBFT_DIR)
	@echo "libft.a created"

$(NAME): $(OBJ_FILES)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(INCL_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
