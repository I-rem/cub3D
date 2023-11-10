/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:46 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 14:51:14 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall_slice(t_map *Map, int x, int draw_start, int draw_end)
{
    t_img *image;
    image = &Map->images[Map->id];
    double tex_x;

    if (Map->ray.side == 0)
        tex_x = Map->player.pos_y + Map->ray.perp_dist * Map->ray.dir_y;
    else
        tex_x = Map->player.pos_x + Map->ray.perp_dist * Map->ray.dir_x;
    tex_x = (tex_x - floor(tex_x)) * image->width;
    int img_height = draw_end - draw_start;
    int img_width = 1;
    int img_bits_per_pixel = image->bpp;
    int img_line_len = image->line_len;
    int endian; 
    void *img_ptr = mlx_new_image(Map->window.mlx_ptr, img_width, img_height);
    char *img_addr = mlx_get_data_addr(img_ptr, &img_bits_per_pixel, &img_line_len, &endian);
    for (int y = 0; y < img_height; y++)
    {
        int tex_y = (int)((y / (double)img_height) * image->height);
        int texel_offset = (tex_y * image->line_len + (int)tex_x * (image->bpp / 8));
        int img_offset = y * img_line_len;
        *(int *)(img_addr + img_offset) = *(int *)(image->addr + texel_offset);
    }
    mlx_put_image_to_window(Map->window.mlx_ptr, Map->window.win_ptr, img_ptr, x, draw_start);
    mlx_destroy_image(Map->window.mlx_ptr, img_ptr);
}

void	draw(t_map *Map, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(WINDOW_HEIGHT / Map->ray.perp_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (Map->ray.side == 0 && Map->ray.dir_x > 0)
		Map->id = 2;
	else if (Map->ray.side == 0 && Map->ray.dir_x < 0)
		Map->id = 3;
	else if (Map->ray.side == 1 && Map->ray.dir_y < 0)
		Map->id = 1;
	else if (Map->ray.side == 1 && Map->ray.dir_y > 0)
		Map->id = 0;
	draw_wall_slice(Map, x, draw_start, draw_end);
}

void	loop(t_map *Map, int *map_x, int *map_y)
{
	while (1)
	{
		if (Map->ray.side_dist_x < Map->ray.side_dist_y)
		{
			Map->ray.side_dist_x += Map->ray.delta_dist_x;
			*map_x += Map->ray.step_x;
			Map->ray.side = 0;
		}
		else
		{
			Map->ray.side_dist_y += Map->ray.delta_dist_y;
			*map_y += Map->ray.step_y;
			Map->ray.side = 1;
		}
		if (*map_x >= 0 && *map_x < Map->col_count && *map_y >= 0
			&& *map_y < Map->row_count && Map->map[*map_y][*map_x] == '1')
			break ;
	}
}

void	ray_init(t_map *Map, double camera_x, int map_x, int map_y)
{
	Map->ray.dir_x = Map->player.dir_x
		+ Map->player.cam_x * camera_x;
	Map->ray.dir_y = Map->player.dir_y
		+ Map->player.cam_y * camera_x;
	Map->ray.delta_dist_x = fabs(1 / Map->ray.dir_x);
	Map->ray.delta_dist_y = fabs(1 / Map->ray.dir_y);
	Map->ray.step_x = 1;
	Map->ray.side_dist_x = (map_x + 1.0 - Map->player.pos_x)
		* Map->ray.delta_dist_x;
	Map->ray.step_y = 1;
	Map->ray.side_dist_y = (map_y + 1.0 - Map->player.pos_y)
		* Map->ray.delta_dist_y;
	if (Map->ray.dir_x < 0)
	{
		Map->ray.step_x = -1;
		Map->ray.side_dist_x = (Map->player.pos_x - map_x)
			* Map->ray.delta_dist_x;
	}
	if (Map->ray.dir_y < 0)
	{
		Map->ray.step_y = -1;
		Map->ray.side_dist_y = (Map->player.pos_y - map_y)
			* Map->ray.delta_dist_y;
	}
}

void	cast_ray(t_map *Map, int x)
{
	double	camera_x;
	int		map_x;
	int		map_y;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	map_x = (int)Map->player.pos_x;
	map_y = (int)Map->player.pos_y;
	if (Map->player.dir_x == 0)
	{
		if (Map->player.dir_y == -1 || Map->player.dir_y == 1)
		{
			Map->player.cam_y = 0.0;
			Map->player.cam_x = Map->player.dir_y * -1;
		}
	}
	ray_init(Map, camera_x, map_x, map_y);
	loop(Map, &map_x, &map_y);
	Map->ray.perp_dist = fabs((map_y - Map->player.pos_y
				+ (1 - Map->ray.step_y) / 2) / Map->ray.dir_y);
	if (Map->ray.side == 0)
		Map->ray.perp_dist = fabs((map_x - Map->player.pos_x
					+ (1 - Map->ray.step_x) / 2) / Map->ray.dir_x);
	draw(Map, x);
}
