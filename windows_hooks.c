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

void	render_map(t_map *Map)
{
	
	int	i;
	int	j;

	i = Map->start_pos_x - 1;
	j = Map->start_pos_y - 1;

	while (Map->map[++i])
	{
		while (Map->map[i][j] != '1')
			i++;
		if (Map->map[i][j] == '1')
		{
		    // mlx_destroy_image(Map->Window.mlx_ptr, Map->NO);
		    // Map->NO = mlx_new_image(Map->Window.mlx_ptr, 1000, 100);
		    mlx_put_image_to_window(Map->Window.mlx_ptr, Map->Window.win_ptr,
					Map->NO_img, WINDOW_WIDTH / 4, abs(Map->start_pos_y -i)*64); // Ekranı ortalaması lazım
			break;		
		}
	}
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
