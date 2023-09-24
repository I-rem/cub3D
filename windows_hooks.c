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

void	render_minimap(t_map *Map)
{
	int	i;
	int	j;

	i = 5;
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j])
		{
			mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
				Map->Minimap.floor_img, j * 16, (i-6) * 16);
			if (Map->map[i][j] == '1')
				mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
					Map->Minimap.wall_img, j * 16, (i-6) * 16);
		}
	}
	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
		Map->Minimap.player_img, Map->start_pos_x * 16, (Map->start_pos_y-6) * 16);
}

void render_image(int s, t_map *data)
{
	void *img = mlx_new_image(data->Window.mlx_ptr
			            , s, s);
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer;
	int	pixel;
	int x = 0;
	int y = 0;
	int color = 0xAAADEF;
	buffer = mlx_get_data_addr(img, &pixel_bits, &line_bytes, &endian);
	while(y++ < s)
	{
		x = 0;
		while(x++ <s)
		{
			pixel = (y * line_bytes) + (x*4);
			if (endian == 1)
			{
			    buffer[pixel + 0] = (color >> 24);
			    buffer[pixel + 1] = (color >> 16) & 0xFF;
                            buffer[pixel + 2] = (color >> 8) & 0xFF;
			    buffer[pixel + 3] = (color) & 0xFF;
			} 
                        else if (endian == 0)
			{
			    buffer[pixel + 0] = (color) & 0xFF;
			    buffer[pixel + 1] = (color >> 8) & 0xFF;
                            buffer[pixel + 2] = (color >> 16) & 0xFF;
			    buffer[pixel + 3] = (color >> 24);
			} 
		}
	}
	mlx_put_image_to_window(data->Window.mlx_ptr, data->Window.win_ptr, img,WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
void	render_map(t_map *Map) // render sky color and floor color horizon will be at the middle of  the window
{
	
	int	i;
	int	j;


	/*i = -1;
	j = -1;

	while(++i < WINDOW_WIDTH)
	{
		j = -1;
		while (++j <= WINDOW_HEIGHT / 2){
		mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr, i, j, 255);
		mlx_pixel_put(Map->Window.mlx_ptr, Map->Window.win_ptr,i, WINDOW_HEIGHT - j, 255255);}
	}*/
	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr, Map->C_img, 0, 0);
	mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr, Map->F_img, 0, WINDOW_HEIGHT / 2);
	i = Map->start_pos_y;
	j = Map->start_pos_x;
	while (Map->map[i])
	{
		while (Map->map[i][j] != '1')
			i--;
		if (Map->map[i][j] == '1')
		{
		    //mlx_destroy_image(Map->Window.mlx_ptr, Map->NO);
		    //Map->NO = mlx_new_image(Map->Window.mlx_ptr, 1000, 100);
		   // mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
			//		Map->NO_img, WINDOW_WIDTH / 4, abs(Map->start_pos_y -i)*64); // Ekranı ortalaması lazım
			render_image(64 / abs(i - Map->start_pos_y), Map);			
			break;		
		}
	}
	render_minimap(Map);
	//raycasting(Map);
/*	i = 5;
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j])
		{
	//		mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
	//			Map-> floor.img_ptr, j * 16, i * 16);
			if (Map->map[i][j] == '1')
				mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
					Map->NO_img, j * 64, (i-6) * 64);
		}
	}*/
	/*mlx_put_image_to_window(data -> mlx_ptr, data -> win_ptr,
		data -> player.img_ptr, data -> map_data.p_position_x * 16,
		data -> map_data.p_position_y * 16);*/
}

int handle_input(int keycode, t_map *Map)
{
    if (keycode == ESC)
    {
	write(1, "ESC\n", 4);
	close_program(Map);
    }
    if (keycode == W || keycode == A || keycode == S || keycode == D)
    {
	
        check_move(Map, keycode);
        //render_map(Map);
		
    }
	/*
	if (keycode == RIGHT_ARR || keycode == LEFT_ARR)
    {
        //look();
        render_map(Map);
		write(1, "sdf", 3);
    }
	*/
    return (0);
}

void	open_window(t_map *Map)
{

    Map->Window.win_ptr = mlx_new_window(Map->Window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	mlx_hook(Map->Window.win_ptr, 17, 0, close_program, Map);
}
