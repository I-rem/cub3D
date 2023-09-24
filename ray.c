#include "cub3d.h"
#define looking_angle 90
// If north looking angle is 90

typedef struct s_ray{
	int	ray_len;
	int	wall_height;
	int	ray_x;
	int	ray_y;
	int	angle;
} t_ray;

void	check_gridline(t_ray *ray, t_map *Map)
{
	ray->ray_y = ((Map->start_pos_y / 64) * 64) + (- Map->start_pos_y);
	ray->ray_x =(Map->start_pos_y - ray->ray_y) / -tan(looking_angle) + start_pos_x;
}

void	draw_line()
{

}

void	raycasting(t_map *Map)
{
	int	x;
	int	y;
	int	begin;
	int	end;

	t_ray ray[WINDOW_WIDTH];

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		check_gridline(ray[x], Map);
		ray[x].wall_height = (64 * WINDOW_HEIGHT
				/ ray[x].ray_len);
		begin = WINDOW_HEIGHT / 2 - ray[x].wall_height / 2;
		end = WINDOW_HEIGHT / 2 + ray[x].wall_height / 2;
		y = begin - 1;
		while (++y < end)
			draw_line(x, y);
	}
}
