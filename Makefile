
SRCS := main.c map_check.c img_utils.c windows_hooks.c color.c ray.c map_utils.c color_utils.c render_utils.c
OBJS = $(SRCS:.c=.o)
CC = gcc
MFLAGS = ./mlx/libmlx.a
LFLAGS = ./libft/libft.a
AFLAGS =  -Wall -Wextra -Werror -I./mlx -I./libft
RM = rm -rf
NAME = cub3D

all :$(MFLAGS) $(LFLAGS) $(NAME)

$(MFLAGS):
	make -C ./mlx

$(LFLAGS):
	make -C ./libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MFLAGS) $(LFLAGS) $(AFLAGS) -framework OpenGL -framework AppKit -o $(NAME)

fclean : clean
	make fclean -C ./libft
	$(RM) $(NAME)

clean :
	make clean -C ./mlx
	make clean -C ./libft
	$(RM) ./*.o ./gnl/*.o

re : fclean all

.PHONY : all fclean clean re
