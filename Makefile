.PHONY: all clean fclean re

NAME = fdf
CC = gcc
FLAGS = -Wall -Werror -Wextra -O2 -O0 -g
LIBRARIES = -lmlx -lft -L$(LIBFT_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(MINILIBX_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

MINILIBX = $(MINILIBX_DIRECTORY)libmlx.a
MINILIBX_DIRECTORY = ./minilibx_macos/
MINILIBX_HEADERS = $(MINILIBX_DIRECTORY)

HEADERS_LIST = fdf.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = main.c \
 			utils.c \
 			stack.c \
 			drawing.c \
 			mouse.c \
 			read.c \
 			ctrls.c \
 			projection.c \
 			map.c \
 			color.c \
 			init.c \
 			utils2.c \
 			funcs_for_hooks.c \
 			rectangle.c \
 			menu.c \
 			color_schemes.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS
GREEN = \033[0;32m
BOLD_GREEN = \033[1;32m
RED = \033[0;31m
BOLD_RED = \033[1;31m
YELLOW = \033[0;33m
BOLD_YELLOW = \033[1;33m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m
MAGENTA = \033[0;35m
BOLD_MAGENTA = \033[1;35m
CYAN = \033[0;36m
BOLD_CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@echo "$(BOLD_BLUE)The last action.....$(RESET)"
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@echo "$(BOLD_MAGENTA)Creating object file $(BOLD_CYAN)$<$(RESET) $(BOLD_MAGENTA)in $(OBJECTS_DIRECTORY)$(RESET)"
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(BOLD_CYAN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(MINILIBX):
	@echo "$(BOLD_YELLOW)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(GREEN)object files $(BOLD_RED)deleted$(RESET)"
	@echo "$(GREEN)$(OBJECTS_DIRECTORY) $(BOLD_RED)deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(GREEN)$(MINILIBX) $(BOLD_RED)deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(GREEN)$(LIBFT) $(BOLD_RED)deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) $(BOLD_RED)deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all