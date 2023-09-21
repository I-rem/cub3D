#include "cub3d.h"

int	char_check2(t_map *Map, int i, int j)
{
	int zero_count;
	int one_count;

	zero_count = 0;
	one_count = 0;
	while(Map->map[++i])
	{
		j = -1;
		while(Map->map[i][++j])
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

int	char_check(t_map *Map, int i, int j) // To do: count 0s and 1s too and make sure there is at least one of each
{
	int	start_count;

	start_count = 0;
	while(Map->map[++i])
	{
		j = -1;
		while(Map->map[i][++j])
		{
			if (Map->map[i][j] == 'N' || Map->map[i][j] == 'W'
				|| Map->map[i][j] == 'E' || Map->map[i][j] == 'S')
			{
				start_count++;
				if (start_count > 1)
					return (err("Too many starting positions on map. Error\n"));
				Map->start_pos_x = j;
				Map->start_pos_y = i;
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

int	color_check(char *color)
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

int wall_check(t_map *Map, int i, int j)
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

int texture_check2(t_map *Map)
{
	return (!(file_check(Map->NO, 2) && file_check(Map->SO, 2)
		&& file_check(Map->WE, 2) && file_check(Map->EA, 2)));
}

int texture_check(t_map *Map)
{
	// Texture adresses can be given in any order code below wont actually be enough for this project :(
    Map->NO = ft_strtrim(ft_strdup(ft_strtrim(Map->map[0], " ") + 3), " ");
    Map->SO = ft_strtrim(ft_strdup(ft_strtrim(Map->map[1], " ") + 3), " ");
    Map->WE = ft_strtrim(ft_strdup(ft_strtrim(Map->map[2], " ") + 3), " ");
    Map->EA = ft_strtrim(ft_strdup(ft_strtrim(Map->map[3], " ") + 3), " ");
    Map->F = ft_strtrim(ft_strdup(ft_strtrim(Map->map[4], " ") + 2), " ");
    Map->C = ft_strtrim(ft_strdup(ft_strtrim(Map->map[5], " ") + 2), " ");

	//Check if the texture files exist, can be read, and have the right file ending
	return (color_check(Map->F) || color_check(Map->C)
			|| char_check(Map, 5, -1) || wall_check(Map, 5, -1));
}

int	map_check(t_map *Map)
{
	return (texture_check(Map) || char_check(Map, 5, -1) || wall_check(Map, 5, -1));
}
