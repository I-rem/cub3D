#include "cub3d.h"

int	err (char *str, t_map *Map)
{
	if (str)
		while (*str)
			write(1, str++, 1);
	if (Map)
		free_map(Map);
	Map = NULL;
	return (1);
}

int	file_check(char *filepath, int type)
{
	int	len;
	int	fd;

	if (filepath == NULL)
		return(0);
	len = ft_strlen(filepath);
	if (type == 1 && ft_strncmp(filepath + len - 4, ".cub", 4))
		return (0);
	else if (type == 2 && ft_strncmp(filepath + len - 4, ".xpm", 4))
		return (0);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}

int	find_color2(char **rgb, char *color)
{
	int	i;
	int	result;

	result = find_decimal(color);
    free(color);
    color = NULL;
    i = -1;
    while (rgb[++i])
    {
        free(rgb[i]);
        rgb[i] = NULL;
    }
	if (rgb)
    	free(rgb);
    rgb = NULL;
    return result;
}

int find_color(char *str)
{
    char	**rgb;
    int		i;
    char	*color;
	int		temp;
	char	*binary;
	char	*temp_color;

    i = -1;
	rgb = ft_split(str, ',');
	color = ft_strdup("");
    while (rgb[++i])
    {
        temp = ft_atoi(rgb[i]);
        binary = find_binary(temp);
        temp_color = ft_strjoin(color, binary);
        if (color)
            free(color);  
        color = temp_color;
		if (binary)
        	free(binary);
		binary = NULL;
		temp_color = NULL;
    }
	return (find_color2(rgb, color));
}
