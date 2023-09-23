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
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
//# define ESC 53
//# define W 13
//# define A 0
//# define S 1
//# define D 2
//# define RIGHT_ARR
//# define LEFT_ARR

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define RIGHT_ARR 65361
# define LEFT_ARR 65307
#define FLOOR "./pics/minimap/Floor.xpm"
#define WALL "./pics/minimap/Wall.xpm"
#define PLAYER "./pics/minimap/Player.xpm"

typedef struct s_window{
    void    *mlx_ptr;
    void    *win_ptr;
} t_window;

typedef struct s_minimap{
    void    *floor_img;
    void    *wall_img;
    void    *player_img;
} t_minimap;

typedef struct s_map{
    int     row_count;
    int     col_count;
    int     start_pos_x;
    int     start_pos_y; // We will probably need to decrease this value before we can actually use it
    char    **map;
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    char    *F;
    char    *C;
    t_window Window;
    t_minimap Minimap;
    void    *NO_img;
    void    *SO_img;
    void    *EA_img;
    void    *WE_img;
} t_map;

int	err(char *str);
int	texture_check(t_map *Map, int i);
int	file_check(char *filepath, int type);
void	open_window(t_map *Map);
void    render_map(t_map *Map);
int	handle_input(int keycode, t_map *Map);
int	handle_no_event(t_map *data);
void	open_window(t_map *Map);
void	img_delete(t_map *data);
void	img_init(t_map *data);
void	check_move(t_map *Map, int keycode);
#endif
