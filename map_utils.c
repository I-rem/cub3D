/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:40 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 14:48:04 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *Map)
{
	int	i;

	i = -1;
	img_delete(Map);
	while (Map->map && Map->map[++i])
	{
		free(Map->map[i]);
		Map->map[i] = NULL;
	}
	if (Map->map - 6)
		free(Map->map - 6);
	Map->map = NULL;
	free(Map->no);
	Map->no = NULL;
	free(Map->so);
	Map->so = NULL;
	free(Map->we);
	Map->we = NULL;
	free(Map->ea);
	Map->ea = NULL;
	free(Map->f);
	Map->f = NULL;
	free(Map->c);
	Map->c = NULL;
}

void	init_null(t_map *Map)
{
	Map->map = NULL;
	Map->no = NULL;
	Map->so = NULL;
	Map->we = NULL;
	Map->ea = NULL;
	Map->f = NULL;
	Map->c = NULL;
	Map->f_img = NULL;
	Map->c_img = NULL;
	Map->images[0].img = NULL;
	Map->images[1].img = NULL;
	Map->images[2].img = NULL;
	Map->images[3].img = NULL;
}

int	line_check(char *map)
{
	int		count;
	size_t	i;

	i = -1;
	count = 0;
	if (map == NULL)
		return (1);
	while (map[++i] && count < 6)
	{
		if (map[i] == '\n')
		{
			count++;
			while (map[i] == '\n')
				i++;
		}
	}
	return (line_check2(map, count, i));
}

void	map_size(char *map, t_map *Map, int i)
{
	int	max;
	int	row;
	int	col;

	max = 0;
	row = 0;
	col = 0;
	if (map)
	{
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
	}
	Map->row_count = row;
	Map->col_count = max;
}

int	is_bad(char c)
{
	if (!c || c == ' ' || c == '\n' || c == '\0')
		return (1);
	return (0);
}
