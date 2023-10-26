#include "cub3d.h"

int	close_program(t_map *Map)
{
	mlx_destroy_window(Map->Window.mlx_ptr, Map->Window.win_ptr);
	free_map(Map);
	exit(EXIT_SUCCESS);
}

int	handle_no_event(t_map *data)
{
	(void)data;
	return (0);
}

int	render_map(t_map *Map)
{
	int	x;

	mlx_put_image_to_window(Map->Window.mlx_ptr,
							Map->Window.win_ptr, Map->C_img, 0, 0);
	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
							Map->F_img, 0, WINDOW_HEIGHT / 2);
	x = -1;
	while(++x < WINDOW_WIDTH)
		cast_ray(Map, x);	
	return (0);
}

int	handle_input(int keycode, t_map *M)
{
	double	rs;
	double	old_dir_x;
	double	old_pl_x;

	if (keycode == ESC)
		close_program(M);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
	        check_move(M, keycode);
	else if (keycode == RIGHT_ARR || keycode == LEFT_ARR)
    {
		rs = ROTATION_SPEED;
		if (keycode == RIGHT_ARR)
			rs = -ROTATION_SPEED;
		if (M->start_dir == 'W')
			rs *= -1;
		old_dir_x = M->Player.dir_x;
		M->Player.dir_x = M->Player.dir_x * cos(rs) - M->Player.dir_y * sin(rs);
		M->Player.dir_y = old_dir_x * sin(rs) + M->Player.dir_y * cos(rs);
		old_pl_x = M->Player.cam_x;
		M->Player.cam_x = M->Player.cam_x * cos(rs) - M->Player.cam_y * sin(rs);
		M->Player.cam_y = old_pl_x * sin(rs) + M->Player.cam_y * cos(rs);
		render_map(M);
	}
    return (0);
}

void	open_window(t_map *Map)
{
	Map->Window.win_ptr = mlx_new_window(Map->Window.mlx_ptr,
							WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	mlx_hook(Map->Window.win_ptr, 17, 0, close_program, Map);
}

