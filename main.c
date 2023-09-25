#include "cub3d.h"

int	err (char *str)
{
	//free_all();
	while (*str)
		write(1, str++, 1);
	return (1);
}

int	file_check(char *filepath, int type)
{
	int	len;
	int	fd;

	if (filepath == NULL)
		return(0);
	len = ft_strlen(filepath);
       	if (type == 1)
	       	if (ft_strncmp(filepath + len - 4, ".cub", 4))
			return (0);
	if (type == 2)
		if (ft_strncmp(filepath + len - 4, ".xpm", 4))
			return (0);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return 0;
	}
	return (fd);
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

int	init_map (int fd, t_map *Map)
{
	char	*str;
	char	*result;

	str = get_next_line(fd);
	result = "";
	while(str)
	{
		result = ft_strjoin(result, str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	map_size(result, Map);
	if (Map->row_count < 9 || Map->col_count < 4)
		return (err("Invalid map format. Error\n"));
	Map->map = ft_split(result, '\n');
	free(result);
	Map->player_angle = 0.0;
	return (texture_check(Map, -1));
}

int	main (int argc, char **argv)
{
	int	fd;
	t_map	Map;

	if (argc != 2)
		return (err("Incorrect number of arguments. Error\n"));
	fd = file_check(argv[1], 1);
	if (!fd)
		return (err("Invalid file. Error\n"));   
	if (init_map(fd, &Map))
		return (1);
	Map.Window.mlx_ptr = mlx_init();
	if (Map.Window.mlx_ptr == NULL)
		return (err("Mlx Pointer Error\n"));
	open_window(&Map);
	img_init(&Map);
	//free_all();
}
