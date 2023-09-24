#include "cub3d.h"

char	*find_binary(int decimal)
{
	char	*binary;
	
	binary = "";
	return binary;
}

int	*find_decimal(char *binary)
{
	int result;
	int i;

	i = -1;
	result = 0;
	while (binary[++i])
	{
		result = result*2 + binary[i] - '0';
	}
}

int find_color(char *str)
{
	char	**rgb;
	int	temp;
	int 	i;
	char	*color;

	color = "";
	rgb = ft_split(str, ", ");
	i = - 1;
	while (rgb[++i])
	{
		temp = ft_atoi(rgb[i]);
		color = ft_strjoin(color, find_binary(decimal));
	}
	return (find_decimal(color));	
}
