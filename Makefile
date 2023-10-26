# Makefile for cub3D

NAME := cub3D
CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
SRCS := gnl/get_next_line_utils.c gnl/get_next_line.c main.c map_check.c img_utils.c windows_hooks.c color.c ray.c map_utils.c color_utils.c
OBJS := $(SRCS:.c=.o)
RM := rm -f
UNAME := $(shell uname)

# Directory where libft.a is located
LIBFT_DIR := libft

# Name of the libft library
LIBFT := $(LIBFT_DIR)/libft.a

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS} $(LIBFT)
    @echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
    @ $(MAKE) -C mlx all >/dev/null 2>&1
    @ cp ./mlx/libmlx.a .
    $(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -L$(LIBFT_DIR) -lft -lm -framework OpenGL -framework AppKit
    @echo "$(GREEN)$(NAME) created[0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS} $(LIBFT)
		@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
		@chmod 777 mlx_linux/configure
		@ $(MAKE) -C mlx_linux all
		$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -L$(LIBFT_DIR) -lft
		@echo "$(GREEN)$(NAME) created[0m ✔️"
endif

all: ${NAME} cub3d.h

ifeq ($(UNAME), Darwin)
clean:
    @ $(RM) *.o */*.o */*/*.o
    @ rm -rf $(NAME).dSYM >/dev/null 2>&1
    @ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
clean:
		@ $(RM) *.o */*.o */*/*.o
		@ rm -rf $(NAME).dSYM >/dev/null 2>&1
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif

ifeq ($(UNAME), Linux)
fclean: clean
		@ $(RM) ${NAME}
		@ $(MAKE) -C mlx_linux clean
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Darwin)
fclean: clean
    @ $(RM) ${NAME}
    @ rm libmlx.a
    @ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

re: fclean all

.PHONY: all clean fclean re
