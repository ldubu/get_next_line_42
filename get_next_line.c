#include "get_next_line.h"

char    *get_next_line(int fd) //cas où fd = 0, >0, renvoyer une erreur si fd correspond à rien où si read fail
{
	char	*first_read;
	char	*final_str;
	size_t	len;

	errno = 0;
	first_read = (char *) malloc(sizeof(char) *24);
	if (!first_read)
	{
		write(1, "error malloc", 12);
		return (NULL);
	}
	len = read(fd, first_read, 24);
	if ( len <= 0)
	{
		write(1, "error read", 10);
		return (NULL);
	}
	first_read[len] = '\0';
	while (!ft_strrchr(first_read, '\n'))
	{
		
	}

	return (first_read);
}

int main(void)
{
	int	 fd = open("test.txt", O_RDONLY);
	char	*line;
	if (fd <= 0)
	write(1, "fail to open file", 17);
	printf("fd = %d\n", fd);
	line = get_next_line(fd);
	printf("%s", line);
	return (0);
}