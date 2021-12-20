#include "get_next_line_bonus.h"

char	*read_line(char *current_read, char **str, int fd);

char	*get_next_line(int fd) //erreur fd <= 0, fd > FD_MAX, BUFFER_SIZE inférieur à zéro (+ trop grande ?)
{
	static char *BUFFER[FD_MAX];
	char		*current_read;
	int			len;

	if (fd <= 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
	return (NULL);
	if (!BUFFER[fd])
	BUFFER[fd] = ft_strdup("");
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE);
	if (len < 0)
		return (NULL); //si len < buffer_size == fin du fichier
	current_read[len] = '\0';
	//printf("première valeur: %s\n", current_read);
	//printf("buffer %s\n", BUFFER[fd]);
	current_read = read_line(current_read, &BUFFER[fd], fd);
	//printf("RETOUR SUITE %s\n", current_read);
	return (current_read);
}

char	*read_line(char *current_read, char **str, int fd)
{
	char	*temp;
	int		len;
	char	*retour;
	char 	*n_position;
	int		i;

	temp = NULL;
	len = 1;
	while (ft_strrchr(*str, '\n') == NULL && len != 0)
	{
		temp = *str;
		*str = ft_strjoin(*str, current_read);
		if (!*str)
			return (NULL);
		free(temp); //remettre current read à 0 ?
		//printf("str %s \n", *str);
		if (ft_strrchr(*str, '\n') == NULL)
		{	len = read(fd, current_read, BUFFER_SIZE);
			//printf("len %d\n", len);
			if (len < 0) //si len < buffer_size == fin du fichier
				return (NULL);
			current_read[len] = '\0';		
			//printf("current %s\n", current_read);
			//printf("str %s \n", *str);
		}
	}
	n_position = ft_strrchr(*str, '\n');
	if (n_position)
	{
		//printf("if \n %s\n", *str);
		len = n_position - *str + 1;
		retour = (char *) malloc(sizeof(char) * len+1);
		if (!retour)
			return (NULL);
		i = 0;
		while (len--)
		{
			retour[i] = (*str)[i];
			i++;
		}
		temp = *str;
		*str = ft_strjoin("", n_position+1);
		retour[i] = '\0';
		free(temp);
		//printf("RETOUR %s\n", retour);
		return (retour);
	}
	else
	{
		//printf("end retour %s \n", *str);
		if ((*str)[0] == '\0')
			return (NULL);
		len = ft_strlen(*str);
		retour = (char *) malloc(sizeof(char) * len +1);
		if (!retour)
			return (NULL);
		//printf("len %s\n", *str);
		i = 0;
		while (len--)
		{
			retour[i] = (*str)[i];
			i++;
		}
		retour[i] = '\0';
		//printf("retour %c\n", retour[0]);
		if (str != NULL)
		{
			free(*str);
			str = NULL;
		}
		return (retour);
	}
}

/*int main(void)
{
	int	 fd = open("test.txt", O_RDONLY);
	char	*line;
	if (fd <= 0)
	write(1, "fail to open file", 17);
	printf("fd = %d\n", fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		
	}
	return (0);
}*/