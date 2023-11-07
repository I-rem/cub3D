/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:51:16 by ikayacio          #+#    #+#             */
/*   Updated: 2023/10/28 14:49:49 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_map2(char *result, t_map *Map)
{
	int	i;

	map_size(result, Map, -1);
	if (Map->row_count < 9 || Map->col_count < 4 || line_check(result))
	{
		if (result)
			free(result);
		return (err("Invalid map format. Error\n", Map));
	}
	Map->map = ft_split(result, '\n');
	i = 0;
	while (Map->map[i])
		i++;
	Map->row_count = i;
	if (result)
		free(result);
	if (!Map->map)
		return (err("Memory allocation failed. Error\n", Map));
	return (texture_check(Map, -1));
}

int	init_map(int fd, t_map *Map)
{
	char	*str;
	char	*result;
	char	*temp;

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
			return (err("Memory allocation failed. Error\n", Map));
		result = temp;
		str = get_next_line(fd);
	}
	Map->flags.w_flag = 0;
	Map->flags.a_flag = 0;
	Map->flags.s_flag = 0;
	Map->flags.d_flag = 0;
	Map->flags.r_flag = 0;
	Map->flags.l_flag = 0;
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
	max = 0;
	while (Map->map[++i])
	{
		j = 0;
		write(1, "\n", 1);
		while (Map->map[i][j])
			j++;
		if (j > max)
			max = j;
	}
	write(1, "\n", 1);
	Map->col_count = max;
}

void	init_dir(t_map *Map)
{
	if (Map->start_dir == 'W')
	{
		Map->player.dir_x = -1.0;
		Map->player.dir_y = 0.0;
	}
	else if (Map->start_dir == 'E')
	{
		Map->player.dir_x = 1.0;
		Map->player.dir_y = 0.0;
	}
	else if (Map->start_dir == 'N')
	{
		Map->player.dir_x = 0.0;
		Map->player.dir_y = -1.0;
	}
	else if (Map->start_dir == 'S')
	{
		Map->player.dir_x = 0.0;
		Map->player.dir_y = 1.0;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	map;

	if (argc != 2)
		return (err("Incorrect number of arguments. Error\n", NULL));
	fd = file_check(argv[1], 1);
	if (!fd)
		return ((err("Invalid file. Error\n", NULL)));
	if (init_map(fd, &map))
		return (1);
	close(fd);
	init_dir(&map);
	map.player.cam_x = 0.0;
	map.player.cam_y = 0.66;
	map.player.pos_x += 0.5;
	map.player.pos_y += 0.5;
	map.window.mlx_ptr = mlx_init();
	if (map.window.mlx_ptr == NULL)
		return (err("Mlx Pointer Error\n", &map));
	open_window(&map);
	img_init(&map, -1);
	free_map(&map);
}
