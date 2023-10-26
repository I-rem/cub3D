#include "cub3d.h"

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

int	color_check2(t_map *Map, int i, int len, char **rgb)
{
	int colorValue;
	int	j;

	while (++i < len)
    {
        colorValue = ft_atoi(rgb[i]);
        if (colorValue > 255 || colorValue < 0)
        {
			j = -1;
            while (++j < len)
            {
                free(rgb[j]);
                rgb[j] = NULL;
            }
            if (rgb)
                free(rgb);
            rgb = NULL;
            return err("Wrong color format. Error\n", Map);
        }
        free(rgb[i]);
        rgb[i] = NULL;
    }
	free(rgb);
    rgb = NULL;
    return (0);
}

int color_check(char *color, t_map *Map)
{
    char	**rgb;
    int		len;
	int		i;

    rgb = ft_split(color, ',');
    len = 0;
	while (rgb && rgb[len])
		len++;
	i = -1;
    if (len != 3)
    {
		while (++i < len)
		{
			free(rgb[i]);
            rgb[i] = NULL;
		}
        if (rgb)
            free(rgb);
        rgb = NULL;
        return err("Wrong color format. Error\n", Map);
    }
	return (color_check2(Map, i, len, rgb));
}