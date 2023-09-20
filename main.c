#include "cub3d.h"

int err(char *str)
{
    while (*str)
        write(2, str++, 1);
    return (1);
}

// .cub formatý, dosya varlýðý, izinleri, açýlabilme kontrolü
int file_check(char *filepath)
{
    int len;
    int fd;

    len = ft_strlen(filepath);
    if (ft_strncmp(filepath + len - 4, ".cub", 4))
        return (0);
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
    {
        close(fd);
        return 0;
    }
    return (fd);
}

void    map_size(char *map, t_map *Map)
{
    int max;
    int row;
    int i;
    int col;

    i = -1;
    max = 0;
    row = 0;
    col = 0;
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
    Map->row_count = row;
    Map->col_count = max;

    //Map->map = (char **)malloc(sizeof(char *) * row + 1);
    //Map->*map = (char *)malloc(sizeof(char) * max + 1);

}

void    init_map(int fd, t_map *Map)
{
    char    *str;
    char    *result;

    str = get_next_line(fd);
    result = "";
    while(str)
    {
        result = ft_strjoin(result, str);
        free(str);
        str = get_next_line(fd);
    }
    free(str);
    map_size(result, Map);
    Map->map = ft_split(result, '\n');
    free(result);
}

int main(int argc, char **argv)
{
    int fd;
    t_map Map;

    if (argc != 2)
        return (err("Incorrect number of arguments. Error\n"));
    fd = file_check(argv[1]);
    if (!fd)
        return (err("Invalid file. Error\n"));
    init_map(fd, &Map);
    //free_all();
    return (0);
}
