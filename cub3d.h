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
# define WINDOW_WIDTH 400
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
# define FOV 120
# define PI 3.14159265359
# define ROTATION_SPEED 0.05
# define FLOOR "./pics/minimap/Floor.xpm"
# define WALL "./pics/minimap/Wall.xpm"
# define PLAYER "./pics/minimap/Player.xpm"
# define TILE_SIZE 64
typedef struct s_window{
    void	*mlx_ptr;
    void	*win_ptr;
} t_window;

typedef struct s_minimap{
    void	*floor_img;
    void	*wall_img;
    void	*player_img;
} t_minimap;

typedef struct s_map{
    int		row_count;
    int		col_count;
    int		p_pos_x;
    int		p_pos_y; // We will probably need to decrease this value before we can actually use it
    char	**map;
    char	*NO;
    char	*SO;
    char	*WE;
    char	*EA;
    char	*F;
    char	*C;
    int		F_col;
    int		C_col;
    t_window	Window;
    t_minimap	Minimap;
    void	*NO_img;
    void	*SO_img;
    void	*EA_img;
    void	*WE_img;
    void	*F_img;
    void	*C_img;
    double	player_angle; // initialize this according to the map file
} t_map;

int	err(char *str);
int	texture_check(t_map *Map, int i);
int	file_check(char *filepath, int type);
void	open_window(t_map *Map);
void	render_map(t_map *Map);
int	handle_input(int keycode, t_map *Map);
int	handle_no_event(t_map *data);
void	open_window(t_map *Map);
void	img_delete(t_map *data);
void	img_init(t_map *data);
void	check_move(t_map *Map, int keycode);
int	find_color(char *str);

//void	raycasting(t_map *Map);
double calculate_distance(double x1, double y1, double x2, double y2);
void cast_ray(t_map *Map, double player_x, double player_y, double ray_angle, double *hit_x, double *hit_y);
int calculate_wall_height(double distance);
void render_wall_column(t_map *Map, int column, int wall_height);
#endif

