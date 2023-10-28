/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:50 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 14:48:50 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_program(t_map *Map)
{
	mlx_destroy_window(Map->window.mlx_ptr, Map->window.win_ptr);
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

	mlx_put_image_to_window(Map->window.mlx_ptr,
		Map->window.win_ptr, Map->c_img, 0, 0);
	mlx_put_image_to_window(Map->window.mlx_ptr, Map->window.win_ptr,
		Map->f_img, 0, WINDOW_HEIGHT / 2);
	x = -1;
	while (++x < WINDOW_WIDTH)
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
		old_dir_x = M->player.dir_x;
		M->player.dir_x = M->player.dir_x * cos(rs) - M->player.dir_y * sin(rs);
		M->player.dir_y = old_dir_x * sin(rs) + M->player.dir_y * cos(rs);
		old_pl_x = M->player.cam_x;
		M->player.cam_x = M->player.cam_x * cos(rs) - M->player.cam_y * sin(rs);
		M->player.cam_y = old_pl_x * sin(rs) + M->player.cam_y * cos(rs);
		render_map(M);
	}
	return (0);
}

void	open_window(t_map *Map)
{
	Map->window.win_ptr = mlx_new_window(Map->window.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	mlx_hook(Map->window.win_ptr, 17, 0, close_program, Map);
}
