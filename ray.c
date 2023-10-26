#include "cub3d.h"

void	draw_wall_slice(t_map *Map, int x, int draw_start, int draw_end, int id)
{
	t_img	*image;
	int		y;
	int		img_y;
	int		color;
	
	image = &Map->Images[id];
	y = draw_start;	
	while (y < draw_end)
	{
		img_y = (int)((y - draw_start) * (double)image->height /
			(double)(draw_end - draw_start));
		color = *(int *)(image->addr + (img_y * image->line_len + x *
			(image->bpp / 8)));
		mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, x, y, color);
		y++;
	}
	image = NULL;
}

void	draw(t_map *Map, int x)
{
	int line_height;
	int draw_start;
	int draw_end;

	line_height = (int)(WINDOW_HEIGHT / Map->Ray.perp_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOW_HEIGHT) 
		draw_end = WINDOW_HEIGHT - 1;
	if (Map->Ray.side == 0 && Map->Ray.dir_x > 0)
    		draw_wall_slice(Map, x, draw_start, draw_end, 2);
	else if (Map->Ray.side == 0 && Map->Ray.dir_x < 0)
    		draw_wall_slice(Map, x, draw_start, draw_end, 3);
	else if (Map->Ray.side == 1 && Map->Ray.dir_y < 0)
    		draw_wall_slice(Map, x, draw_start, draw_end, 1);
	else if (Map->Ray.side == 1 && Map->Ray.dir_y > 0)
    		draw_wall_slice(Map, x, draw_start, draw_end, 0);
}

void	loop(t_map *Map, int *map_x, int *map_y)
{
	while (1)
	{
		if (Map->Ray.side_dist_x < Map->Ray.side_dist_y)
		{
			Map->Ray.side_dist_x += Map->Ray.delta_dist_x;
			*map_x += Map->Ray.step_x;
			Map->Ray.side = 0;
		}
		else
		{
			Map->Ray.side_dist_y += Map->Ray.delta_dist_y;
			*map_y += Map->Ray.step_y;
			Map->Ray.side = 1;
        	}
		if (*map_x >= 0 && *map_x < Map->col_count && *map_y >= 0 &&
			*map_y  < Map->row_count && Map->map[*map_y][*map_x] == '1')
			break;
	}
}

void	ray_init(t_map *Map, double camera_x, int map_x, int map_y)
{
	Map->Ray.dir_x = Map->Player.dir_x +
			Map->Player.cam_x * camera_x;
	Map->Ray.dir_y = Map->Player.dir_y +
			Map->Player.cam_y * camera_x;	
    	Map->Ray.delta_dist_x = fabs(1 / Map->Ray.dir_x);
    	Map->Ray.delta_dist_y = fabs(1 / Map->Ray.dir_y);
	Map->Ray.step_x = 1;
	Map->Ray.side_dist_x = (map_x + 1.0 - Map->Player.pos_x) *
				Map->Ray.delta_dist_x;
	Map->Ray.step_y = 1;
	Map->Ray.side_dist_y = (map_y + 1.0 - Map->Player.pos_y) *
				Map->Ray.delta_dist_y;
	if (Map->Ray.dir_x < 0)
	{
	        Map->Ray.step_x = -1;
	        Map->Ray.side_dist_x = (Map->Player.pos_x - map_x) *
					Map->Ray.delta_dist_x;
	}
	if (Map->Ray.dir_y < 0)
	{
	        Map->Ray.step_y = -1;
	        Map->Ray.side_dist_y = (Map->Player.pos_y - map_y) *
					Map->Ray.delta_dist_y;
	}
}

void cast_ray(t_map *Map, int x)
{
	double	camera_x;
	int map_x;
	int map_y;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	map_x = (int)Map->Player.pos_x;
	map_y = (int)Map->Player.pos_y;
	if (Map->Player.dir_x == 0)
		if (Map->Player.dir_y == -1 || Map->Player.dir_y == 1)
		{
			Map->Player.cam_y = 0.0;
			Map->Player.cam_x = Map->Player.dir_y * -1;
		}
	ray_init(Map, camera_x, map_x, map_y);
	loop(Map, &map_x, &map_y);
	Map->Ray.perp_dist = fabs((map_y - Map->Player.pos_y +
				(1 - Map->Ray.step_y) / 2) / Map->Ray.dir_y);
	if (Map->Ray.side == 0)
		Map->Ray.perp_dist = fabs((map_x - Map->Player.pos_x +
				(1 - Map->Ray.step_x) / 2) / Map->Ray.dir_x);
	draw(Map, x);
}

