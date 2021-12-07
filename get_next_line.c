#include "get_next_line.h"

char    *get_next_line(int fd) //cas où fd = 0, >0, renvoyer une erreur si fd correspond à rien où si read fail
{
    char *first_read;

    errno = 0;
    first_read = (char *) malloc(sizeof(char) *24);
    if (!first_read)
    {
        write(1, "error malloc", 12);
        return (NULL);
    }
    if (read(fd, first_read, 24) <= 0)
    {
        if (errno ==  EISDIR)
            write(1, "read error", 10);
        return (NULL);
    }
    return (first_read);
}

int main(void)
{
    int     fd = open("test.txt", O_RDONLY);
    char    *line;
    if (fd <= 0)
        write(1, "fail to open file", 17);
    printf("fd = %d\n", fd);
    line = get_next_line(fd);
    printf("%s", line);
    return (0);
}