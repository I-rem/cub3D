#ifndef CUB3D_H
#define CUB3D_H
# include "mlx_linux/mlx.h"
# include "gnl/get_next_line.h"
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
# define WINDOW_HEIGHT 400
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
# define LEFT_ARR 65363
# define FLOOR "./pics/minimap/Floor.xpm"
# define WALL "./pics/minimap/Wall.xpm"
# define PLAYER "./pics/minimap/Player.xpm"

#define ROTATION_SPEED (M_PI / 180.0)
# define MOVE_SPEED 0.05

typedef struct s_window{
    void	*mlx_ptr;
    void	*win_ptr;
} t_window;

typedef struct s_minimap{
    void	*floor_img;
    void	*wall_img;
    void	*player_img;
} t_minimap;

typedef struct s_img{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int width;
    int height;
} t_img;

typedef struct s_ray{
    double  pos_x;
    double  dir_x;
    double  dir_y;
    int     map_x;
    int     map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_dist;
    int step_x;
    int step_y;
    int is_hit;
    int side;
} t_ray;

typedef struct s_player{
    double     pos_x;
    double     pos_y;
    double  dir_x;
    double  dir_y;
    double  cam_x;
    double  cam_y;
} t_player;

typedef struct s_map{
    int		row_count;
    int		col_count;
    
    char	**map;
    char	*NO;
    char	*SO;
    char	*WE;
    char	*EA;
    char	*F;
    char	*C;
    int		F_col;
    int		C_col;
    char    start_dir;
    t_window	Window;
    t_minimap	Minimap;
    void	*F_img;
    void	*C_img;
    t_img   Images[4];
    t_ray   Ray;
    t_player Player;
} t_map;

int	err(char *str);
int	texture_check(t_map *Map, int i);
int	file_check(char *filepath, int type);
void	open_window(t_map *Map);
int	render_map(t_map *Map);
int	handle_input(int keycode, t_map *Map);
int	handle_no_event(t_map *data);
void	open_window(t_map *Map);
void	img_delete(t_map *data);
void	img_init(t_map *data);
void	check_move(t_map *Map, int keycode);
int	find_color(char *str);

//void	raycasting(t_map *Map);
void cast_ray(t_map *Map, int x);
#endif

