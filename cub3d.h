#ifndef CUB3D_H
#define CUB3D_H
# include "mlx_linux/mlx.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# define WINDOW_WIDTH 10000
# define WINDOW_HEIGHT 10000
# define COIN "textures/chest_golden_open_full.xpm"
# define EXIT "textures/Floor_ladder.xpm"
# define PLAYER "textures/npc_paladin.xpm"
# define FLOOR "textures/Edge_single.xpm"
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define RIGHT_ARR
# define LEFT_ARR

typedef struct s_map{
    int     row_count;
    int     col_count;
    char    **map;
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    char    *F;
    char    *C;
} t_map;

int err(char *str);
int texture_check(t_map *Map);
#endif