NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I$(INCLUDES)

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES = inc/

SRC_NAME =	main.c \
			init.c \
			spaghetti.c \
			forking.c \
			output.c \
			parsing.c \
			utils.c \
			monitor.c \
			cleanup.c

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))

all: $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;36m Compiled" $(*F) "\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32m Executable" $(NAME) "created\033[0;39m"

clean:
	@rm -rf $(OBJ_DIR) $(LIBFTA)
	@echo "\033[1;31m Deleted all object files\033[0;39m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31m Deleted $(NAME)\033[0;39m"

re: fclean all

.PHONY: re all fclean clean
