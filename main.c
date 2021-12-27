#include "get_next_line.h"

int main(void)
{
    int     fd = open("gnlTester/files/41_with_nl", O_RDONLY);
    char    *line;
    if (fd <= 0)
    write(1, "fail to open file", 17);
    printf("fd = %d\n", fd);
	line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
		line = get_next_line(fd);
    }
    printf("%s", line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
    return (0);
}