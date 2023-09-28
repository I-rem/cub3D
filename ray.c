#include "cub3d.h"

void draw_wall_slice(t_map *Map, int x, int draw_start, int draw_end, int id) {
    t_img *image;

    image = &Map->Images[id];
    for (int y = draw_start; y < draw_end; y++) {
        int img_y = (int)((y - draw_start) * (double)image->height / (double)(draw_end - draw_start));
        int color = *(int *)(image->addr + (img_y * image->line_len + x * (image->bpp / 8)));
        mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, x, y, color);
    }
}

void    draw_col(t_map *Map, int x, int start, int end, int color)
{
    int y;

    y = start;
    while (y++ < end)
    {
        mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, x, y, color);
    }
}

void cast_ray(t_map *Map, int x) {
    
    // Calculate the ray's direction in the game world
    double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
    Map->Ray.dir_x = Map->Player.dir_x + Map->Player.cam_x * camera_x;
    Map->Ray.dir_y = Map->Player.dir_y + Map->Player.cam_y * camera_x;

    // Initial position and direction of the ray
    int map_x = (int)Map->Player.pos_y;
    int map_y = (int)Map->Player.pos_x;

    // Length of ray from current position to next x or y-side
    double side_dist_x;
    double side_dist_y;

    // Length of ray from one side to next in map
    double delta_dist_x = fabs(1 / Map->Ray.dir_x);
    double delta_dist_y = fabs(1 / Map->Ray.dir_y);

    // Step to determine whether the ray moves in the x-direction or y-direction
    int step_x;
    int step_y;

    // Calculate initial side_dist_x and side_dist_y
    if (Map->Ray.dir_x < 0) {
        step_x = -1;
        side_dist_x = (Map->Player.pos_y - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - Map->Player.pos_y) * delta_dist_x;
    }
    if (Map->Ray.dir_y < 0) {
        step_y = -1;
        side_dist_y = (Map->Player.pos_x - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - Map->Player.pos_x) * delta_dist_y;
    }

    // Perform DDA (Digital Differential Analysis) algorithm
    while (1) {
        
        // Check if the ray has hit a wall
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            Map->Ray.side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            Map->Ray.side = 1;
        }
        // Check if the ray has hit a wall (you need to implement this condition based on your map data)
        if (map_x >= 0 && map_x < Map->row_count && map_y >= 0 && map_y  < Map->col_count && Map->map[map_x][map_y] == '1') {
            break;
            
        }
    }
   
    // Calculate the perpendicular distance to the wall
    if (Map->Ray.side == 0) {
        Map->Ray.perp_dist = fabs((map_x - Map->Player.pos_y + (1 - step_x) / 2) / Map->Ray.dir_x);
    } else {
        Map->Ray.perp_dist = fabs((map_y - Map->Player.pos_x + (1 - step_y) / 2) / Map->Ray.dir_y);
    }

    // Calculate the height of the wall slice to draw
    int line_height = (int)(WINDOW_HEIGHT / Map->Ray.perp_dist);

    // Calculate the starting and ending points for drawing the wall slice
    int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_start < 0) {
        draw_start = 0;
    }
    int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_end >= WINDOW_HEIGHT) {
        draw_end = WINDOW_HEIGHT - 1;
    }

    // Choose wall color based on the side of the wall
   

    // Draw the wall slice
   
    //draw_col(Map, x, draw_start, draw_end, color);
    // Determine which texture to use based on the wall's orientation
    int tex_id = 0; // Default to north texture
    if (Map->Ray.side == 0 && Map->Ray.dir_x > 0)
        tex_id = 2; // East texture
    else if (Map->Ray.side == 0 && Map->Ray.dir_x < 0)
        tex_id = 3; // West texture
    else if (Map->Ray.side == 1 && Map->Ray.dir_y > 0)
        tex_id = 1; // South texture

    // Render the wall slice with the appropriate texture
    draw_wall_slice(Map, x, draw_start, draw_end, tex_id);
}

