/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:05:53 by ikayacio          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:14 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_map *Map, int x, int y)
{
	(void)Map;
	(void)x;
	(void)y;
	Map->start_pos_x = x;
	Map->start_pos_y = y;
	render_map(Map);
}

void	img_init(t_map *data)
{
	int	w;
	int	h;

	w = 64;
	h = 64;

	data->NO_img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->NO, &w, &h);
	data->SO_img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->SO, &w, &h);
	data->EA_img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->WE, &w, &h);
	data->WE_img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->EA, &w, &h);
	render_map(data);
	mlx_key_hook(data->Window.win_ptr, &handle_input, data);
	mlx_loop_hook(data->Window.mlx_ptr, &handle_no_event, data);
	mlx_loop(data->Window.mlx_ptr);
}

void	img_delete(t_map *data)
{
	mlx_destroy_image(data->Window.mlx_ptr, data->NO_img);
	mlx_destroy_image(data->Window.mlx_ptr, data->SO_img);
	mlx_destroy_image(data->Window.mlx_ptr, data->EA_img);
	mlx_destroy_image(data->Window.mlx_ptr, data->WE_img);
}

void	check_move(t_map *Map, int keycode) // This kind of movement is probably too discrete for this project, need to figure more continous functions
{
	int	x;
	int	y;

	x = Map->start_pos_x;
	y = Map->start_pos_y;
	if (keycode == W && Map->map[y - 1][x] != '1')
		move(Map, x, y - 1);
	if (keycode == S && Map->map[y + 1][x] != '1')
		move(Map, x, y + 1);
	if (keycode == A && Map->map[y][x - 1] != '1')
		move(Map, x - 1, y);
	if (keycode == D && Map->map[y][x + 1] != '1')
		move(Map, x + 1, y);
}
