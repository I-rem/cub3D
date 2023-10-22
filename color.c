#include "cub3d.h"

int	err (char *str, t_map *Map)
{
	if (Map)
		free_map(Map);
	Map = NULL;
	if (str)
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
	if (type == 1 && ft_strncmp(filepath + len - 4, ".cub", 4))
		return (0);
	else if (type == 2 && ft_strncmp(filepath + len - 4, ".xpm", 4))
		return (0);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (0);
	return (fd);
}

char	*find_binary (int decimal)
{
	char	*binary;
	char	*temp;

	binary = ft_strdup("");
	while (decimal > 0)
	{
		if (decimal % 2 == 1)
			temp = ft_strjoin("1", binary);
		else
			temp = ft_strjoin("0", binary);
		decimal /= 2;
		free(binary);
		binary = temp;
		temp = NULL;
	}
	return (binary);
}

int	find_decimal (char *binary)
{
	int	result;
	int	i;

	i = -1;
	result = 0;
	while (binary[++i])
		result = result * 2 + binary[i] - '0';
	return (result);
}

int find_color(char *str)
{
    char **rgb = ft_split(str, ',');
    int i;
    char *color = ft_strdup("");
    int result;

    i = -1;
    while (rgb[++i])
    {
        int temp = ft_atoi(rgb[i]);
        char *binary = find_binary(temp);
        char *temp_color = ft_strjoin(color, binary);
        if (color)
            free(color);  
        color = temp_color;
		if (binary)
        	free(binary);
		binary = NULL;
		temp_color = NULL;
    }
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
