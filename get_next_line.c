#include "get_next_line_bonus.h"

char	*read_line(char *current_read, char **str, int fd);
void	free_str(char **str);

char	*get_next_line(int fd) //erreur fd <= 0, fd > FD_MAX, BUFFER_SIZE inférieur à zéro (+ trop grande ?)
{
	static char *BUFFER;
	char		*current_read;
	int			len;

	//printf("fd %d\n", fd);
	//printf("Buffer size = %d\n", BUFFER_SIZE);
	if (fd <= 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	//printf("ERROR1\n");
	
	
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1)); //chaine que l'on renvoie, free par le programme
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE);
	//printf("len %d\n", len);	
	
	if (len < 0)
	{
		free(current_read);
		return (NULL);
	}
	current_read[len] = '\0';
	
	if (current_read[0] == '\0')
	{
		//printf(" str address after end  %p\n", BUFFER);
		if (BUFFER != NULL)
			free(BUFFER);
		free(current_read);
		return (NULL);
	}

	if (!BUFFER)
		BUFFER = ft_strdup(""); //free quand arrivé à la fin du fichier ou à la fin du programme
	if (!BUFFER)
		return (NULL);

	current_read = read_line(current_read, &BUFFER, fd);
	//printf("current %s\n", current_read);
	return (current_read);
}

char	*read_line(char *current_read, char **str, int fd)
{
	char	*temp;
	int		len;
	char	*retour;
	char 	*nl_position;
	int		i;

	temp = NULL;
	len = 1;
	while (ft_strrchr(*str, '\n') == NULL && len != 0)
	{
		//printf(" str address %p\n", *str);
		temp = *str;
		*str = ft_strjoin(*str, current_read); //on envoie 2 string, str free par swap et current que l'on réecrit donc pas de free
		if (!*str)
			return (NULL);
		free(temp); //free ancienne str
		if (ft_strrchr(*str, '\n') == NULL)
		{	len = read(fd, current_read, BUFFER_SIZE);
			if (len < 0)
				return (NULL);
			current_read[len] = '\0';		
		}
	}
	//printf("str after while %s.", *str);
	nl_position = ft_strrchr(*str, '\n');
	if (nl_position)
	{
		len = nl_position - *str + 1;
		//printf("len %d\n", len);
		retour = (char *) malloc(sizeof(char) * len+1);
		if (!retour)
			return (NULL);
		i = 0;
		while (len--)
		{
			retour[i] = (*str)[i];
			i++;
		}
		retour[i] = '\0';
		temp = *str;
		*str = ft_strjoin("", nl_position+1);
		if (!*str)
			return (NULL);
		//printf(" str address after retour %p\n", *str);
		free(temp);
		free(current_read);
		return (retour);
	}
	else
	{
		if ((*str)[0] == '\0')
		{
			printf(" str address after end big f %p\n", *str);
			free(*str);
			free(current_read);
			return (NULL);
		}
		len = ft_strlen(*str);
		retour = (char *) malloc(sizeof(char) * len +1);
		if (!retour)
			return (NULL);
		i = 0;
		while (len--)
		{
			retour[i] = (*str)[i];
			i++;
		}
		retour[i] = '\0';
		temp = *str;
		*str = ft_strjoin("", *str+i);
		if (!*str)
			return (NULL);
		free(temp);
		//printf(" str address after no nl %p\n", *str);
		free(current_read);
		//printf("temp %p", temp);
		return (retour);
	}
}

void	free_str(char **str)
{
	if (!str)
		free(*str);
	str = NULL;
}

/*int main(void)
{
	int	 fd = open("big_line.txt", O_RDONLY);
	char	*line;
	if (fd <= 0)
	write(1, "fail to open file", 17);
	//printf("fd = %d\n", fd);
	line = get_next_line(fd);
	//printf("%s", line);
	while (line != NULL)
	{
		printf("%s", line);
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		
	}
	return (0);
}*/