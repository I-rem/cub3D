#include "cub3d.h"

int		line_check(char *map)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (map[++i] && count < 6)
		if (map[i] == '\n')
		{
			count++;
			while(map[++i] == '\n');
		}
	if (count == 6)
		while (map[++i])
		{
			if (map[i] && map[i] == '\n'
				&& map[i + 1] == '\n')
			{
				while(map[++i] == '\n');
				if (map[i] != '\0')
					return (1);	
			}
		}
	return (0);
}

void	map_size (char *map, t_map *Map)
{
	int	max;
	int	row;
	int	i;
	int	col;

	i = -1;
	max = 0;
	row = 0;
	col = 0;
	if (map)
		while (map[++i])
		{
			if (map[i] == '\n')
			{
				col = 0;
				row++;
			}
			else
				col++;
			if (col > max)
				max = col;
		}
	Map->row_count = row;
	Map->col_count = max;
}

void	init_null(t_map *Map)
{
	Map->map = NULL;
	Map->NO = NULL;
	Map->SO = NULL;
	Map->WE = NULL;
	Map->EA = NULL;
	Map->F = NULL;
	Map->C = NULL;
	Map->F_img = NULL;
	Map->C_img = NULL;
}

int init_map(int fd, t_map *Map)
{
    char *str;
    char *result;
    char *temp;

	result = NULL;
	temp = NULL;
	init_null(Map);
    while ((str = get_next_line(fd)) != NULL)
    {
        temp = ft_strjoin(result, str);
        free(str);
        if (!temp)
        {
			if (result)
            	free(result);
            return err("Memory allocation failed. Error\n", Map);
        }
		if (result)
        	free(result);
        result = temp;
		temp = NULL;
    }
    if (result == NULL)
        return err("Failed to read map. Error\n", Map);
    map_size(result, Map);
	if (Map->row_count < 9 || Map->col_count < 4)
    {
        free(result);
        return err("Invalid map format. Error\n", Map);
    }
	if (line_check(result))
		return(err("Empty line in map. Error\n", Map));
	Map->map = ft_split(result, '\n');
    free(result);
	if (!Map->map)
        return err("Memory allocation failed. Error\n", Map);
    return (texture_check(Map, -1));
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
	i = 0;
	while (Map->map[i] != NULL)
		i++;
	Map->row_count = i;
	i = -1;
	max = 0;
	while (Map->map[++i])
	{
		j = 0;
		while (Map->map[i][j])
			j++;
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
	new_map(&Map);
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
