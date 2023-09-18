#include "cub3d.h"

// .cub formatı, dosya varlığı, izinleri, açılabilme kontrolü
int file_check(char *filepath)
{
    int len;

    len = 0;
    while (filepath[len])
        len++;
    if (filepath[len - 1] != 'b' || filepath[len - 2] != 'u'
    || filepath[len - 3] != 'c' || filepath[len - 4] != '.')
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    if (argc != 2 || !file_check(argv[1]))
        return 1; // Error mesajı fonksiyonu ekle;
}