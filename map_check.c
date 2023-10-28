/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:31 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 17:28:26 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (err("No floors. Error\n", Map));
	else if (one_count == 1)
		return (err("No walls. Error\n", Map));
	return (0);
}

int	char_check(t_map *Map, int i, int j, int start_count)
{
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
					return (err("Too many starting positions. Error\n", Map));
				Map->player.pos_x = j;
				Map->player.pos_y = i - 6;
				Map->start_dir = Map->map[i][j];
			}
			else if (Map->map[i][j] != '1' && Map->map[i][j] != '0'
					&& Map->map[i][j] != ' ')
				return (err("Invalid characters on map. Error\n", Map));
		}
	}
	if (start_count == 0)
		return (err("No starting position entered on map. Error\n", Map));
	return (char_check2(Map, 5, -1));
}

int	wall_check(t_map *Map, int i, int j)
{
	new_map(Map);
	while (++i < Map->col_count && Map->map[i])
	{
		j = -1;
		while (++j < Map->row_count && Map->map[i][j] != '\0')
		{
			if ((Map->map[i][j] && Map->map[i][j] == '0')
				&& (i == 0 || j == 0 || is_bad(Map->map[i - 1][j])
				|| !Map->map[i + 1] || is_bad(Map->map[i + 1][j])
				|| is_bad(Map->map[i][j - 1]) || is_bad(Map->map[i][j + 1])))
				return (err("Walls are wrong. Error\n", Map));
			if (Map->map[i][j] && (Map->map[i][j] == 'N'
				|| Map->map[i][j] == 'S'
				|| Map->map[i][j] == 'W' || Map->map[i][j] == 'E')
				&& (i == 0 || j == 0 || is_bad(Map->map[i - 1][j])
				|| !Map->map[i + 1] || is_bad(Map->map[i + 1][j])
				|| is_bad(Map->map[i][j - 1]) || is_bad(Map->map[i][j + 1])))
				return (err("Walls are wrong. Error\n", Map));
		}
	}
	return (0);
}

int	texture_check2(t_map *Map, int i)
{
	while (++i < 6 && Map->map[i])
	{
		if (!ft_strncmp(Map->map[i], "NO ", 3))
			Map->no = ft_strtrim(Map->map[i] + 3, " ");
		else if (!ft_strncmp(Map->map[i], "SO ", 3))
			Map->so = ft_strtrim(Map->map[i] + 3, " ");
		else if (!ft_strncmp(Map->map[i], "WE ", 3))
			Map->we = ft_strtrim(Map->map[i] + 3, " ");
		else if (!ft_strncmp(Map->map[i], "EA ", 3))
			Map->ea = ft_strtrim(Map->map[i] + 3, " ");
		else if (!ft_strncmp(Map->map[i], "F ", 2))
			Map->f = ft_strtrim(Map->map[i] + 2, " ");
		else if (!ft_strncmp(Map->map[i], "C ", 2))
			Map->c = ft_strtrim(Map->map[i] + 2, " ");
	}
	if (!file_check(Map->no, 2) || !file_check(Map->so, 2)
		|| !file_check(Map->we, 2) || !file_check(Map->ea, 2))
		return (err("Invalid texture files. Error\n", Map));
	if (color_check(Map->f, Map) || color_check(Map->c, Map)
		|| char_check(Map, 5, -1, 0) || wall_check(Map, -1, -1))
		return (1);
	return (0);
}

int	texture_check(t_map *Map, int i)
{
	char	*temp;

	while (++i < 6 && Map->map[i])
	{
		temp = ft_strtrim(Map->map[i], " ");
		free(Map->map[i]);
		Map->map[i] = temp;
		temp = NULL;
	}
	return (texture_check2(Map, -1));
}
