#include "cub3d.h"
#define looking_angle 90
// If north looking angle is 90

double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void cast_ray(t_map *Map, double player_x, double player_y, double ray_angle, double *hit_x, double *hit_y) {
    double x_step, y_step;
    double x_check, y_check;
    double x_intersect, y_intersect;
    int grid_x, grid_y;

    // Initialize steps based on the ray angle
    if (ray_angle >= 0 && ray_angle <= M_PI) {
        // Ray facing down
        y_step = -1;
        x_step = fabs(1 / tan(ray_angle));
    } else {
        // Ray facing up
        y_step = 1;
        x_step = fabs(1 / tan(ray_angle));
    }

    // Initialize the first intersection point (grid cell)
    x_check = floor(player_x / TILE_SIZE) * TILE_SIZE;
    y_check = player_y + (player_x - x_check) * tan(ray_angle);

    // Perform ray casting until we hit a wall
    while (x_check >= 0 && x_check < Map->col_count * TILE_SIZE &&
           y_check >= 0 && y_check < Map->row_count * TILE_SIZE) {
        grid_x = (int)(x_check / TILE_SIZE);
        grid_y = (int)(y_check / TILE_SIZE);

        if (Map->map[grid_y][grid_x] == '1') {
            // Wall hit
            x_intersect = x_check;
            y_intersect = y_check;
            break;
        }

        x_check += x_step;
        y_check += y_step;
    }

    *hit_x = x_intersect;
    *hit_y = y_intersect;
}

int calculate_wall_height(double distance) {
    // Apply perspective correction based on distance
    // This is a simplified example; you may need more complex calculations
    return (int)(WINDOW_HEIGHT / (2 * distance));
}

void render_wall_column(t_map *Map, int column, int wall_height) {
    int wall_color = 0xFFFFFF;  // Color of the wall texture

    int column_height = WINDOW_HEIGHT / 2;  // Half of the window height

    // Calculate top and bottom positions of the wall segment
    int wall_top = column_height - (wall_height / 2);
    int wall_bottom = wall_top + wall_height;

    // Render the wall segment in the specified column
    for (int y = 0; y < WINDOW_HEIGHT / 2; y++) {
        if (y < wall_top || y >= wall_bottom) {
            // Render the sky or floor
            mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, column, y, Map->C_col);
        } else {
            // Render the wall
            mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, column, y, wall_color);
        }
    }
}

/*
typedef struct s_ray{
	int	ray_len;
	int	wall_height;
	int	ray_x;
	int	ray_y;
	int	angle;
} t_ray;

void	check_gridline(t_ray *ray, t_map *Map)
{
	ray->ray_y = ((Map->p_pos_y / 64) * 64) + (- Map->p_pos_y);
	ray->ray_x =(Map->p_pos_y - ray->ray_y) / -tan(looking_angle) + p_pos_x;
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
}*/

