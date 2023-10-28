/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:40 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 10:51:41 by ikayacio         ###   ########.fr       */
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
	free(Map->NO);
	Map->NO = NULL;
	free(Map->SO);
	Map->SO = NULL;
	free(Map->WE);
	Map->WE = NULL;
	free(Map->EA);
	Map->EA = NULL;
	free(Map->F);
	Map->F = NULL;
	free(Map->C);
	Map->C = NULL;
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

