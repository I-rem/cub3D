#include "cub3d.h"

int	init_map2(char *result, t_map *Map)
{
	map_size(result, Map);
	if (Map->row_count < 9 || Map->col_count < 4 || line_check(result))
    {
		if (result)
        	free(result);
        return err("Invalid map format. Error\n", Map);
    }
	Map->map = ft_split(result, '\n');
	if (result)
    	free(result);
	if (!Map->map)
        return err("Memory allocation failed. Error\n", Map);
    return (texture_check(Map, -1));
}

int init_map(int fd, t_map *Map)
{
    char *str;
    char *result;
    char *temp;

	result = NULL;
	temp = NULL;
	init_null(Map);
	str = get_next_line(fd);
    while (str != NULL)
    {
        temp = ft_strjoin(result, str);
        free(str);
		free(result);
        if (!temp)
            return err("Memory allocation failed. Error\n", Map);
        result = temp;
		str = get_next_line(fd);
    }
	return (init_map2(result, Map));
}

void	new_map(t_map *Map)
{
	int	i;
	int	j;
	int	max;
	
	i = -1;
	while (++i < 6)
	{
		if (Map->map[i])
			free(Map->map[i]);
		Map->map[i] = NULL;
	}
	Map->map += 6;
	i = -1;
	while (Map->map[++i] != NULL);
	Map->row_count = i;
	i = -1;
	max = 0;
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j]);
		if (j > max)
			max = j;
	}
	Map->col_count = max;
}

void	init_dir (t_map *Map)
{
	if (Map->start_dir == 'W')
	{
		Map->Player.dir_x = -1.0;
		Map->Player.dir_y = 0.0;
	}
	else if (Map->start_dir == 'E')
	{
		Map->Player.dir_x = 1.0;
		Map->Player.dir_y = 0.0;
	}
	else if (Map->start_dir == 'N')
	{
		Map->Player.dir_x = 0.0;
		Map->Player.dir_y = -1.0;
	}
	else if (Map->start_dir == 'S')
	{
		Map->Player.dir_x = 0.0;
		Map->Player.dir_y = 1.0;
	}
}

int	main (int argc, char **argv)
{
	int	fd;
	t_map	Map;

	if (argc != 2)
		return (err("Incorrect number of arguments. Error\n", NULL));
	fd = file_check(argv[1], 1);
	if (!fd)
		return (err("Invalid file. Error\n", NULL));   
	if (init_map(fd, &Map))
		return (1);
	close(fd);
	init_dir(&Map);
	Map.Player.cam_x = 0.0;
	Map.Player.cam_y = 0.66;
	Map.Player.pos_x += 0.32;
	Map.Player.pos_y += 0.5;
	Map.Window.mlx_ptr = mlx_init();
	if (Map.Window.mlx_ptr == NULL)
		return (err("Mlx Pointer Error\n", &Map));
	open_window(&Map);
	img_init(&Map, -1);
	free_map(&Map);
}
