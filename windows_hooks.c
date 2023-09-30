#include "cub3d.h"

int	close_program(t_map *Map)
{
	int	i;

	mlx_destroy_window(Map->Window.mlx_ptr, Map->Window.win_ptr);
	img_delete(Map);
	i = 0;
	while (Map->map[i] != NULL)
	{
		free(Map->map[i]);
		Map->map[i] = NULL;
		i++;
	}
	free(Map->Window.mlx_ptr);
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

	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr, Map->C_img, 0, 0);
	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr, Map->F_img, 0, WINDOW_HEIGHT / 2);
	x = -1;
	while(++x < WINDOW_WIDTH)
		cast_ray(Map, x);	
	return 0;
}

int handle_input(int keycode, t_map *Map)
{
	double	rotation_speed;
	double	old_dir_x;
	double old_plane_x;

	if (keycode == ESC)
		close_program(Map);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
	        check_move(Map, keycode);
	else if (keycode == RIGHT_ARR || keycode == LEFT_ARR)
    	{
		if (keycode == RIGHT_ARR)
			rotation_speed = -ROTATION_SPEED;
		else if (keycode == LEFT_ARR)
			rotation_speed = ROTATION_SPEED;
		if (Map->start_dir == 'W')
			rotation_speed *= -1;
		old_dir_x = Map->Player.dir_x;
		Map->Player.dir_x = Map->Player.dir_x * cos(rotation_speed) - Map->Player.dir_y * sin(rotation_speed);
		Map->Player.dir_y = old_dir_x * sin(rotation_speed) + Map->Player.dir_y * cos(rotation_speed);
		old_plane_x = Map->Player.cam_x;
		Map->Player.cam_x = Map->Player.cam_x * cos(rotation_speed) - Map->Player.cam_y * sin(rotation_speed);
		Map->Player.cam_y = old_plane_x * sin(rotation_speed) + Map->Player.cam_y * cos(rotation_speed);
		render_map(Map);
	}
    return (0);
}

void	open_window(t_map *Map)
{

    Map->Window.win_ptr = mlx_new_window(Map->Window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	mlx_hook(Map->Window.win_ptr, 17, 0, close_program, Map);
	//mlx_loop_hook(Map->Window.mlx_ptr, (int (*)(void *))render_map, Map);
}

