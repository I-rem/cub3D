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

char	*find_binary (int decimal)
{
	char	*binary;

	binary = "";
	while (decimal > 0)
	{
		if (decimal % 2 == 1)
			binary = ft_strjoin("1", binary);
		else
			binary = ft_strjoin("0", binary);
		decimal /= 2;
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

int	find_color (char *str)
{
	char	**rgb;
	int	temp;
	int 	i;
	char	*color;

	color = "";
	rgb = ft_split(str, ',');
	i = - 1;
	while (rgb[++i])
	{
		temp = ft_atoi(rgb[i]);
		color = ft_strjoin(color, find_binary(temp));
	}
	return (find_decimal(color));	
}
