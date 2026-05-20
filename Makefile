NAME = comp 
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INC_DIR = inc

SRC = $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC = -I$(INC_DIR)

SANITIZE = -g -fsanitize=address

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic $(INC)

# Colors for messages
GREEN  = \033[0;32m
RED    = \033[0;91m
RESET  = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -L$(LIB_DIR)
	@echo "$(GREEN)Executable $(NAME) was successfully created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files were deleted.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable file was deleted.$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
