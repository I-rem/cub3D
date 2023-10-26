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

void	move(t_map *Map, double x, double y)
{
	Map->Player.pos_x = x;
	Map->Player.pos_y = y;
	render_map(Map);
}

void img_init2(void *img, int color, int y, int x)
{
    int		pixel_bits;
    int		line_bytes;
    int		endian;
    char	*buffer;
    int		pixel;

    buffer = mlx_get_data_addr(img, &pixel_bits, &line_bytes, &endian);
    while (y < WINDOW_HEIGHT / 2)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            pixel = (y * line_bytes) + (x * 4);
            buffer[pixel + 0] = (color >> 0) & 0xFF;
            buffer[pixel + 1] = (color >> 8) & 0xFF; 
            buffer[pixel + 2] = (color >> 16) & 0xFF;
            buffer[pixel + 3] = (color >> 24) & 0xFF;
            x++;
        }
        y++;
    }
}

void	img_init(t_map *data, int i)
{
	data->F_col = find_color(data->F);
	data->C_col = find_color(data->C);
	data->F_img = mlx_new_image(data->Window.mlx_ptr
			            , WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	data->C_img = mlx_new_image(data->Window.mlx_ptr
			            , WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	img_init2(data->C_img, data->C_col, 0, 0);
	img_init2(data->F_img, data->F_col, 0, 0);
	data->Images[0].img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->NO, 
							&data->Images[0].width, &data->Images[0].height);
	data->Images[1].img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->SO,
							&data->Images[1].width, &data->Images[1].height);
	data->Images[2].img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->WE,
							&data->Images[2].width, &data->Images[2].height);
	data->Images[3].img = mlx_xpm_file_to_image(data->Window.mlx_ptr, data->EA,
							&data->Images[3].width, &data->Images[3].height);
	while (++i < 4)
		data->Images[i].addr = mlx_get_data_addr(data->Images[i].img,
								&data->Images[i].bpp, &data->Images[i].line_len,
								&data->Images[i].endian);
	render_map(data);
	mlx_key_hook(data->Window.win_ptr, &handle_input, data);
	mlx_loop_hook(data->Window.mlx_ptr, &handle_no_event, data);
	mlx_loop(data->Window.mlx_ptr);
}

void	img_delete(t_map *data)
{
	if (!data)
		return ;
	if (data->C_img)
		mlx_destroy_image(data->Window.mlx_ptr, data->C_img);
    if (data->F_img)
		mlx_destroy_image(data->Window.mlx_ptr, data->F_img);
	if (data->Images && data->Images[0].img)
		mlx_destroy_image(data->Window.mlx_ptr, data->Images[0].img);
	if (data->Images && data->Images[1].img)
		mlx_destroy_image(data->Window.mlx_ptr, data->Images[1].img);
	if (data->Images && data->Images[2].img)
		mlx_destroy_image(data->Window.mlx_ptr, data->Images[2].img);
	if (data->Images && data->Images[3].img)
		mlx_destroy_image(data->Window.mlx_ptr, data->Images[3].img);
}

void	check_move(t_map *Map, int keycode)
{
	double nw_x;
	double nw_y;

	nw_x = Map->Player.pos_x + Map->Player.dir_y * MOVE_SPEED;
	nw_y = Map->Player.pos_y - Map->Player.dir_x * MOVE_SPEED;
	if (keycode == S || keycode == W)
	{
		nw_x = Map->Player.pos_x - Map->Player.dir_x * MOVE_SPEED;
		nw_y = Map->Player.pos_y - Map->Player.dir_y * MOVE_SPEED;
		if (keycode == W)
		{
			nw_x = Map->Player.pos_x + Map->Player.dir_x * MOVE_SPEED;
			nw_y = Map->Player.pos_y + Map->Player.dir_y * MOVE_SPEED;
		}
	}		
	else if ((keycode == A && Map->start_dir == 'W')
		|| (keycode == D && Map->start_dir != 'W'))
	{
		nw_x = Map->Player.pos_x - Map->Player.dir_y * MOVE_SPEED;
		nw_y = Map->Player.pos_y + Map->Player.dir_x * MOVE_SPEED;
	}	
	if (nw_x >= 0 && nw_x < WINDOW_WIDTH && nw_y >= 0 && nw_y < WINDOW_HEIGHT)
		if (Map->map[(int)nw_y][(int)nw_x] &&
			Map->map[(int)nw_y][(int)nw_x] != '1')
			move(Map, nw_x, nw_y);		
}
