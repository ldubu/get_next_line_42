#include "get_next_line.h"

int main(void)
{
	int	 fd = open("./gnlTester/files/big_line_with_nl", O_RDONLY);
	char	*line;
	if (fd <= 0) {
		write(1, "fail to open file", 17);
		return (1);
	}
	//printf("fd = %d\n", fd);
	line = get_next_line(fd);
	//printf("%s", line);
	while (line != NULL)
	{
		printf("%s", line);
		//printf("==========================================\n");
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		
	}
	printf("%s", line);
	return (0);
}