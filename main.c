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
    fd = open(filepath, O_CREAT || O_RDONLY);

    if (fd == -1)
    {
        close(fd);
        return 0;
    }

    return (fd);
}

void    init_map(int fd)
{
    char    *str;
    char    *result;

    str = get_next_line(fd);
    while(str)
    {
        result = ft_strjoin(result, str);
        free(str);
        str = get_next_line(fd);
    }
    free(str);
}
int main(int argc, char **argv)
{
    int fd;

    if (argc != 2)
        return (err("Incorrect number of arguments. Error\n"));
    fd = file_check(argv[1]);
    if (!fd)
        return (err("Invalid file. Error\n")); // Error mesajý fonksiyonu ekle;
    //init_map(fd);
    //free_all();
    return (0);
}
