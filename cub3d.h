/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:02 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 17:27:30 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 400

/*
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define RIGHT_ARR 124
# define LEFT_ARR 123
*/

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define RIGHT_ARR 65361
# define LEFT_ARR 65363

# define ROTATION_SPEED 0.01744
# define MOVE_SPEED 0.1

typedef struct s_window{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_window;

typedef struct s_img{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_ray{
	double	pos_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_dist;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	cam_x;
	double	cam_y;
}	t_player;

typedef struct s_map{
	int			row_count;
	int			col_count;
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	int			f_col;
	int			c_col;
	char		start_dir;
	t_window	window;
	void		*f_img;
	void		*c_img;
	t_img		images[4];
	t_ray		ray;
	t_player	player;
	int			id;
}	t_map;

int		err(char *str, t_map *Map);
int		texture_check(t_map *Map, int i);
int		file_check(char *filepath, int type);
void	open_window(t_map *Map);
int		render_map(t_map *Map);
int		handle_input(int keycode, t_map *Map);
int		handle_no_event(t_map *data);
void	open_window(t_map *Map);
void	img_delete(t_map *data);
void	img_init(t_map *data, int i);
void	check_move(t_map *Map, int keycode);
int		find_color(char *str, int i);
void	cast_ray(t_map *Map, int x);
void	free_map(t_map *Map);
void	init_null(t_map *Map);
int		line_check(char *map);
int		color_check(char *color, t_map *Map);
void	map_size(char *map, t_map *Map, int i);
char	*find_binary(int decimal);
int		find_decimal(char *binary);
void	new_map(t_map *Map);
int		is_bad(char c);
int		line_check2(char *map, int count, int i);
#endif
