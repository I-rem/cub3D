#include "cub3d.h"

void draw_wall_slice2(t_map *M, t_img *image, double tex_x)
{
	int		tex_y;
	int		texel_offset;
	int		img_offset;
	int		y;

	y = -1;
	while (++y < M->wall.height)
    {
        tex_y = (int)((y / (double)M->wall.height) * image->height);
        texel_offset = (tex_y * image->line_len
						+ (int)tex_x * (image->bpp / 8));
        img_offset = y * M->wall.line_len;
        *(int *)(M->wall.addr + img_offset) = *(int *)(image->addr
												+ texel_offset);
    }
}

void draw_wall_slice(t_map *M, int x, int draw_start, int draw_end)
{
    t_img	*image;
    double	tex_x;
	
	image = &M->images[M->id];
    if (M->ray.side == 0)
		tex_x = M->player.pos_y + M->ray.perp_dist * M->ray.dir_y;
	else
		tex_x = M->player.pos_x + M->ray.perp_dist * M->ray.dir_x;
	tex_x = (tex_x - floor(tex_x)) * image->width;
    M->wall.height = draw_end - draw_start;
    M->wall.bpp = image->bpp;
    M->wall.line_len = image->line_len;
    M->wall.img = mlx_new_image(M->window.mlx_ptr, 1, M->wall.height);
    M->wall.addr = mlx_get_data_addr(M->wall.img, &M->wall.bpp,
					&M->wall.line_len, &M->wall.endian);
    draw_wall_slice2(M, image, tex_x);
    mlx_put_image_to_window(M->window.mlx_ptr,M->window.win_ptr,
							M->wall.img, x, draw_start);
    mlx_destroy_image(M->window.mlx_ptr, M->wall.img);
}

void	rotate(t_map *M)
{
	double	rs;
	double	old_dir_x;
	double	old_pl_x;

	rs = -ROTATION_SPEED;
	if (M->flags.l_flag)
		rs = ROTATION_SPEED;
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

int	handle_no_event(t_map *Map)
{
	if (Map->flags.r_flag || Map->flags.l_flag)
		rotate(Map);
	if (Map->flags.w_flag || Map->flags.a_flag
		|| Map->flags.s_flag || Map->flags.d_flag)
	{
		if (Map->flags.w_flag)
			check_move(Map, W);
		else if (Map->flags.a_flag)
			check_move(Map, A);
		else if (Map->flags.s_flag)
			check_move(Map, S);
		else if (Map->flags.d_flag)
			check_move(Map, D);
	}
	return (0);
}
