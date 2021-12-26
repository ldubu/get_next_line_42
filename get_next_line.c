/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldubuche <laura.dubuche@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:58 by ldubuche          #+#    #+#             */
/*   Updated: 2021/12/22 18:42:34 by ldubuche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer(char *current_read, char *buffer, int fd);
char	*ft_buffjoin(char *buffer, char *str, char *to_free);
char	*r_value(char **buffer);
char	*free_str(char *str);

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*current_read;
	int			len;
	
	//printf("enter fonction\n");
	if (fd <= 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	current_read = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!current_read)
		return (NULL);
	len = read(fd, current_read, BUFFER_SIZE);
	if (len < 0)
		return (free_str(current_read));
	current_read[len] = '\0';
	//printf("read len %d\n", len);
	if (len > 0)
	{
		buffer = fill_buffer(current_read, buffer, fd);
		//printf("buffer after fill :.%s.\n", buffer);
		if (buffer == NULL)
			return (free_str(current_read));
	}
	else if (len == 0 && (!buffer || buffer[0] == '\0'))
	{
		if (buffer != NULL)
			free(buffer);
		return (free_str(current_read));
	}
	if (current_read != NULL)
		free(current_read);
	current_read = NULL;
	//printf("buffer :.%s.\n", buffer);
	return (r_value(&buffer));
}

char	*fill_buffer(char *current_read, char *buffer, int fd)
{
	int		len;

	//printf("enter fill\n");
	len = 1;
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (free_str(buffer));
	}
	buffer = ft_buffjoin(buffer, current_read, buffer);
	if (!buffer)
		return (NULL);
	//printf("buffer fill :.%s.\n", buffer);
	while (ft_strrchr(buffer, '\n') == NULL && len != 0)
	{
		if (ft_strrchr(buffer, '\n') == NULL)
		{	
			len = read(fd, current_read, BUFFER_SIZE);
			if (len < 0)
				return (NULL);
			current_read[len] = '\0';
		}
		buffer = ft_buffjoin(buffer, current_read, buffer);
		if (!buffer)
			return (NULL);
		//printf("buffer fill :.%s.\n", buffer);
	}
	return (buffer);
}

char	*r_value(char **buffer)
{
	int		len;
	char	*retour;
	char	*nl_position;
	int		i;

	nl_position = ft_strrchr(*buffer, '\n');
	if (nl_position)
		len = nl_position - *buffer + 1;
	else
		len = ft_strlen(*buffer);
	retour = (char *) malloc(sizeof(char) * len + 1);
	if (!retour)
		return (free_str(*buffer));
	i = 0;
	while (len--)
	{
		retour[i] = (*buffer)[i];
		i++;
	}
	retour[i] = '\0';
	if (nl_position)
		*buffer = ft_buffjoin("", nl_position + 1, *buffer);
	else
		*buffer = ft_buffjoin("", *buffer + i, *buffer);
	if (!(*buffer))
		return (free_str(*buffer));
	//printf("retour = .%s.\n", retour);
	//printf("buffer retour :.%s.\n", *buffer);
	return (retour);
}

char	*ft_buffjoin(char *buffer, char *str, char *to_free)
{
	buffer = ft_strjoin(buffer, str);
	if (!buffer)
		return (NULL);
	free(to_free);
	return (buffer);
}

char	*free_str(char *str)
{
	if (str != NULL)
		free(str);
	return (NULL);
}
