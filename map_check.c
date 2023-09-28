#include "cub3d.h"

int	char_check2(t_map *Map, int i, int j)
{
	int	zero_count;
	int	one_count;

	zero_count = 0;
	one_count = 0;
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j])
		{
			if (Map->map[i][j] == '0')
				zero_count++;
			else if (Map->map[i][j] == '1')
				one_count++;
		}
	}
	if (zero_count == 0)
		return (err("No floors. Error\n"));
	else if (one_count == 1)
		return (err("No walls. Error\n"));
	return (0);
}

int	char_check (t_map *Map, int i, int j)
{
	int	start_count;

	start_count = 0;
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j])
		{
			if (Map->map[i][j] == 'N' || Map->map[i][j] == 'W'
				|| Map->map[i][j] == 'E' || Map->map[i][j] == 'S')
			{
				start_count++;
				if (start_count > 1)
					return (err("Too many starting positions on map. Error\n"));
				Map->Player.pos_x = j;
				Map->Player.pos_y = i - 6;
			}
			else if (Map->map[i][j] != '1' && Map->map[i][j] != '0'
					&& Map->map[i][j] != ' ')
				return (err("Invalid characters on map. Error\n"));
		}
	}
	if (start_count == 0)
		return err("No starting position entered on map. Error\n");
	return (char_check2(Map, 5, -1));
}

int	color_check (char *color)
{
	char	**rgb;
	int		len;

	len = 0;
	rgb = ft_split(color, ',');
	while (rgb[len])
		len++;
	write(1, &len, 1);
	if (len != 3)
		return (err("Wrong color format. Error\n"));
	while (--len >= 0)
		if (ft_atoi(rgb[len]) > 255 || ft_atoi(rgb[len]) < 0)
			return (err("Wrong color format. Error\n"));
	return (0);
}

int	wall_check (t_map *Map, int i, int j)
{
	while (Map->map[++i])
	{
		j = -1;
		while (Map->map[i][++j])
		{
			if (Map->map[i][j] == '0' && (Map->map[i - 1][j] == ' '
				|| Map->map[i + 1][j] == ' ' || Map->map[i ][j - 1] == ' '
				|| Map->map[i][j + 1] == ' '))
			return (err("Improper map. Error\n"));
			if ((Map->map[i][j] == 'N' || Map->map[i][j] == 'S'
				|| Map->map[i][j] == 'W' || Map->map[i][j] == 'E')
				&& (Map->map[i - 1][j] == ' '
				|| Map->map[i + 1][j] == ' ' || Map->map[i ][j - 1] == ' '
				|| Map->map[i][j + 1] == ' '))
			return (err("Improper map. Error\n"));
		}
	}
	return (0);
}

int	texture_check(t_map *Map, int i)
{

	while (Map->map[++i] && i < 6)
		Map->map[i] = ft_strdup(ft_strtrim(Map->map[i], " "));
	i = -1;
	while (Map->map[++i] && i < 6)
	{
		if (!ft_strncmp(Map->map[i], "NO ", 3))
			Map->NO = ft_strdup(ft_strtrim(ft_strdup(Map->map[i] + 3), " "));
		else if (!ft_strncmp(Map->map[i], "SO ", 3))
			Map->SO = ft_strdup(ft_strtrim(ft_strdup(Map->map[i] + 3), " "));
		else if (!ft_strncmp(Map->map[i], "WE ", 3))
			Map->WE = ft_strtrim(ft_strdup(Map->map[i] + 3), " ");
		else if (!ft_strncmp(Map->map[i], "EA ", 3))
			Map->EA = ft_strtrim(ft_strdup(Map->map[i] + 3), " ");
		else if (!ft_strncmp(Map->map[i], "F ", 2))
			Map->F = ft_strtrim(ft_strdup(Map->map[i] + 2), " ");
		else if (!ft_strncmp(Map->map[i], "C ", 2))
			Map->C = ft_strtrim(ft_strdup(Map->map[i] + 2), " ");
	}
	if (!file_check(Map->NO, 2) || !file_check(Map->SO, 2)
		|| !file_check(Map->WE, 2) || !file_check(Map->EA, 2))
		return (err("Invalid texture files. Error\n"));
	return (color_check(Map->F) || color_check(Map->C)
			|| char_check(Map, 5, -1) || wall_check(Map, 5, -1));
}
